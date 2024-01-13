#!/usr/bin/env python
# coding: utf-8

# In[ ]:


import numpy as np
import cv2
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
from tensorflow.keras.utils import to_categorical

# Assume you have lists 'rgb_frames', 'imu_data', and 'labels' containing your RGB frames, IMU data, and corresponding labels

# Step 1: Resize RGB frames
resized_frames = [cv2.resize(frame, (224, 224)) for frame in rgb_frames]

# Step 2: Convert RGB frames to NumPy array
rgb_data = np.array(resized_frames)

# Step 3: Normalize RGB data (optional but often beneficial for training)
rgb_data = rgb_data / 255.0

# Step 4: Encode labels
label_encoder = LabelEncoder()
encoded_labels = label_encoder.fit_transform(labels)

# Step 5: Convert labels to one-hot encoding
one_hot_labels = to_categorical(encoded_labels)

# Step 6: Split the data into training, validation, and test sets
rgb_train, rgb_temp, imu_train, imu_temp, labels_train, labels_temp = train_test_split(
    rgb_data, imu_data, one_hot_labels, test_size=0.3, random_state=42
)

rgb_val, rgb_test, imu_val, imu_test, labels_val, labels_test = train_test_split(
    rgb_temp, imu_temp, labels_temp, test_size=0.5, random_state=42
)

