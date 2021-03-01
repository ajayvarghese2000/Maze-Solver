#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h> 

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(51234);
Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

double xz = 0;
double yz = 0;

double Xh = 0;
double Yh = 0;

void setup() {
  Serial.begin(9600);
  accel.begin();
  mag.begin();

  //Matlab Handshake
  /*
  Serial.println('a');
  char a = 'b';
  while(a != 'a')
  {
    a=Serial.read();
  }
  //*/
  
}

void loop() {
  sensors_event_t e;
  sensors_event_t e2;
  
  mag.getEvent(&e);
  accel.getEvent(&e2);

  xz = sqrt((e2.acceleration.x)*(e2.acceleration.x)+(e2.acceleration.z)*(e2.acceleration.z));
  yz = sqrt((e2.acceleration.y)*(e2.acceleration.y)+(e2.acceleration.z)*(e2.acceleration.z));

  Xh=(e.magnetic.x)*((e2.acceleration.x)/xz)+(e.magnetic.z)*((e2.acceleration.z)/xz);
  Yh=(e.magnetic.x)*((e2.acceleration.z)/yz)*((e2.acceleration.z)/xz)+(e.magnetic.y)*((e2.acceleration.y)/yz)-(e.magnetic.z)*((e2.acceleration.z)/yz)*((e2.acceleration.x)/xz);
  //Serial.print("X:");
  Serial.println(Xh);
  //Serial.print("Y:");
  Serial.println(Yh);
/*
  Serial.println(xz);
  Serial.println(yz);
  Serial.print(event2.acceleration.x);
  Serial.print(event2.acceleration.y);
  Serial.print(event2.acceleration.z);
  Delay before the next sample */
  delay(50);

}
