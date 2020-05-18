# Syringe Control System for Soft Robot Actuators

![Demo](https://github.com/EricYufengWu/PneumaticSyringeSystem/blob/master/Documentation/Demo.gif)

## General Info

This repository hosts code, PCB designs, and other results from my undergraduate independent research course. This research is supervised by Professor Chris Rogers at Tufts University.

The goal of the research is to develop a low-cost, modular pneumatic system that controls soft actuators using a linear actuator and a medical syringe. If time allows, I will also try to perform a well-rounded comparison between my new system and traditional controlling methods like [this one.](https://softroboticstoolkit.com/book/control-board). For now, the system is named "Syringe Control System", or SCS in short.

I would like to thank Professor Chris Rogers, Professor Brandon Stafford, and many other people from [Tufts Center for Engineering Education and Outreach](https://ceeo.tufts.edu/) and [Tufts Nolop FAST Facility](https://nolop.org/) for making this project possible.

Scroll down for pictures, demos, and complete building instructions.

Questions? Email yufeng.wu@tufts.edu and I will try to get back to you ASAP. I would also love to hear feedback or suggestions on how I can improve the current system.

## Images & Demos

Check out my presentation video on Youtube: https://youtu.be/lQ8lNfzFreA

![Rendering 01](https://github.com/EricYufengWu/PneumaticSyringeSystem/blob/master/Documentation/05_16_20_Render03.JPG)
![Rendering 02](https://github.com/EricYufengWu/PneumaticSyringeSystem/blob/master/Documentation/05_04_20_Render02.JPG)
![Working Demo](https://github.com/EricYufengWu/PneumaticSyringeSystem/blob/master/Documentation/v3_2_units.jpeg)

## BOM & Links

Click [here](https://docs.google.com/spreadsheets/d/1QlE3OmNmio2WvQ-pDKSaTucrADuNShoU5-5D75yimro/edit?usp=sharing) for the complete bill of materials.

Click [here](https://grabcad.com/library/linear-syringe-system-for-controlling-soft-robot-actuators-1/details?folder_id=8379164) for the 3D-printed components in STL, STEP, and SolidWorks format.

You can also view the 3D-model online through [here](https://autode.sk/2SUinZA)

Get the latest Gerber package and original KiCAD files (with custom libraries) under the "PCB" folder.

## Building Instructions

A full manual, including instructions on BOM, 3D-printing, ordering PCB, mechanical assembly, coding, and operation, can be found [here](https://github.com/EricYufengWu/PneumaticSyringeSystem/blob/master/Documentation/SCS_Manual_v3.1.pdf) in PDF. 

## Using The Code

Please see "Arduino_TeensyLC" for some simple demo code I wrote for the system.

Follow the instruction on the [PJRC Website](https://www.pjrc.com/teensy/teensyLC.html) to set up your Teensy LC. Similarly, go to the [Arduino Website](https://www.arduino.cc/en/Guide/ArduinoNano) if you are setting up an Arduino Nano as the Master Unit.

Upload "mid_master_TC" to the Teensy LC on each of your units. For every new unit, you will need to change the I2C slave address on line 41. If you are not sure what address values you can use, check out [this helpful list](https://learn.adafruit.com/i2c-addresses/the-list) form Adafruit. In the code, you can also tune the gain constants for the closed-loop control system in line 32 - 38. They have not been fine tuned yet, but for now they seem to work with little to no problem. If you end up finding better constant values, please do not hesitate to share it with me!

After you upload the code to a control unit, the unit should be operational in manual mode, i.e. after connecting the unit to 12V motor and 5V logic power, you should be able to control the unit using the built'in buttons. You should also be able to view the current pressure and positional data if you access the Teensy LC using a serial manitor on your computer.

Upload "top_master_nano.ino" to your arduino Nano as the master unit. You can use the serial input to send command to and get data from any designated unit in the I2C bus.

For more detailed instruciton, please refer to the instruction manual.

BEFORE YOU PROCEED: Please read the next section about the limitations of the SCS as well as things to keep in mind during its operation. 


## Limitations and Precautions
I2C protocol is capable of connecting more than 100 slaves at once. However, for the current version, it is recommended that you do not connect more than 8 units to the same master unit at the same time. This is due to the current rating of the wires used in the design. Future development will focus on how to tackle this issue.

Although the system uses Sparkfun's Qwiic system to communicaate with the units via I2C, it is currently NOT compatible with other boards on the Qwiic system: The SCS uses 5V on its logic line to power the Teensy LC, whereas the real Qwiic system uses 3.3V to power the sensors. Connecting other 3.3V sensors to the SCS system could permanently damage your sensors!

Keep in mind that although the system proves to be safe to operate, the stability of the system has not been so thoroughly tested. This mostly means that certain components might accidentally malfunction or get heated up. 