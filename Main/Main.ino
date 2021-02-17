/* Main Code for Maze Solver

    A module addon for the Boe-Bot using ultrasonic and IR distance sensors to auto solve a maze

    Created On : 13/02/21

    Last Updated : 13/02/21

    Change Log:
*/

#include <Servo.h> // Library to Control the Motors


#include <hcsr04.h> // Incluing Library for Easy Ultrasonic Sernsor Ativation

/*
    To use the ultrasonic library you first need to define an US entity

        HCSR04 <Name of Variable>(Trigger Pin, Echo Pin, MinRange, MaxRange);
    
    Then you have access to subfunctions, to get the distance in millimeters do:
        
        <Name of Variable>.distanceInMillimeters();
    
    This will retun the distance in mm as an int if its over the max range it will output -1

*/

#include <SharpIR.h> // Library to Contol the IR Sensor

/*
    To use the IR library you first need to define an ir entity

        SharpIR  <Name of Variable>(sensorModel, sensorPin);
            e.g SharpIR IRF(SharpIR::GP2Y0A41SK0F, A0);
    
    Then you have access to subfunctions, to get the distance in millimeters do:
        
        <Name of Variable>.getDistance();
    
    This will retun the distance in cm as an int. NOTE : This auto applys a 20ms delay between reads

*/

#include <Wire.h> // For I2C
#include <math.h> // For Maths

// All for mag acc
#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>



// Connected Devices
//      Define the pins of any connected devices below

// Creating the Left Ultrasonic Sensor entity (Trigger Pin, Echo Pin, MinRange, MaxRange)
HCSR04 USL(2, 3, 10, 70); // Range doesn't need to bigger than this as the robot is boput 15cm wide and the maze 22cm

// Creating the right Ultrasonic Sensor entity
HCSR04 USR(4, 5, 10, 70);

// Creating the front IR Sensor entity on A0
SharpIR IRF(SharpIR::GP2Y0A41SK0F, A0);

// Creating the accell and mag A4 and A5 
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(51234);
Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

// Creating the Servo entitys - Will be attached to the pins 11 and 10 in setup()
Servo servoleft;
Servo servoright;

// Adding The LED's
int led = 12; // Red
int led2 = 13; // Green

// Pause Switch
int Pasue = 9;

// Run Switchs
int R1 = 8;
int R2 = 7;
int R3 = 6;



// Global Variables
//      Define any global variables you need here

// Array of 100 chars to store the directions the robot takes on each runs
struct runs{
    char turns[100];  // e.g 
    bool valid;     //      turns[100] = {'l', 'r', 'r', 'l','e', 'e', 'e'}
    int t_loc;      // l/r for left/right and e for end/null
}; // Valid gets set to true after the run is complete and t-loc is the location of the T junction in the run array

runs run[3];

// Run selector deictates what run the robot is doing. Will be controlled by an external 3-pole switch attached to the uno
boolean runselect[2] = {false,false};



void setup(){

    // Starting the Serial Port
    Serial.begin(9600);
    
    // Resetting the stored runs
    clearruns();

    // Attaching pins to the servo
    servoleft.attach(10);
    servoright.attach(11);

    // Starting the mag accl
    accel.begin();
    mag.begin();

}

void loop() {

    solvemaze(); // does nothing right now

    // Printing sensor values to simply test
	Serial.println(boebot_sensor(2));

}

// Takes an avarage of 15 values from the sensor to combat inaccuracies
// Takes the sensor reqired and retuns the avrage value in mm
int boebot_sensor(int sensor){
    
    // Variable to store the total (Gets reset on each call)
    int total = 0;
    
    // Switch statment to pick which sensor to ping
    // 0 = Front; 1 = Left; 2 = Right; anyother will return an error code of -1 
    switch (sensor)
    {
    case 0: // Front Sensor
        
        // Summing up 15 values
        for (int i = 0; i < 15; i++)
        {
            // Pulsing the US Sensor and adding it to the current total
            total = IRF.getDistance(false) + total;
            delay(5); // Delay to not onverload the module
        }

        // Getting the average
        total = total/15;

        // Returning the ans
        return total*10;
        break;
    
    case 1: // Left Sensor

        // Summing up 15 values
        for (int i = 0; i < 15; i++)
        {
            // Pulsing the US Sensor and adding it to the current total
            total = USL.distanceInMillimeters() + total;
            delay(5); // Delay to not onverload the module
        }

        // Getting the average
        total = total/15;

        // Returning the ans
        return total;
        break;
    
    case 2: // Right Sensor
        
        // Summing up 15 values
        for (int i = 0; i < 15; i++)
        {  
            // Pulsing the US Sensor and adding it to the current total
            total = USR.distanceInMillimeters() + total;
            delay(5); // Delay to not onverload the module
        }

        // Getting the average
        total = total/15;

        // Returning the ans
        return total;
        break;
    
    default:
        return -1;
        break;
    }

}

// Moves the boebot forward
void boebot_move_forwards(){
    servoleft.writeMicroseconds(1300);
    servoright.writeMicroseconds(1700);
}

// Moves the boebot backward
void boebot_move_backwards(){
    servoleft.writeMicroseconds(1700);
    servoright.writeMicroseconds(1300);
}

// Turns the boebot left then stops
void boebot_turn_left(){
    servoleft.writeMicroseconds(1400);
    servoright.writeMicroseconds(1400);
    delay(375);
    boebot_stop();
}

// Turns the boebot right
void boebot_turn_right(){
    servoleft.writeMicroseconds(1590);
    servoright.writeMicroseconds(1590);
    delay(380);
    boebot_stop();
    
}

// Stops the Boebot
void boebot_stop(){
    servoleft.writeMicroseconds(1500);
    servoright.writeMicroseconds(1500);
}

// An overall function that will run the solving
void solvemaze(){

}
  
// Function to set-up default vales and clear any stored data in the 3 runs
void clearruns(){
    for (int i = 0; i < 3; i++) // for each run
    {
        run[i].t_loc = -1; // Setting an inaccesable value for the T-locaction
        run[i].valid = false; // Setting the run to be invalid
        
        for (int j = 0; j < 100; j++) // for each 100 turns in each run
        {
            run[i].turns[j] = 'e'; // Setting all the turns to be invalid to start with
        }
        
    }
    
}
