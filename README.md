# Arduino - Temperature and Humidity detector

This is a simple project to create a device to measure temperature and humidity.

PIECES:

- Arduino Uno (other microcontrollers are good as well)
- LCD display
- active buzzer
- ultrasonic sensor
- DHT22 (or others) temperature and humidity sensor
- potentiometer (to adjust LCD brightness)

The wiring image shows how to wire the pieces together. 

![alt text](https://github.com/pitbull36/ard_temp_humidity/blob/master/wiring_temp_hum_DHT22.png?raw=true)

The device waits for input, as something is approaching the ultrasonic sensor at a distance <= 35 cm,
you will hear a double beep and on the LCD screen it will appear the temperature and humidity of the room 
until the ultrasonic sensor become free again.

The code is in the .ino file.
