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

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9;  // Analog output pin that the LED is attached to

int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // value output to the PWM (analog out)

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

// Create variables necessary for timing components. These variables are unsigned long types becuase they are going to become very large very quickly. 
unsigned long previousMillis = 0;  // Create the previousMillis variable that will store last time LED was updated. Set it intially to 0.
unsigned long previousMillis1 = 0;  // Create the previousMillis1 variable that will store last time LED was updated. Set it intially to 0.
//const long interval = 3000;  // Create the interval variable. This will the interval at which the LED blinks (milliseconds).
//const long interval2 = 250; // Create the interval2 variable. This will the interval at which the LED blinks (milliseconds). This interval specifies a shorter time than the one above.

void setup() {
  // initialize serial communications at 9600 bps:
  // start the serial port
  long baudRate = 9600;       // NOTE1: The baudRate for sending & receiving programs must match
  Serial.begin(baudRate);     // NOTE2: Set the baudRate to 115200 for faster communication
  myservo.attach(11);          // attaches the servo on pin 11 to the servo object
}

void loop() {
    // servo sweep 
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(pos);              // tell servo to go to position in variable 'pos'

          delay(500);

          // read the analog in value:
          sensorValue = analogRead(analogInPin);
          // map it to the range of the analog out:
          outputValue = map(sensorValue, 0, 1023, 0, 255);
          // change the analog out value:
          analogWrite(analogOutPin, outputValue);

          // print the results to the Serial Monitor:
          //Serial.print("output = ");
          Serial.println(outputValue);
        }

      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
          myservo.write(pos);              // tell servo to go to position in variable 'pos'

          delay(500);

          // read the analog in value:
          sensorValue = analogRead(analogInPin);
          // map it to the range of the analog out:
          outputValue = map(sensorValue, 0, 1023, 0, 255);
          // change the analog out value:
          analogWrite(analogOutPin, outputValue);

          // print the results to the Serial Monitor:
          //Serial.print("output = ");
          Serial.println(outputValue);      
        }
  }    
