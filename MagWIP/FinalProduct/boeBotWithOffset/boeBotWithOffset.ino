#include <Wire.h>
#include <LSM303.h>
#include <math.h>
LSM303 compass;

void setup()
{
Serial.begin(9600);
Wire.begin();
compass.init();
compass.enableDefault();
}

float out = 0;
float Pi = 3.14159;
float command = 90;
float strt=0;
float ends=0;



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
  
  

  // Calculate the angle of the vector y,x
  float head = (atan2(Ym_cal,Xm_cal) * 180) / Pi;

  // Normalize to 0-360
  if (head < 0) {
    head = 360 + head;
  }
  if(command != 0){
    strt = head;
    ends = strt + command;
    if(ends>360){
      ends=ends-360;
    }
    else if (ends < 0){
      ends=ends+360;
    }
    command = 0;
  }
  
  
  if(fabs(ends-head)<3){
    Serial.println("Booooooooooooooooop");
  }
  
  
  Serial.println(ends);
  Serial.println(head);
  delay(5);
}
