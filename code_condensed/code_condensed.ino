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
    Serial.begin(115200);
    while (!Serial) {
      delay(10);
    }

    loadCell.begin();

    Serial.println("Tareing....");
    for (uint8_t t=0; t<3; t++) {
      loadCell.tareA(loadCell.readChannelRaw(CHAN_A_GAIN_128));
      loadCell.tareA(loadCell.readChannelRaw(CHAN_A_GAIN_128));
      loadCell.tareB(loadCell.readChannelRaw(CHAN_B_GAIN_32));
      loadCell.tareB(loadCell.readChannelRaw(CHAN_B_GAIN_32));
    }
}

void loop()
{
  // Load Cell Will Need Calibration at Some Point
  // Waits 5 Seconds
  delay(5000);
  // Gets Weight From Weight Sensor (prints weight)
  int32_t weight = loadCell.readChannelBlocking(CHAN_A_GAIN_128);
  Serial.print("Channel A (Gain 128): ");
  Serial.println(weight);
  // Waits 1 Second
  delay(1000);
  // If Weight is over/equal to threshold rotate and push object to left, and rotates obejct to center
  // If Weight is under threshold rotate and push object to right
  int32_t threshold = 12;
  if (weight >= threshold) {
    baseMotor.step(STEPS_PER_REV / 2);
    rollerA.step(STEPS_PER_REV * 4);
    rollerB.step(STEPS_PER_REV * 4);
    baseMotor.step(-STEPS_PER_REV / 2);
  } else {
    baseMotor.step(-STEPS_PER_REV / 2);
    rollerA.step(STEPS_PER_REV * 4);;
    rollerB.step(STEPS_PER_REV * 4);
    baseMotor.step(STEPS_PER_REV / 2);
  }
  // Stop Process

}