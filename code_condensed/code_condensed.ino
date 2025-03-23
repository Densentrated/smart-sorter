#include <Arduino.h>
#include <Stepper.h>
#include "Adafruit_HX711.h"

// SWAP PINS TO CORRECT NUMBERS LATER
#define BASE_IN_1 1
#define BASE_IN_2 2
#define BASE_IN_3 3
#define BASE_IN_4 4

#define ROLLERA_IN_1 5
#define ROLLERA_IN_2 6
#define ROLLERA_IN_3 7
#define ROLLERA_IN_4 8

#define ROLLER_B_IN_1 9
#define ROLLER_B_IN_2 10
#define ROLLER_B_IN_3 11
#define ROLLER_B_IN_4 12

#define LOADCELL_DOUT 13
#define LOADCELL_SCK 14

// Defining Pins

// This constant is the same for all numbers because they are all the same motor
const int STEPS_PER_REV = 2048;

// Defining the motor that rotates the base
Stepper baseMotor(STEPS_PER_REV, BASE_IN_1, BASE_IN_2, BASE_IN_3, BASE_IN_4);

// Defining the two motors that will rotate (These are implemented as one motor as in hardware they will be hooked to the same pins and will do the same actions)
Stepper rollerA(STEPS_PER_REV, ROLLERA_IN_1, ROLLERA_IN_2, ROLLERA_IN_3, ROLLERA_IN_4);
Stepper rollerB(STEPS_PER_REV, ROLLER_B_IN_1, ROLLER_B_IN_2, ROLLER_B_IN_3, ROLLER_B_IN_4);

// Defining the weight sensor that will get the value of the weight sensor
Adafruit_HX711 loadCell(LOADCELL_DOUT, LOADCELL_SCK);

void setup()
{
    // Starting up weight cell
    loadCell.begin();
}

void loop()
{
  // Load Cell Will Need Calibration at Some Point
  
  // Waits 5 Seconds
  // Gets Weight From Weight Sensor
  // Waits 1 Second
  // If Weight is over threshold rotate and push object to left
  // If Weight is over threshold rotate and push object to right
  // Stop Process

}