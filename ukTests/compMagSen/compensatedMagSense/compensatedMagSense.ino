#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h> 

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(51234);
Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

const float alpha = 0.4;
float fXa = 0;
float fYa = 0;
float fZa = 0;
float fXm = 0;
float fYm = 0;
float fZm = 0;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  accel.begin();
  mag.begin();
  mag.setMagRate(LSM303_MAGRATE_220);


//Matlab Handshake
  //
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

}

void loop(){
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
    Xm_off = event2.magnetic.x*(1000.0) + 11043.48991573; 
    Ym_off = event2.magnetic.y*(1000.0) + 19945.89879643; 
    Zm_off = event2.magnetic.z*(1000.0) + 6179.35963384; 
    
    Xm_cal =  0.56951592*Xm_off + 0.00564035*Ym_off + -0.00072947*Zm_off; 
    Ym_cal =  0.00564035*Xm_off + 0.53849090*Ym_off + 0.00005520*Zm_off; 
    Zm_cal =  -0.00072947*Xm_off + 0.00005520*Ym_off + 0.56013352*Zm_off; 
    
    Xm2_off = Xm_cal - 65.96475937; 
    Ym2_off = Ym_cal - 144.46051992; 
    Zm2_off = Zm_cal - 264.77626554; 
    
    Xm2_cal =  1.03538986*Xm2_off + -0.00464247*Ym2_off + -0.00028484*Zm2_off; 
    Ym2_cal =  -0.00464247*Xm2_off + 1.02451135*Ym2_off + -0.00579398*Zm2_off; 
    Zm2_cal =  -0.00028484*Xm2_off + -0.00579398*Ym2_off + 1.02712962*Zm2_off;
    
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
    
    Serial.println(fXm_comp,7);
    Serial.println(fYm_comp,7);
    
    //Serial.println(event2.magnetic.x*1000,7);
    //Serial.println(event2.magnetic.y*1000,7);

    Serial.println(Xm2_cal,7);
    Serial.println(Ym2_cal,7);
    
    delay(60);
  }
}
