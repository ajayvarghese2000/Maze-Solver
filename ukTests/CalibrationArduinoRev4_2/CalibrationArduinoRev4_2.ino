#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

void setup()
{
Serial.begin(28800);
Wire.begin();
mag.begin();


//Matlab Handshake
  //
  Serial.println('a');
  char a = 'b';
  while(a != 'a')
  {
    a=Serial.read();
  }
  //*/

  mag.setMagRate(LSM303_MAGRATE_220);
  delay(2500);
}

void loop()
{
  sensors_event_t event;
  mag.getEvent(&event);
  
  float Xm_off, Ym_off, Zm_off, Xm_cal, Ym_cal, Zm_cal;

 Xm_off = event.magnetic.x*(1000.0) + 11043.48991573; //X-axis combined bias (Non calibrated data - bias)
  Ym_off = event.magnetic.y*(1000.0) + 19945.89879643; //Y-axis combined bias (Default: substracting bias)
  Zm_off = event.magnetic.z*(1000.0) + 6179.35963384; //Z-axis combined bias

  Xm_cal =  0.56951592*Xm_off + 0.00564035*Ym_off + -0.00072947*Zm_off; //X-axis correction for combined scale factors (Default: positive factors)
  Ym_cal =  0.00564035*Xm_off + 0.53849090*Ym_off + 0.00005520*Zm_off; //Y-axis correction for combined scale factors
  Zm_cal =  -0.00072947*Xm_off + 0.00005520*Ym_off + 0.56013352*Zm_off; //Z-axis correction for combined scale factors

  //Serial.print(Xm_cal, 10); Serial.print(" "); Serial.print(Ym_cal, 10); Serial.print(" "); Serial.println(Zm_cal, 10);
  //Serial.print("X: ");
  //Serial.print("Y: ");
  //Serial.print("Z: ");
  if((event.magnetic.x!=0)||(event.magnetic.y!=0)||(event.magnetic.z!=0)){
  Serial.println(Xm_cal,7);
  Serial.println(Ym_cal,7);
  Serial.println(Zm_cal,7);

  delay(35);
  }
}
