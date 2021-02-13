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

// Connected Devices
//      Define the pins of any connected devices below

// Creating the Left Ultrasonic Sensor entity (Trigger Pin, Echo Pin, MinRange, MaxRange)
HCSR04 USL(2, 3, 10, 70); // Range doesn't need to bigger than this as the robot is boput 15cm wide and the maze 22cm

// Creating the right Ultrasonic Sensor entity
HCSR04 USR(4, 5, 10, 70);

// Creating the front IR Sensor entity on A0
SharpIR IRF(SharpIR::GP2Y0A41SK0F, A0);


void setup(){

    // Starting the Serial Port
    Serial.begin(9600);
}

void loop() {

	Serial.println(boebot_sensor(0));

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

}

// Moves the boebot backward
void boebot_move_backwards(){
    
}

// Turns the boebot left
void boebot_turn_left(){
    
}

// Turns the boebot right
void boebot_turn_right(){
    
}

// An overall function that will run the solving
void solvemaze(){

}