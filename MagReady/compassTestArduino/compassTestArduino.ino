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

Xm_off = compass.m.x*(100000.0/1100.0) - 7024.10400864; //X-axis combined bias (Non calibrated data - bias)
Ym_off = compass.m.y*(100000.0/1100.0) + 5300.20058655; //Y-axis combined bias (Default: substracting bias)
Zm_off = compass.m.z*(100000.0/980.0 ) - 6550.05656025; //Z-axis combined bias

Xm_cal =  0.86131059*Xm_off + 0.01089249*Ym_off + 0.01893214*Zm_off; //X-axis correction for combined scale factors (Default: positive factors)
Ym_cal =  0.01089249*Xm_off + 0.80200574*Ym_off + -0.01610820*Zm_off; //Y-axis correction for combined scale factors
Zm_cal =  0.01893214*Xm_off + -0.01610820*Ym_off + 0.88873569*Zm_off; //Z-axis correction for combined scale factors


//Serial.print(Xm_cal, 10); Serial.print(" "); Serial.print(Ym_cal, 10); Serial.print(" "); Serial.println(Zm_cal, 10);

Serial.println(Xm_cal);
Serial.println(Ym_cal);

Serial.println(compass.m.x*(100000.0/1100.0));
Serial.println(compass.m.y*(100000.0/1100.0));

delay(200);
}
