
#include <Adafruit_LSM303_Accel.h>
//#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h> 
#include <LSM303.h>

LSM303 compass;

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(51234);
//Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);


void setup() {
  Serial.begin(9600);
  accel.begin();
  Wire.begin();
  //mag.begin();
  
  compass.init();
  compass.enableDefault();

  //Matlab Handshake
  /*
  Serial.println('a');
  char a = 'b';
  while(a != 'a')
  {
    a=Serial.read();
  }
  //*/
  accel.setRange(LSM303_RANGE_4G);
  Serial.print("Range set to: ");
  lsm303_accel_range_t new_range = accel.getRange();
  switch (new_range) {
  case LSM303_RANGE_2G:
    Serial.println("+- 2G");
    break;
  case LSM303_RANGE_4G:
    Serial.println("+- 4G");
    break;
  case LSM303_RANGE_8G:
    Serial.println("+- 8G");
    break;
  case LSM303_RANGE_16G:
    Serial.println("+- 16G");
    break;
  }
  accel.setMode(LSM303_MODE_HIGH_RESOLUTION);
  Serial.print("Mode set to: ");
  lsm303_accel_mode_t new_mode = accel.getMode();
  switch (new_mode) {
  case LSM303_MODE_NORMAL:
    Serial.println("Normal");
    break;
  case LSM303_MODE_LOW_POWER:
    Serial.println("Low Power");
    break;
  case LSM303_MODE_HIGH_RESOLUTION:
    Serial.println("High Resolution");
    break;
  }
}


void loop() {
  compass.read();
  float Xa_print, Ya_print, Za_print;

  
  sensors_event_t e; 
  accel.getEvent(&e);

  Xa_print = compass.a.x/400.0; 
  Ya_print = compass.a.y/400.0;
  Za_print = compass.a.z/400.0;
 

  Serial.print("X:");
  Serial.println(e.acceleration.x);
  Serial.println(Xa_print);
  Serial.print("Y:");
  Serial.println(e.acceleration.y);
  Serial.println(Ya_print);
  Serial.print("Z:");
  Serial.println(e.acceleration.z);
  Serial.println(Za_print);
  Serial.println("");
/* 
  Serial.print(event2.acceleration.x);
  Serial.print(event2.acceleration.y);
  Serial.print(event2.acceleration.z);
  Delay before the next sample */
  delay(1000);

}
