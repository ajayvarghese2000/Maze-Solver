/* Main Code for Maze Solver

    A module addon for the Boe-Bot using ultrasonic and IR distance sensors to auto solve a maze

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

#include <Wire.h> // For I2C
#include <math.h> // For Maths

// All for mag acc
#include <LSM303.h>
#include <math.h>



// Connected Devices
//      Define the pins of any connected devices below

// Creating the Left Ultrasonic Sensor entity (Trigger Pin, Echo Pin, MinRange, MaxRange)
HCSR04 USL(2, 3, 10, 60); // Range doesn't need to bigger than this as the robot is about 15cm wide and the maze 22cm

// Creating the right Ultrasonic Sensor entity
HCSR04 USR(4, 5, 10, 60);

// Creating the accell and mag A4 and A5 
LSM303 compass;

// Creating the Servo entitys - Will be attached to the pins 11 and 10 in setup()
Servo servoleft;
Servo servoright;

// Adding The LED's
int led = 12; // Red
int led2 = 13; // Green

// Pause Switch
int Pause = 9;

// Run Switchs Default High, Low when Active
int R1 = 8;
int R2 = 7;
int R3 = 6;



// Global Variables
//      Define any global variables you need here
// Array of 100 chars to store the directions the robot takes on each runs
struct runs{
    char turns[100];  // e.g 
    bool valid;      //      turns[100] = {'l', 'r', 'r', 'l','e', 'e', 'e'}
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
    Wire.begin();
    compass.init();
    compass.enableDefault();

    // Setting Up The Run Switch
    pinMode(R1,INPUT_PULLUP);
    pinMode(R2,INPUT_PULLUP);
    pinMode(R3,INPUT_PULLUP);

    // Setting Up The Pause Switch
    pinMode(Pause, INPUT);

    // Setting up the LED's
    pinMode(led, OUTPUT);
    pinMode(led2, OUTPUT);

}

void loop() {
    //solvemaze();
    Serial.println(GetCurrentAngle());
}

// Takes an avarage of 15 values from the sensor to combat inaccuracies
// Takes the sensor reqired and retuns the avrage value in mm
// 0 = front, 1 = left, 2 = right
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
            total = IRSensorDistance() + total;
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
    servoleft.writeMicroseconds(1362);
    servoright.writeMicroseconds(1700);
    return;
}

// Moves the boebot backward
void boebot_move_backwards(){
    servoleft.writeMicroseconds(1700);
    servoright.writeMicroseconds(1300);
    return;
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
    return;
}

// An overall function that will run the solving
void solvemaze(){
    /*if ( runselect[1] == false && runselect[0] == true) // If the runsel == 01 i.e run 1
    {
        lefthandrule();
    }
    else{
      lefthandrule();
    }*/

    lefthandrule();
    return;
    
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

// When run it will update the global runselect variable and print which run is active
void updateRunSelect(){

    // Gets the state of the pins by doing a digital read
    int R1_s = digitalRead(R1);
    int R2_s = digitalRead(R2);
    int R3_s = digitalRead(R3);

    if (R1_s == 0)
    {
        runselect[0] = true;
        runselect[1] = false;
        Serial.println("RUN 1");
    }
    else if (R2_s == 0)
    {
        runselect[0] = false;
        runselect[1] = true;
        Serial.println("RUN 2");
    }
    else if (R3_s == 0)
    {
        runselect[0] = true;
        runselect[1] = true;
        Serial.println("RUN 3");
    }
    else
    {
        runselect[0] = false;
        runselect[1] = false;
        Serial.println("ERROR : RUN SWITCH ISSUE");
    } 
}

// Checks if the pause switch is high and returns true/false
boolean PauseActive(){
    
    // Checks the pause state
    int Pause_S = digitalRead(Pause);

    // Returns a true/false depending on the pause switch.
    switch (Pause_S)
    {
    case 1:
        Serial.println("PAUSED");
        boebot_stop();
        return true;
        break;
    
    default:
        return false;
        break;
    }
}

// Function to run the left hand rule.
void lefthandrule(){
    if (IsFrontBlocked() == true)
    {
        int node = AvailableTurns();
        Serial.println(node);
        LightLED(node);
    }
    else
    {
        return;
    }
}
// Checks if the front is blocked. If the front is blocked it returns TRUE
boolean IsFrontBlocked(){

    // Checks if something is blocking the front sensor
    if(boebot_sensor(0) > 70)
    {
        boebot_move_forwards();
        return false;
    }
    else // Default action is to stop, so it fails to safe
    {
        boebot_stop();
        return true;
    }    
}

// Returns the distance sensed by the IR module in CM
int IRSensorDistance(){
    float volts = analogRead(A0)*0.0048828125;
    int distance = 13*pow(volts, -1);
    return distance;
}

// Function the checks what turns are avaliable and returns a number
// 0 = no turns, 1 = left turn only, 2 = right trun only, 3 = T junction
int AvailableTurns(){
    int left = boebot_sensor(1); // get the left distance
    int right = boebot_sensor(2); // get the right distance

    if (left == -1 && right == -1) // T junction
    {
        return 3;
    }
    else if (0 < left && left <= 50 && right == -1) // only right
    {
        return 2;
    }
    else if (0 < right && right <= 50 && left == -1) // only left
    {
        return 1;
    }
    else
    {
        return 0; // dead end
    }
}

// Lights up the LED's depending on an input
// 0 = no light, 1 = Left LED, 2 = Right LED, 3 = Both LED
void LightLED(int node){
    switch (node)
    {
    case 0:
        digitalWrite(led, LOW);
        digitalWrite(led2, LOW);
        break;
    case 1:
        digitalWrite(led, LOW);
        digitalWrite(led2, HIGH);
        break;
    case 2:
        digitalWrite(led, HIGH);
        digitalWrite(led2, LOW);
        break;
    case 3:
        digitalWrite(led, HIGH);
        digitalWrite(led2, HIGH);
        break;
    default:
        break;
    }
}

// Uses the magnatometer to return the current angle in degrees it is facing.
// Remember angles are measured counter-clockwise
double GetCurrentAngle(){
    compass.read();
    double Xm_off, Ym_off, Zm_off, Xm_cal, Ym_cal, Zm_cal, ang, rot;

    Xm_off = compass.m.x*(100000.0/1100.0) - 7024.10400864; //X-axis combined bias (Non calibrated data - bias)
    Ym_off = compass.m.y*(100000.0/1100.0) + 5300.20058655; //Y-axis combined bias (Default: substracting bias)
    Zm_off = compass.m.z*(100000.0/980.0 ) - 6550.05656025; //Z-axis combined bias

    Xm_cal =  0.86131059*Xm_off + 0.01089249*Ym_off + 0.01893214*Zm_off; //X-axis correction for combined scale factors (Default: positive factors)
    Ym_cal =  0.01089249*Xm_off + 0.80200574*Ym_off + -0.01610820*Zm_off; //Y-axis correction for combined scale factors
    Zm_cal =  0.01893214*Xm_off + -0.01610820*Ym_off + 0.88873569*Zm_off; //Z-axis correction for combined scale factors

    ang = atan2(Ym_cal,Xm_cal);
    rot = ((ang/M_PI)*180);

    if(ang < 0)
    {
        rot = (180+rot)+180;
    }

    return rot;

}