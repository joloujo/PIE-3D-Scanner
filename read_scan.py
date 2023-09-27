import numpy as np

with open('scan1.npy', 'rb') as f:
    points = np.load(f)

print(points)