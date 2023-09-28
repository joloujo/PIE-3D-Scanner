import numpy as np
import matplotlib.pyplot as plt

with open('scan1.npy', 'rb') as f:
    arr = np.load(f)

# Create an empty list
filter_arr = []

# go through each element in arr
for element in arr:
  # if the element is higher than 42, set the value to True, otherwise False:
  if 17 < element[0] < 19 and element[2] < 2.5:
    filter_arr.append(True)
  else:
    filter_arr.append(False)

final_arr = arr[filter_arr]

print(final_arr)


fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter(final_arr[:, 0], final_arr[:, 1], final_arr[:, 2])

ax.set_xlim3d([13, 27])
ax.set_ylim3d([-10, 8])
ax.set_zlim3d([-12, 2])

plt.show()