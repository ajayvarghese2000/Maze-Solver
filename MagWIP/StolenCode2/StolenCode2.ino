#include <Wire.h>
#include <LSM303.h>
LSM303 compass;

void setup()
{
Serial.begin(9600);
Wire.begin();
compass.init();
compass.enableDefault();
Serial.println("Magnetometer Calibrated (Units in Nanotesla)");


}

void loop()
{
compass.read();
float Xm_off, Ym_off, Zm_off, Xm_cal, Ym_cal, Zm_cal;

Xm_off = compass.m.x*(100000.0/1100.0) + 7424.702602; //X-axis combined bias (Non calibrated data - bias)
Ym_off = compass.m.y*(100000.0/1100.0) + 15265.398347; //Y-axis combined bias (Default: substracting bias)
Zm_off = compass.m.z*(100000.0/980.0 ) + 344.341696; //Z-axis combined bias

Xm_cal =  1.073725*Xm_off + 0.006311*Ym_off + -0.002938*Zm_off; //X-axis correction for combined scale factors (Default: positive factors)
Ym_cal =  0.006311*Xm_off + 1.020986*Ym_off + 0.007252*Zm_off; //Y-axis correction for combined scale factors
Zm_cal =  -0.002938*Xm_off + 0.007252*Ym_off + 1.086718*Zm_off; //Z-axis correction for combined scale factors

//Serial.print(Xm_cal, 10); Serial.print(" "); Serial.print(Ym_cal, 10); Serial.print(" "); Serial.println(Zm_cal, 10);



delay(50);
}
