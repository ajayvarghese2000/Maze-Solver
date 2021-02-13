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
    Serial.begin(9600);
}

void loop() {

    // Output the distance in mm
	Serial.println(USL.distanceInMillimeters());



    delay(250);
}