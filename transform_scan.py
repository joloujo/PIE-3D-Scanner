# import necesary libraries
import numpy as np

def transform_scan(distance: float, tilt_angle: float, pan_angle: float):
    # Create a point the measured distance away from the sensor in the sensors frame
    point = np.array([distance, 0, 0, 1])

    # transform from the sensor frame to the tilt servo frame 
    distance_to_tilt_servo = np.array([
        [1, 0, 0, 0.75],
        [0, 1, 0,    0],
        [0, 0, 1,    0],
        [0, 0, 0,    1]
        ])
    point = np.dot(distance_to_tilt_servo, point)

    # rotate the point by the tilt servo angle 
    tilt_servo_rotation = np.array([
        [np.cos(tilt_angle), 0, -np.sin(tilt_angle), 0],
        [                 0, 1,                   0, 0],
        [np.sin(tilt_angle), 0,  np.cos(tilt_angle), 0],
        [                 0, 0,                   0, 1]
        ])
    point = np.dot(tilt_servo_rotation, point)

    # transform from the tilt servo frame to the pan servo frame 
    tilt_servo_to_pan_servo = np.array([
        [1, 0, 0, 0],
        [0, 1, 0, 0],
        [0, 0, 1, -2.25],
        [0, 0, 0, 1]
        ])
    point = np.dot(tilt_servo_to_pan_servo, point)

    # rotate the point by the pan servo angle 
    pan_servo_rotation = np.array([
        [np.cos(pan_angle), -np.sin(pan_angle), 0, 0],
        [np.sin(pan_angle),  np.cos(pan_angle), 0, 0],
        [                 0,                 0, 1, 0],
        [                 0,                 0, 0, 1]
        ])
    point = np.dot(pan_servo_rotation, point)

    # transform from the pan servo to the ground frame 
    pan_servo_to_ground = np.array([
        [1, 0, 0, 0],
        [0, 1, 0, 0],
        [0, 0, 1, -2.25],
        [0, 0, 0, 1]
        ])
    point = np.dot(pan_servo_to_ground, point)

    x, y, z = point[0:3]
    return (x, y, z)

print(transform_scan(1, 1, 1))