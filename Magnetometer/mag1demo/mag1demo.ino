#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h> 



Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

void setup(void) {
  Serial.begin(9600);
  Serial.println("Magnetometer Test");
  Serial.println("");

  /* Initialise the sensor */
  if (!mag.begin()) {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while (1)
      ;
  }

}

void loop(void) {
  
  sensors_event_t event;
  mag.getEvent(&event);

  float Pi = 3.14159;

  float angle = (atan2(event.magnetic.y,event.magnetic.x)*180)/Pi;
  
  if (angle < 0) {
  angle = 360 + angle;
  }
  Serial.print("\nAngle: ");
  Serial.println(angle);
  Serial.print("X: ");
  Serial.println(event.magnetic.x);
  Serial.print("Y: ");
  Serial.println(event.magnetic.y);
  Serial.print("Z: ");
  Serial.println(event.magnetic.z);
  delay(500);
}
