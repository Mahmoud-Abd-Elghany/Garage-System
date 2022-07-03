# Garage-System

## Description
This is a demo for a garage system to regulate the movements of cars upon entering or exiting the garage.
By using an ECU to control the gates of the garage to not allow more cars inside the garage more than the empty slots available.
The ECU automatically close the gate in 2 cases: 
  1- The Car passes the second PIR.
  2- The Car doesn't pass the second PIR before predetermined time runs open which starts upon opening the gate or activating first PIR.

## Components
Microcontroller, PIR Sensors, Servo Motors, LCD

## Drivers
Timer (PMW & Counter), LCD, DIO.

## Simulation
Proteus 8++
![alt text](image.jpg)
