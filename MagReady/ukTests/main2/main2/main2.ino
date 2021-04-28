#include <Adafruit_LSM303_Accel.h>
#include <Servo.h>
#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h> 
#define Pi 3.14159
//#define ACHIVED 5

float anglPlz(void);
//void turn2angl(float angl,int time2adj);

//Ajay turn functions
void boebot_move_forwards();
void boebot_move_backwards();
void boebot_turn_left();
void boebot_turn_right();
void boebot_turn_180R();
void boebot_turn_180L();
void boebot_stop();

//Good turn functions(JK)
void boebot_turn_right_positive(int ratio);
void boebot_move_line(int ratio);
bool anglSeek(float angl);

//Creating magnetometer and accelerometer entities
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(51234);
Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

// Creating the Servo entities - Will be attached to the pins 11 and 10 in setup()
Servo servoleft;
Servo servoright;

const float alpha = 0.7;//compass filtering 0.4
const float ACHIVED = 5;//error bounds
const float traveltime=30;//30 is good
const float stopintime=1;

float fXa = 0;
float fYa = 0;
float fZa = 0;
float fXm = 0;
float fYm = 0;
float fZm = 0;

float likeAngle=0;

float dynamic = ACHIVED;

int count = 0;
void setup()
{
  Serial.begin(9600);
  
  //STARTING I2C
  Wire.begin();

  //starting LSM303
  accel.begin();
  mag.begin();
  mag.setMagRate(LSM303_MAGRATE_220);
  
  // Attaching pins to the servo
  servoleft.attach(10);
  servoright.attach(11);

  
//Matlab Handshake
  /*
  Serial.println('a');
  char a = 'b';
  while(a != 'a')
  {
    a=Serial.read();
  }
  //*/
  mag.setMagRate(LSM303_MAGRATE_75);
  accel.setRange(LSM303_RANGE_4G);
  accel.setMode(LSM303_MODE_HIGH_RESOLUTION);

  
  likeAngle=anglPlz();
}

void loop(){
   /*
  count = count + 1;
  Serial.println(count);
  if((count % 200)==0){
    if((likeAngle+90)>=360)
    {
      likeAngle=likeAngle+90-360;
    }
    else
    {
      likeAngle=likeAngle+90;
    }
  }
 
  unsigned long tim = millis();
  
  
  while(1){
  if((unsigned long)(tim+5000)<tim)
    break;
  
  }
  //Serial.println(anglPlz());
  boebot_turn_right_positive(temp);
  delay(100);
  */
  bool temp = anglSeek(likeAngle);
  //Serial.print("Actual angle:");
  //Serial.println(anglPlz()); 
  //Serial.print("Desired angle:");
  //Serial.println(likeAngle);   
  //Serial.print("delta angle:");
  //Serial.println(abs(anglPlz()-likeAngle)); 
  /*
  Serial.print("dynamic angle:");
  Serial.println(dynamic); 

  Serial.print("Actual angle:");
  Serial.println(anglPlz()); 
  Serial.print("Desired angle:");
  Serial.println(likeAngle); 
  if(temp==1){
  Serial.println("true--------------------------"); 
  }
  Serial.println("");
  Serial.println("");
  Serial.println("");
  //delay(20);
  */
  //delay(1);
}

bool anglSeek(float angl)
{
  //delay(5);
  
  float rotDir = anglPlz();

  float dirTell = rotDir - angl;

  if(dirTell<-180)
  {
    dirTell=dirTell+360;
  }
  else if(dirTell>180)
  {
    dirTell=dirTell-360;
  }
  
  

  Serial.println((dirTell));
  
  //static float dynamic;
  if(abs(angl-rotDir)< dynamic){ // if angle is reached within ACHIVED degrees
    dynamic = ACHIVED*2;//3 is good
    delay(traveltime);
    boebot_stop();
    return true;
    
  }
 
  else if(dirTell<0)//else if(((rotDir<=angl)&&((rotDir+180.0)>=angl)))//if angle is to the right||
  { 
    Serial.println("right");
    dynamic = ACHIVED;
    if(abs(dirTell)< 20)
    {
      boebot_turn_right_positive(30);
      delay(traveltime*3);
      boebot_stop();
      //delay(stopintime);
    }
    else if(abs(dirTell)< 90)
    {
      boebot_turn_right_positive(100);
      delay(traveltime);
      boebot_stop();
      
      Serial.println("Slow");
      //delay(stopintime);
    }
    else
    {
      boebot_turn_right_positive(200);
      delay(traveltime);
      boebot_stop();
    }
    
    return false;
  }
  else// if angle is to the left
  {
    dynamic = ACHIVED;
    Serial.println("left");
    if(abs(dirTell)< 20)
    {
      boebot_turn_right_positive(-30);
      delay(traveltime*3);
      boebot_stop();
      //delay(stopintime);
    }
    else if(abs(dirTell)< 90)
    {
      boebot_turn_right_positive(-100);
      delay(traveltime);
      boebot_stop();
      Serial.println("Slow");
      //delay(stopintime);
    }
    else
    {
      
      boebot_turn_right_positive(-200);
      delay(traveltime);
      boebot_stop();
    }
    
    
    return false;
  }
}   



float anglPlz()
{
  servoleft.detach();
  servoright.detach();
  
  float Xa_off, Ya_off, Za_off, Xa_cal, Ya_cal, Za_cal;
  float Xm_off, Ym_off, Zm_off, Xm_cal, Ym_cal, Zm_cal, Xm2_off, Ym2_off, Zm2_off, Xm2_cal, Ym2_cal, Zm2_cal;
  float pitch, pitch_print, roll, roll_print, Heading, fXm_comp, fYm_comp;
  
  sensors_event_t event;
  accel.getEvent(&event);

  sensors_event_t event2;
  mag.getEvent(&event2);
  if((event2.magnetic.x!=0)&&(event2.magnetic.y!=0)&&(event2.magnetic.z!=0)){
    //Accel
    Xa_off = event.acceleration.x + 0.09936010; //X-axis combined bias (Non calibrated data - bias)
    Ya_off = event.acceleration.y + -0.20228716; //Y-axis combined bias (Default: substracting bias)
    Za_off = event.acceleration.z + 0.13047152; //Z-axis combined bias
    
    Xa_cal =  1.02674657*Xa_off + -0.00200062*Ya_off + 0.00374363*Za_off; //X-axis correction for combined scale factors (Default: positive factors)
    Ya_cal =  -0.00200062*Xa_off + 1.00162291*Ya_off + -0.00285011*Za_off; //Y-axis correction for combined scale factors
    Za_cal =  0.00374363*Xa_off + -0.00285011*Ya_off + 0.98308850*Za_off; //Z-axis correction for combined scale factors
    
    //Mag (double filter)
    
    Xm2_off = event2.magnetic.x*(1000.0) + 15457.78386802; 
    Ym2_off = event2.magnetic.y*(1000.0) + 25151.00289933; 
    Zm2_off = event2.magnetic.z*(1000.0) - 1962.50002183; 
    
    Xm2_cal =  0.86289497*Xm2_off + 0.00465130*Ym2_off + 0.02390530*Zm2_off; 
    Ym2_cal =  0.00465130*Xm2_off + 0.80913161*Ym2_off + 0.01086330*Zm2_off; 
    Zm2_cal =  0.02390530*Xm2_off + 0.01086330*Ym2_off + 0.83280781*Zm2_off;
    
    // Low-Pass filter accelerometer
    fXa = Xa_cal * alpha + (fXa * (1.0 - alpha));
    fYa = Ya_cal * alpha + (fYa * (1.0 - alpha));
    fZa = Za_cal * alpha + (fZa * (1.0 - alpha));
    
    // Low-Pass filter magnetometer
    fXm = Xm2_cal * alpha + (fXm * (1.0 - alpha));
    fYm = Ym2_cal * alpha + (fYm * (1.0 - alpha));
    fZm = Zm2_cal * alpha + (fZm * (1.0 - alpha));
    
    // Pitch and roll
    //roll  = atan2(fYa, sqrt(fXa*fXa + fZa*fZa));
    //pitch = atan2(fXa, sqrt(fYa*fYa + fZa*fZa));
    //roll_print = roll*180.0/M_PI;
    //pitch_print = pitch*180.0/M_PI;

    pitch  = atan2(Xa_cal, Za_cal);
    roll = atan2(Ya_cal, Za_cal);
    
    
    // Tilt compensated magnetic sensor measurements
    //fXm_comp = fXm*cos(pitch)+fZm*sin(pitch);
    //fYm_comp = fXm*sin(roll)*sin(pitch)+fYm*cos(roll)-fZm*sin(roll)*cos(pitch);

    fXm_comp = fXm*cos(pitch)+fYm*sin(pitch)*sin(roll)-fZm*sin(pitch)*cos(roll);
    //fYm_comp = fYm*cos(roll)+fZm*sin(roll);
    fYm_comp = fXm*sin(roll)*sin(pitch)+fYm*cos(roll)-fZm*sin(roll)*cos(pitch);
    
    float heading = (atan2(fYm_comp,fXm_comp) * 180) / Pi;
 
    // Normalize to 0-360
    if (heading < 0)
    {
    heading = 360 + heading;
    }
    
    servoleft.attach(10);
    servoright.attach(11);
    
    //Serial.println(heading,7);
    return heading;
    //delay(60);
  }
}

// Moves the boebot forward
void boebot_move_line(int ratio){
    //servoleft.writeMicroseconds(1450);
    //servoright.writeMicroseconds(1550);

    servoleft.writeMicroseconds(1500-ratio);
    servoright.writeMicroseconds(1500+ratio);
    return;
}

void boebot_turn_right_positive(int ratio){
    servoleft.writeMicroseconds(1500+ratio);
    servoright.writeMicroseconds(1500+ratio);
    //delay(550);
   // boebot_stop();
}
// Moves the boebot forward
void boebot_move_forwards(){
    servoleft.writeMicroseconds(1450);
    servoright.writeMicroseconds(1550);
    return;
}

// Moves the boebot backward
void boebot_move_backwards(){
    servoleft.writeMicroseconds(1700);
    servoright.writeMicroseconds(1300);
    return;
}

// Turns the boebot left then stops
void boebot_turn_left(){
    servoleft.writeMicroseconds(1400);
    servoright.writeMicroseconds(1400);
    delay(550);
    boebot_stop();
}

// Turns the boebot right
void boebot_turn_right(){
    servoleft.writeMicroseconds(1590);
    servoright.writeMicroseconds(1590);
    delay(550);
    boebot_stop();
    
}

// Turns the robot 180 in the right direction
void boebot_turn_180R(){
    servoleft.writeMicroseconds(1600);
    servoright.writeMicroseconds(1600);
    delay(1000);
    boebot_stop();
    
}

// Turns the robot 180 in the left direction
void boebot_turn_180L(){
    servoleft.writeMicroseconds(1400);
    servoright.writeMicroseconds(1400);
    delay(1000);
    boebot_stop();
    
}

// Stops the Boebot
void boebot_stop(){
    servoleft.writeMicroseconds(1500);
    servoright.writeMicroseconds(1500);
    return;
}
