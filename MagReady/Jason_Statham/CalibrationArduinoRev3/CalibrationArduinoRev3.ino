//#include <ArduinoJson.h>
#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

//StaticJsonDocument<500> doc;

Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

void setup()
{
Serial.begin(14400);
Wire.begin();
//Wire.setClock(400000);
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
  
  double Xm_off, Ym_off, Zm_off, Xm_cal, Ym_cal, Zm_cal;

  Xm_off = event.magnetic.x*(1000.0) + 0; //X-axis combined bias (Non calibrated data - bias)
  Ym_off = event.magnetic.y*(1000.0) + 0; //Y-axis combined bias (Default: substracting bias)
  Zm_off = event.magnetic.z*(1000.0) + 0; //Z-axis combined bias

  Xm_cal =  1*Xm_off + 0*Ym_off + 0*Zm_off; //X-axis correction for combined scale factors (Default: positive factors)
  Ym_cal =  0*Xm_off + 1*Ym_off + 0*Zm_off; //Y-axis correction for combined scale factors
  Zm_cal =  0*Xm_off + 0*Ym_off + 1*Zm_off; //Z-axis correction for combined scale factors

  //Serial.print(Xm_cal, 10); Serial.print(" "); Serial.print(Ym_cal, 10); Serial.print(" "); Serial.println(Zm_cal, 10);
  //Serial.print("X: ");
  //Serial.print("Y: ");
  //Serial.print("Z: ");
  //Serial.println(Xm_cal,10);
  //Serial.println(Ym_cal,10);
  //Serial.println(Zm_cal,10);
  //{"X":-19272.73,"Y":-14363.64,"Z":-58163.27}
  //doc["X"]=(Xm_cal);
  //doc["Y"]=(Ym_cal);
  //doc["Z"]=(Zm_cal);
  

  Serial.print("{\"X\":");
  Serial.print(Xm_cal,10);
  Serial.print(", \"Y\":");
  Serial.print(Ym_cal,10);
  Serial.print(", \"Z\":");
  Serial.print(Zm_cal,10);
  Serial.print("}");  
  //serializeJson(doc, Serial);
  Serial.println(",");

  
  delay(10);
}
