#!/usr/bin/env pybricks-micropython

from pybricks import ev3brick as brick
from pybricks.ev3devices import (Motor, TouchSensor, ColorSensor,
                                 InfraredSensor, UltrasonicSensor, GyroSensor)
from pybricks.parameters import (Port, Stop, Direction, Button, Color,
                                 SoundFile, ImageFile, Align)
from pybricks.tools import print, wait, StopWatch
from pybricks.robotics import DriveBase

# Write your program here
def main():
    brick.sound.beep()
    medium_motor1 = Motor(Port.A)
    medium_motor2 = Motor(Port.B)
    touch_backward = TouchSensor(Port.S1)
    touch_forward = TouchSensor(Port.S2)

    while True:
        if touch_forward.pressed():
            medium_motor1.run(1500)
            medium_motor2.run(1500)
        elif touch_backward.pressed():
            medium_motor1.run(-1500)
            medium_motor2.run(-1500)
        else:
            medium_motor1.stop()
            medium_motor2.stop()



main()