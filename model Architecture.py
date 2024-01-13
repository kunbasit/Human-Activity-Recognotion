#!/usr/bin/env python
# coding: utf-8

# In[49]:


from tensorflow.keras.models import Model
from tensorflow.keras.layers import Input, Conv2D, MaxPooling2D, LSTM, Dense, concatenate, Flatten, Dropout

# Assume 'num_additional_features' represents the number of additional features in the IMU data

# Input for RGB data
rgb_input = Input(shape=(224, 224, 3), name='rgb_input')
# Input for IMU data with additional features
imu_input = Input(shape=(sequence_length, num_imu_features + num_additional_features), name='imu_input')

# Stream 1: RGB stream
rgb_conv1 = Conv2D(64, (3, 3), activation='relu')(rgb_input)
rgb_pool1 = MaxPooling2D(pool_size=(2, 2))(rgb_conv1)
rgb_conv2 = Conv2D(128, (3, 3), activation='relu')(rgb_pool1)
rgb_pool2 = MaxPooling2D(pool_size=(2, 2))(rgb_conv2)
rgb_flatten = Flatten()(rgb_pool2)

# Stream 2: IMU stream with LSTM
imu_lstm = LSTM(64)(imu_input)

# Merge the streams
merged = concatenate([rgb_flatten, imu_lstm])
merged_dropout = Dropout(0.5)(merged)

# Fully connected layers
dense1 = Dense(128, activation='relu')(merged_dropout)
output = Dense(num_classes, activation='softmax', name='output')(dense1)

# Create the model
model = Model(inputs=[rgb_input, imu_input], outputs=output)

# Print the model summary
model.summary()


# print('X:', X, sep='\n')

# In[50]:


print('X:', X, sep='\n')


# In[51]:


print('y:', y, sep='\n', end='\n\n')


# In[52]:


print('intercept:', model.intercept_)


# In[53]:


print('coef:', model.coef_, end='\n\n')


# In[54]:


print('p_pred:', p_pred, sep='\n', end='\n\n')


# In[55]:


print('y_pred:', y_pred, end='\n\n')


# In[56]:


print('score_:', score_, end='\n\n')


# In[59]:


print('conf_m:', conf_m, sep='\n', end='\n\n')


# In[60]:


print('report:', report, sep='\n')


# In[ ]:





# In[ ]:




