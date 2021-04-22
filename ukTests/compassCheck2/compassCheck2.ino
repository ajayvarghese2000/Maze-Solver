#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

void setup()
{
Serial.begin(9600);
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
  
  float Xm_off, Ym_off, Zm_off, Xm_cal, Ym_cal, Zm_cal, Xm2_off, Ym2_off, Zm2_off, Xm2_cal, Ym2_cal, Zm2_cal;

  Xm_off = event.magnetic.x*(1000.0) + 11043.48991573; //X-axis combined bias (Non calibrated data - bias)
  Ym_off = event.magnetic.y*(1000.0) + 19945.89879643; //Y-axis combined bias (Default: substracting bias)
  Zm_off = event.magnetic.z*(1000.0) + 6179.35963384; //Z-axis combined bias

  Xm_cal =  0.56951592*Xm_off + 0.00564035*Ym_off + -0.00072947*Zm_off; //X-axis correction for combined scale factors (Default: positive factors)
  Ym_cal =  0.00564035*Xm_off + 0.53849090*Ym_off + 0.00005520*Zm_off; //Y-axis correction for combined scale factors
  Zm_cal =  -0.00072947*Xm_off + 0.00005520*Ym_off + 0.56013352*Zm_off; //Z-axis correction for combined scale factors

  Xm2_off = Xm_cal - 65.96475937; //X-axis combined bias (Non calibrated data - bias)
  Ym2_off = Ym_cal - 144.46051992; //Y-axis combined bias (Default: substracting bias)
  Zm2_off = Zm_cal - 264.77626554; //Z-axis combined bias

  Xm2_cal =  1.03538986*Xm2_off + -0.00464247*Ym2_off + -0.00028484*Zm2_off; //X-axis correction for combined scale factors (Default: positive factors)
  Ym2_cal =  -0.00464247*Xm2_off + 1.02451135*Ym2_off + -0.00579398*Zm2_off; //Y-axis correction for combined scale factors
  Zm2_cal =  -0.00028484*Xm2_off + -0.00579398*Ym2_off + 1.02712962*Zm2_off; //Z-axis correction for combined scale factors

  //Serial.print(Xm_cal, 10); Serial.print(" "); Serial.print(Ym_cal, 10); Serial.print(" "); Serial.println(Zm_cal, 10);
  //Serial.print("X: ");
  //Serial.print("Y: ");
  //Serial.print("Z: ");
  if((event.magnetic.x!=0)||(event.magnetic.y!=0)||(event.magnetic.z!=0)){
  Serial.println(Xm2_cal,7);
  Serial.println(Ym2_cal,7);

  Serial.println(0,7);
  Serial.println(0,7);
  //Serial.println(Zm_cal,10);
  delay(60);//40
  }
}
