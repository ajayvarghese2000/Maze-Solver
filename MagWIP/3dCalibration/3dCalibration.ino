#include <Wire.h>
#include <LSM303.h>
LSM303 compass;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();
  //Serial.println("Magnetometer Uncalibrated (Units in Nanotesla)");
  
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
float Xm_print, Ym_print, Zm_print;

Xm_print = compass.m.x*(100000.0/1100.0); // Gain X [LSB/Gauss] for selected sensor input field range (1.3 in these case)
Ym_print = compass.m.y*(100000.0/1100.0); // Gain Y [LSB/Gauss] for selected sensor input field range
Zm_print = compass.m.z*(100000.0/980.0 );  // Gain Z [LSB/Gauss] for selected sensor input field range

Serial.println(Xm_print, 10); Serial.println(Ym_print, 10); Serial.println(Zm_print, 10);

delay(50);
}
