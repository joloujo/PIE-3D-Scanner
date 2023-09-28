/* 
This project creates a 3D scanner using an IR distance sensor and two servos.
A plot of a scanned letter, "E," is then created using the data collected by the sensor.
*/

#include <Servo.h>

// sets inital values for the sensor and its scaled output
int sensorValue = 0;  // value read from the sensor
int outputValue = 0;  // value of scaled sensor output

// assign pins for the sensor and the two servos
int sensor_pin = A0; // assigns the sensor to pin A0
int tilt_pin = 10; // assigns the tilting servo to pin 10
int pan_pin = 11; // assigns the panning servo to pin 11

// sets max and min values for the tilting servo
int min_tilt = 80; // sets min value for tilting servo
int max_tilt = 145; // sets max value for tilting servo

//sets the max and min values for the panning servo
int min_pan = 65; // sets min value for panning servo
int max_pan = 115; // sets max value for panning servo

// creates servo objects
Servo tilt_servo;  // create servo object to control the tilting servo
Servo pan_servo; // create servo object to control the panning servo

// The setup loop handles important set up components like the pin modes and serial monitor.
void setup() {
  long baudRate = 9600; // initialize serial communications at 9600 bps:      
  Serial.begin(baudRate); // start the serial port
  pinMode(sensor_pin, INPUT); // Sets sensor_pin to be an input.
  pinMode(tilt_pin, OUTPUT); // Sets tilt_pin to be an output.  
  pinMode(pan_pin, OUTPUT); // Sets pan_pin to be an output.  
  tilt_servo.attach(tilt_pin); // attaches the servo on pin 10 to the servo object
  pan_servo.attach(pan_pin); // attaches the servo on pin 11 to the servo object

  tilt_servo.write(max_tilt+10); // sets starting position of the tilting servo
  delay(500); // waits for the servo to move to the starting position
}

// defines how to complete a single scan
int single_scan(int angle) {
  pan_servo.write(angle); // tell servo to go to position in variable 'angle'
  delay(500); // waits for the servo to move to the position

  int min = 1000; // sets the initial value that the sensor value will be compared to while filtering out data

  // filters out any spikes by finding the smallest reading from 100 readings and setting that as the sensor value for that point
  for (int i = 0; i < 100; i++) {
    int sensorValue = analogRead(sensor_pin);
    if (sensorValue < min) {
      min = sensorValue;
    }
  }

  // scales the sensor value just determined by mapping it onto a smaller scale
  int outputValue = map(min, 0, 1023, 0, 255);

  // returns the filtered and scaled output value from the sensor
  return outputValue;
}

// The void loop will have our main code that loops over and over repeatedly 
void loop() {
  // creates a loop that moves the tilt servo from its max to its min tilt in increments of -4; during this loop, the pan servo moves back and forth in increments of 2, all while retrieving filtered and scaled data from the sensor and printing it.
  for (int tilt = max_tilt; tilt >= min_tilt; tilt -= 4) { // loop that moves the tilt servo from its max to its min tilt in increments of -4
    tilt_servo.write(tilt);
    delay(500); // wait for the servo to move to position

    for (int pan = min_pan; pan <= max_pan; pan += 2) { // loop that moves the pan servo from its min to its max tilt in increments of 2 and scans using the sensor.
      outputValue = single_scan(pan); // sets the output value to the filtered and scanned sensor data

      // print the results of the sensor and two servos to the Serial Monitor:
      Serial.print(outputValue);
      Serial.print(",");
      Serial.print(pan);
      Serial.print(",");
      Serial.println(tilt);
    }

    tilt_servo.write(tilt-2); // moves the tilt servo
    delay(500); // wait for the servo to move to position

    for (int pan = max_pan; pan >= min_pan; pan -= 2) { // goes from 180 degrees to 0 degrees
      outputValue = single_scan(pan); // sets the output value to the filtered and scanned sensor data

      // print the results of the sensor and two servos to the Serial Monitor:
      Serial.print(outputValue);
      Serial.print(",");
      Serial.print(pan);
      Serial.print(",");
      Serial.println(tilt);
    }
  }

  Serial.println("break"); // prints "break" to the serial monitor so we know that it has exited the loop
}    
