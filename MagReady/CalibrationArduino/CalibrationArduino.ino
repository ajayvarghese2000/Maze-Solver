#include <Wire.h>
#include <LSM303.h>
LSM303 compass;

void setup()
{
Serial.begin(9600);
Wire.begin();
compass.init();
compass.enableDefault();
//Serial.println("Magnetometer Calibrated (Units in Nanotesla)");

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

void loop()
{
compass.read();
float Xm_off, Ym_off, Zm_off, Xm_cal, Ym_cal, Zm_cal;

Xm_off = compass.m.x*(100000.0/1100.0) + 0; //X-axis combined bias (Non calibrated data - bias)
Ym_off = compass.m.y*(100000.0/1100.0) + 0; //Y-axis combined bias (Default: substracting bias)
Zm_off = compass.m.z*(100000.0/980.0 ) + 0; //Z-axis combined bias

Xm_cal =  1*Xm_off + 0*Ym_off + 0*Zm_off; //X-axis correction for combined scale factors (Default: positive factors)
Ym_cal =  0*Xm_off + 1*Ym_off + 0*Zm_off; //Y-axis correction for combined scale factors
Zm_cal =  0*Xm_off + 0*Ym_off + 1*Zm_off; //Z-axis correction for combined scale factors

//Serial.print(Xm_cal, 10); Serial.print(" "); Serial.print(Ym_cal, 10); Serial.print(" "); Serial.println(Zm_cal, 10);
//Serial.print("X: ");
//Serial.print("Y: ");
//Serial.print("Z: ");
Serial.println(Xm_cal,10);
Serial.println(Ym_cal,10);
Serial.println(Zm_cal,10);

delay(50);
}
