# import necesary libraries
import numpy as np
import matplotlib.pyplot as plt
import serial

# import transform function from other file
from transform_scan import transform_scan

# setup values for serial port 
port = "COM4" # CHANGE TO MATCH ARDUINO COM PORT
baudrate = 9600

# start serial connection
serialPort = serial.Serial(port, baudrate, timeout=1)
serialPort.flush()

# initialize numpy array for the scanned points
points = np.zeros([0, 3])

# define function to convert from sensor reading to inches based on calibration data.
def toInches(value: int):
  inches = 284.093 / (-22.7874 + value) + 8.7055
  return inches

# repeat until loop broken
while True:
  # read data from serial connection
  lineOfData = serialPort.readline().decode()

  # if data was received 
  if len(lineOfData) > 0:
    # split data into array
    data = lineOfData.split(",")

    # if a break was sent, the scan is done
    if "break" in data[0]:
      break
    
    # if not broken, there's data
    # convert the data to integers
    outputValue = int(data[0])
    pan_value = int(data[1])
    tilt_value = int(data[2])

    # get the distance from the sensor reading
    distance = toInches(outputValue)

    # convert the angles from degrees to radians
    pan_angle = np.deg2rad(pan_value-90)
    tilt_angle = np.deg2rad(tilt_value-110)

    # transform the scan from sphrical to cartesian coordinates
    (x, y, z) = transform_scan(distance, tilt_angle, pan_angle)

    # add the point to the list of points
    points = np.vstack((points, [x, y, z]))
    print(points)

# when the scan is done save the plot
with open('scan1.npy', 'wb') as f:
  np.save(f, points)

# close the serial connection
serialPort.close()