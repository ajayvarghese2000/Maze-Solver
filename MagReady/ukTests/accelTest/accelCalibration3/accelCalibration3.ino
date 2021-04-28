#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h> 
#define pi 3.141593

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

  float Xa_off, Ya_off, Za_off, Xa_cal, Ya_cal, Za_cal,roll,pitch;
  
  sensors_event_t event;
  accel.getEvent(&event);
  
  Xa_off = event.acceleration.x + 0.09936010; //X-axis combined bias (Non calibrated data - bias)
  Ya_off = event.acceleration.y + -0.20228716; //Y-axis combined bias (Default: substracting bias)
  Za_off = event.acceleration.z + 0.13047152; //Z-axis combined bias
    
  Xa_cal =  1.02674657*Xa_off + -0.00200062*Ya_off + 0.00374363*Za_off; //X-axis correction for combined scale factors (Default: positive factors)
  Ya_cal =  -0.00200062*Xa_off + 1.00162291*Ya_off + -0.00285011*Za_off; //Y-axis correction for combined scale factors
  Za_cal =  0.00374363*Xa_off + -0.00285011*Ya_off + 0.98308850*Za_off; //Z-axis correction for combined scale factors

  //roll  = atan2(Xa_cal, sqrt(Xa_cal*Xa_cal + Za_cal*Za_cal));
  //pitch = atan2(Xa_cal, sqrt(Ya_cal*Ya_cal + Za_cal*Za_cal));

  pitch  = atan2(Xa_cal, Za_cal);
  roll = atan2(Ya_cal, Za_cal);

  Serial.println(pitch,7);
  Serial.println(roll,7);

  //Serial.println(360*pitch/(2*pi),7);
  //Serial.println(360*roll/(2*pi),7);

  //Serial.println(Xa_cal);
  //Serial.println(Ya_cal);
  //Serial.println(Za_cal);
  //Serial.println("");

  delay(25);
  }
