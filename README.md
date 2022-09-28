# Laser Cooler Temp Sensor
Temp sensor using Arduino for monitoring water cooler temp for those who don't have a chiller with temp sensor built in.

## Components

The following components were used in this build:
* Arduino Compatible UNO
* DS18B20 Submersible Temperature Sensor
* DS3132 RTC (Real Time Clock) Module
* 16x2 LCD Display
* 1 passive buzzer
* 1 Red and 1 Green LEDs
* 4 220Ohm resistors
* 1 4.7kohm resistor
* 1 Potentiometer
* Breadboard
* Various jumper wires to connect it together

## The Code
The code is in the folder above this file and contains the Arduino Sketch file.  Additional code will be added for a cross platform serial logger to add logging to PC, Mac and Linux machines - primary will be PC and Mac to start.  The data logging will log time stamps from the temperature sensor at the time on the arduino (hence the RTC) and create a CSV file for analysis.  Most users will not want or need this logging capability and thus can just use the build guide and code for just the sensor since it has a visual display of the temperature, green led for good temp, red led for bad temp and a buzzer alarm for bad temp.
