/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground through 220 ohm resistor

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInOutSerial
*/

#include <Servo.h>

int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // value output to the PWM (analog out)

int sensor_pin = A0;
int tilt_pin = 10;
int pan_pin = 11;

int min_tilt = 75;
int max_tilt = 150;

int min_pan = 45;
int max_pan = 135;

Servo tilt_servo;  // create servo object to control a servo
Servo pan_servo;

void setup() {
  // initialize serial communications at 9600 bps:
  // start the serial port
  long baudRate = 9600;       // NOTE1: The baudRate for sending & receiving programs must match
  Serial.begin(baudRate);     // NOTE2: Set the baudRate to 115200 for faster communication
  tilt_servo.attach(tilt_pin);          // attaches the servo on pin 11 to the servo object
  pan_servo.attach(pan_pin); 
}

int single_scan(int angle) {
  pan_servo.write(angle);              // tell servo to go to position in variable 'pos'
  delay(500);

  int min = 1000;

  for (int i = 0; i < 100; i++) {
    int sensorValue = analogRead(sensor_pin);
    if (sensorValue < min) {
      min = sensorValue;
    }
  }

  int outputValue = map(min, 0, 1023, 0, 255);

  return outputValue;
}

void loop() {
  for (int tilt = max_tilt; tilt >= min_tilt; tilt -= 4) {
    tilt_servo.write(tilt);
    delay(500);

    for (int pan = min_pan; pan <= max_pan; pan += 2) { // goes from 0 degrees to 180 degrees
      outputValue = single_scan(pan);

      // print the results to the Serial Monitor:
      Serial.print(outputValue);
      Serial.print(",");
      Serial.print(pan);
      Serial.print(",");
      Serial.println(tilt);
    }

    tilt_servo.write(tilt-2);
    delay(500);

    for (int pan = max_pan; pan >= min_pan; pan -= 2) { // goes from 180 degrees to 0 degrees
      outputValue = single_scan(pan);

      // print the results to the Serial Monitor:
      Serial.print(outputValue);
      Serial.print(",");
      Serial.print(pan);
      Serial.print(",");
      Serial.println(tilt);
    }
  }
}    
