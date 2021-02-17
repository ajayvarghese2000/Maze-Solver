#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h> 

Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

void setup() 
{
  Serial.begin(9600);
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
  Serial.println(event.magnetic.x);
  Serial.println(event.magnetic.y);
  delay(50);
}
