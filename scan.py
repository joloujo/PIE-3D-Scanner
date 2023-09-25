import math
import serial

# setup values for serial port 
port = "COM4" # CHANGE TO MATCH ARDUINO COM PORT
baudrate = 9600

# start serial connection
serialPort = serial.Serial(port, baudrate, timeout=1)

def toCentimeters(value: int):
  centimeters = 82.947 * math.exp(-0.028 * value)
  return centimeters

while True:
  # read data from serial connection
  lineOfData = serialPort.readline().decode()

  # if data was received 
  if len(lineOfData) > 0:
    # convert the data from a string to an integer
    data = int(lineOfData)

    distance = toCentimeters(data)

    # print the data
    print(str(distance) + "cm")