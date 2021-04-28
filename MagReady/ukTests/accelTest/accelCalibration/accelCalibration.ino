#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h> 

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(51234);

void setup() {
  Serial.begin(9600);
  accel.begin();
  Wire.begin();
  //mag.begin();

  //Matlab Handshake
  //
  Serial.println('a');
  char a = 'b';
  while(a != 'a')
  {
    a=Serial.read();
  }
  //*/
  
  accel.setRange(LSM303_RANGE_4G);
  accel.setMode(LSM303_MODE_HIGH_RESOLUTION);
} 
void loop() {

  float Xa_off, Ya_off, Za_off, Xa_cal, Ya_cal, Za_cal;
  
  sensors_event_t event;
  accel.getEvent(&event);
  
  Xa_off = event.acceleration.x + 0; //X-axis combined bias (Non calibrated data - bias)
  Ya_off = event.acceleration.y + 0; //Y-axis combined bias (Default: substracting bias)
  Za_off = event.acceleration.z + 0; //Z-axis combined bias

  Xa_cal =  1*Xa_off + 0*Ya_off + 0*Za_off; //X-axis correction for combined scale factors (Default: positive factors)
  Ya_cal =  0*Xa_off + 1*Ya_off + 0*Za_off; //Y-axis correction for combined scale factors
  Za_cal =  0*Xa_off + 0*Ya_off + 1*Za_off; //Z-axis correction for combined scale factors

  Serial.println(Xa_cal,7);
  Serial.println(Ya_cal,7);
  Serial.println(Za_cal,7);


  }
