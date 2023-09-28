import numpy as np
import matplotlib.pyplot as plt
import serial

from transform_scan import transform_scan

# setup values for serial port 
port = "COM4" # CHANGE TO MATCH ARDUINO COM PORT
baudrate = 9600

# start serial connection
serialPort = serial.Serial(port, baudrate, timeout=1)
serialPort.flush()

points = np.zeros([0, 3])

def toInches(value: int):
  inches = 284.093 / (-22.7874 + value) + 8.7055
  return inches

while True:
  # read data from serial connection
  lineOfData = serialPort.readline().decode()

  # if data was received 
  if len(lineOfData) > 0:
    data = lineOfData.split(",")

    if "break" in data[0]:
      break
    
    outputValue = int(data[0])
    pan_value = int(data[1])
    tilt_value = int(data[2])

    distance = toInches(outputValue)

    # print the data
    # print(str(distance) + " inches at " + str(pan_value) + ", " + str(tilt_value))

    pan_angle = np.deg2rad(pan_value-90)
    tilt_angle = np.deg2rad(tilt_value-110)

    (x, y, z) = transform_scan(distance, tilt_angle, pan_angle)

    points = np.vstack((points, [x, y, z]))
    print(points)

with open('scan1.npy', 'wb') as f:
  np.save(f, points)

serialPort.close()