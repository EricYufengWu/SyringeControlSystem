# Linear Syringe System for Controlling Soft Robot Actuators

![Demo](https://github.com/EricYufengWu/PneumaticSyringeSystem/blob/master/Documentation/Demo.gif)

## General Info

This repository hosts code, PCB designs, and other results from my undergraduate independent research course. This research is supervised by Professor Chris Rogers at Tufts University.

The goal of the research is to develop a low-cost, modular pneumatic system that controls soft actuators using a linear actuator and a medical syringe. If time allows, I will also try to perform a well-rounded comparison between my new system and traditional controlling methods like [this one.](https://softroboticstoolkit.com/book/control-board)

Scroll down for pictures, demos, and complete building instructions.

Questions? Email yufeng.wu@tufts.edu and I will try to get back to you ASAP. I would also love to hear feedback or suggestions on how I can improve the current system.

Note: This README is still under construction! I just wrapped up my spring semester and will try to have the complete building instruction ready in the next two weeks. 

## Images & Demos

Check out my presentation video on Youtube: https://youtu.be/lQ8lNfzFreA

![Rendering 01](https://github.com/EricYufengWu/PneumaticSyringeSystem/blob/master/Documentation/05_04_20_Render02.JPG)
![Rendering 02](https://github.com/EricYufengWu/PneumaticSyringeSystem/blob/master/Documentation/05_04_20_Render01.JPG)
![Working Demo](https://github.com/EricYufengWu/PneumaticSyringeSystem/blob/master/Documentation/v3_2_units.jpeg)

## Building Instructions

### 1. BOM & Links
Click [here](https://docs.google.com/spreadsheets/d/1QlE3OmNmio2WvQ-pDKSaTucrADuNShoU5-5D75yimro/edit?usp=sharing) for the complete bill of materials.

Click [here](https://grabcad.com/) for the 3D-printed components in STL, STEP, and SolidWorks format.

You can also view the 3D-model online through [here](https://autode.sk/2SUinZA)

Get the latest Gerber package and original KiCAD files (with custom libraries) under the "PCB" folder.

### 2. 3D-Printing the Parts

### 3. The Custom PCB

### 4. Assembly Instructions

A PDF Assembly instruction can be found [here](https://github.com/EricYufengWu/PneumaticSyringeSystem/blob/master/Documentation/Assembly.pdf) 

### 5. The Code
Please see "Arduino_TeensyLC" for some simple demo code I wrote for the system.

BEFORE YOU PROCEED: Please read the next section about the limitations of the current system as well as things to keep in mind during its operation. 

Keep in mind that although the system is considered safe to operate, the stability of the system has not been so thoroughly tested. This mostly means that certain components might accidentally malfunction or get heated up. 

### 6. Limitations and Precautions
Although I2C protocol is capable of connecting more than 100 slaves at once, for the current version, it is recommended that you do not connect more than 8 units to the same master unit at the same time. This is due to the current rating of the wires used in the design. Future development will focus on how to tackle this issue.