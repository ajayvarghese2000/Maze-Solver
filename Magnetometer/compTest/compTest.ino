#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h> 

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(51234);
Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

double Gxz = 0;
double Gyz = 0;

double Xh = 0;
double Yh = 0;

void setup() {
  Serial.begin(9600);
  accel.begin();
  mag.begin();
  Wire.begin();

  //Matlab Handshake
  //
  Serial.println('a');
  char a = 'b';
  while(a != 'a')
  {
    a=Serial.read();
  }
  //*/
  
}

void loop() {
  sensors_event_t e;
  sensors_event_t e2;
  
  mag.getEvent(&e);
  accel.getEvent(&e2);

  //pitch = atan2(e2.acceleration.z,e2.acceleration.x);
  //roll = atan2(e2.acceleration.z,e2.acceleration.y);
  
  //Xh = (e.magnetic.x)*cos(pitch)+(e.magnetic.z)*sin(pitch);
  //Yh = (e.magnetic.x)*sin(roll)*sin(pitch)+(e.magnetic.y)*cos(roll)-(e.magnetic.z)*sin(roll)*cos(pitch);

  //Xh = (e.magnetic.x)*cos(pitch) + (e.magnetic.y)*sin(pitch)*sin(roll) - (e.magnetic.z)*cos(roll)*sin(pitch);
  //Yh = (e.magnetic.y)*cos(roll) + (e.magnetic.z)*sin(roll);
  
  Gxz = sqrt((e2.acceleration.z)*(e2.acceleration.z)+(e2.acceleration.x)*(e2.acceleration.x));
  Gyz = sqrt((e2.acceleration.z)*(e2.acceleration.z)+(e2.acceleration.y)*(e2.acceleration.y));  
   
  Xh = (e.magnetic.z)*((e2.acceleration.x)/(Gxz))+(e.magnetic.x)*((e2.acceleration.z)/(Gxz));
  Yh = (e.magnetic.z)*((e2.acceleration.y)/(Gyz))+(e.magnetic.y)*((e2.acceleration.z)/(Gyz));
  
  /*
  Serial.print("Pitch:");
  Serial.println(pitch);
  Serial.print("Roll:");
  Serial.println(roll);
  */
  //Serial.print("X:");
  Serial.println(e.magnetic.x);
  //Serial.print("Y:");
  Serial.println(e.magnetic.y);
/* 
  Serial.print(event2.acceleration.x);
  Serial.print(event2.acceleration.y);
  Serial.print(event2.acceleration.z);
  Delay before the next sample */
  delay(50);

}
