# import necesary libraries
import numpy as np
import matplotlib.pyplot as plt

# load the scan data
with open('scan1.npy', 'rb') as f:
    arr = np.load(f)

# Create an empty list
filter_arr = []

# go through each element in arr
for element in arr:
  # if the element is within the desired scan area, keep it:
  if 17 < element[0] < 19 and element[2] < 2.5:
    filter_arr.append(True)
  else:
    filter_arr.append(False)

# apply the filter array
final_arr = arr[filter_arr]

# plot the data with a matplotlib 3D scatter plot
fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter(final_arr[:, 0], final_arr[:, 1], final_arr[:, 2])

# make all of the axes equal so there is no distortion
ax.set_xlim3d([13, 27]) # type: ignore
ax.set_ylim3d([-10, 8]) # type: ignore
ax.set_zlim3d([-12, 2]) # type: ignore

# show the plot
plt.show()