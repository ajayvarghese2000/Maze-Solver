/* Main Code for Maze Solver

    A module addon for the Boe-Bot using ultrasonic and IR distance sensors to auto solve a maze

    Created On : 13/02/21

    Last Updated : 13/02/21

    Change Log:

        13/02/21 -> Made the Code - Ajay

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


// Creating the Left Ultrasonic Sensor entity (Trigger Pin, Echo Pin, MinRange, MaxRange)
HCSR04 USL(2, 3, 10, 70); // Range doesn't need to bigger than this as the robot is boput 15cm wide and the maze 22cm

// Creating the right Ultrasonic Sensor entity
HCSR04 USR(4, 5, 10, 70);


void setup(){

    // Starting the Serial Port
    Serial.begin(9600);
}

void loop() {

    // Output the distance in mm
	Serial.println(boebot_sensor(2));

}

// Takes an avarage of 15 values from the sensor to combat inaccuracies
// Takes the sensor reqired and retuns the avrage value in mm
int boebot_sensor(int sensor){
    
    int total = 0;
    
    switch (sensor)
    {
    case 0: // Front Sensor
        /* code */
        break;
    
    case 1: // Left Sensor

        // Summing up 15 values
        for (int i = 0; i < 15; i++)
        {
            total = USL.distanceInMillimeters() + total;
            delay(5);
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
            total = USR.distanceInMillimeters() + total;
            delay(5);
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