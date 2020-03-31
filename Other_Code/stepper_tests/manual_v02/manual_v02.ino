/*
 * Simple demo, should work with any driver board
 *
 * Connect STEP, DIR as indicated
 *
 * Copyright (C)2015-2017 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>
#include "BasicStepperDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 60 

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1                                                                                             

// All the wires needed for full functionality
#define DIR 8
#define STEP 9
//Uncomment line to use enable/disable functionality
//#define SLEEP 13

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

//Uncomment line to use enable/disable functionality
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

//buttons definition
#define forw_pin 2
#define back_pin 3

void setup() {
    stepper.begin(RPM, MICROSTEPS);
    // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
    // stepper.setEnableActiveState(LOW);

    pinMode(forw_pin, INPUT);
    pinMode(back_pin, INPUT);
}

void loop() {
  
    // energize coils - the motor will hold position
    // stepper.enable();
  
    /*
     * Moving motor one full revolution using the degree notation
     */
//    if(digitalRead(forw_pin) == HIGH){
//      stepper.rotate(90);
//      delay(1000);
//      stepper.rotate(-90);
//      delay(1000);
//    }
    

    /*
     * Moving motor to original position using steps
     */
    if (digitalRead(forw_pin) == HIGH){
      stepper.rotate(90);
    }
    else if (digitalRead(back_pin) == HIGH){
      stepper.rotate(-90);
    }
    

    // pause and allow the motor to be moved by hand
    // stepper.disable();

    //delay(5000);
}
