# 4-Way Intersection Traffic Light Control System

A simulated traffic light control system for a four-way intersection using the PIC16F877A microcontroller. The system controls traffic lights in four directions and displays countdown timers using 7-segment displays.

## Project Overview

This project simulates a traffic light control system for a four-way intersection: North, East, South, and West.

The system uses the PIC16F877A microcontroller to control red, yellow, and green traffic lights in a predefined sequence. Each direction has a countdown timer displayed on a 7-segment display, showing the remaining time before the traffic light changes.

The project was developed using C programming language and simulated with PICSimLab.

## Features

- Controls traffic lights in four directions.
- Supports Red, Yellow, and Green light states.
- Automatically switches traffic lights according to predefined timing.
- Displays countdown timers for all four directions.
- Uses 7-segment displays for real-time countdown display.
- Applies Multiplexing technique to control multiple display digits.

## Hardware Components

- PIC16F877A Microcontroller
- 12 LEDs (Red, Yellow, and Green)
- 4 sets of 4-digit 7-Segment Displays

## Software & Tools

- C Programming Language
- mikroC PRO for PIC
- PICSimLab for circuit simulation

## System Operation

1. The North direction starts with a green light.
2. The green light changes to yellow after the configured time.
3. The system switches to the next direction.
4. Other directions remain red while one direction has the green or yellow light.
5. Countdown timers update continuously on the 7-segment displays.
6. The process repeats continuously for all four directions.

## Project Images

Simulation images will be added here.

## Learning Outcomes

- Understanding PIC16F877A microcontroller programming.
- Practicing C programming for embedded systems.
- Learning digital input/output control.
- Understanding 7-segment display operation.
- Applying Multiplexing techniques.
- Using PICSimLab to simulate and test embedded systems.

## Author

**Pakorn Kaewmanee**

Computer Engineering Student

Rajamangala University of Technology Phra Nakhon

## Project Category

Embedded Systems | Microcontroller | Traffic Light Control

