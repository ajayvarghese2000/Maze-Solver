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
}

void loop()
{
  sensors_event_t event;
  mag.getEvent(&event);
  
  float Xm_off, Ym_off, Zm_off, Xm_cal, Ym_cal, Zm_cal;

  Xm_off = event.magnetic.x*(1000.0) + 9323.33088288; //X-axis combined bias (Non calibrated data - bias)
  Ym_off = event.magnetic.y*(1000.0) + 20609.34028329; //Y-axis combined bias (Default: substracting bias)
  Zm_off = event.magnetic.z*(1000.0) + 5216.68897173; //Z-axis combined bias

  Xm_cal =  1.03973393*Xm_off + 0.00420141*Ym_off + -0.00141117*Zm_off; //X-axis correction for combined scale factors (Default: positive factors)
  Ym_cal =  0.00420141*Xm_off + 0.98508591*Ym_off + 0.01723721*Zm_off; //Y-axis correction for combined scale factors
  Zm_cal =  -0.00141117*Xm_off + 0.01723721*Ym_off + 1.01552846*Zm_off; //Z-axis correction for combined scale factors

  //Serial.print(Xm_cal, 10); Serial.print(" "); Serial.print(Ym_cal, 10); Serial.print(" "); Serial.println(Zm_cal, 10);
  //Serial.print("X: ");
  //Serial.print("Y: ");
  //Serial.print("Z: ");
  
  Serial.println(Xm_cal,10);
  Serial.println(Ym_cal,10);

  Serial.println(event.magnetic.x*(1000.0),10);
  Serial.println(event.magnetic.y*(1000.0),10);
  //Serial.println(Zm_cal,10);
  delay(40);//40
}
