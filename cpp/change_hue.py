import cv2
import matplotlib.pyplot as plt
import numpy as np
 
plt.figure(figsize=(40,40))
 
for i in range(0,8):
     
    hsv_image = np.zeros((50, 50, 3), dtype=np.uint8)
 
    # saturation is increased by 35 for every image and hue and value is set to some middle value like 120.
    sat = i * 35
    hsv_image[:,:,:] = ( 120, sat, 120)
     
    # Converting hsv to rgb for displaying in matplotlib
    rgb_image = cv2.cvtColor(hsv_image, cv2.COLOR_HSV2RGB)
     
    # Display the image
    ax = plt.subplot(1, 8, i+1)
    plt.imshow(rgb_image)
    plt.axis('off')  # this will not show the axis
    ax.set_title('S={}'.format(sat), fontdict={'fontsize': 45})