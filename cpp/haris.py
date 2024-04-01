import cv2
import numpy as np
from matplotlib import pyplot as plt


def my_harris(img_dir,window_size,k,threshold):

    img = cv2.imread(img_dir)
    gray = np.float32(cv2.cvtColor(img,cv2.COLOR_BGR2GRAY))

    img_gaussian = cv2.GaussianBlur(gray,(3,3),0)

    # Check if the image is exists
    if img is None:
        print('Invalid image:' + img_dir)
        return None
    else:
        print('Image successfully read...')
        
    height = img.shape[0]   #.shape[0] outputs height 
    width = img.shape[1]    #.shape[1] outputs width .shape[2] outputs color channels of image
    matrix_R = np.zeros((height,width))
    
    #   Step 1 - Calculate the x e y image derivatives (dx e dy)
    dx = cv2.convertScaleAbs(cv2.Sobel(img_gaussian, cv2.CV_64F, 1, 0, ksize=3))
    dy = cv2.convertScaleAbs(cv2.Sobel(img_gaussian, cv2.CV_64F, 0, 1, ksize=3))
    # dy, dx = np.gradient(gray)
    
    dx = np.uint16(dx)
    dy = np.uint16(dy)
    #   Step 2 - Calculate product and second derivatives (dx2, dy2 e dxy)
    dx2=np.square(dx)
    dy2=np.square(dy)
    dxy=dx*dy
    
    dx2 = cv2.GaussianBlur(dx2,(3,3),0)
    dy2 = cv2.GaussianBlur(dy2,(3,3),0)
    dxy = cv2.GaussianBlur(dxy,(3,3),0)
    
    plt.subplot(2, 3, 1)
    plt.title("Original")
    plt.xticks([]), plt.yticks([])
    plt.imshow(img, cmap='gray')
    
    plt.subplot(2, 3, 2)
    plt.title("Ix")
    plt.imshow(dx, cmap='gray')
    plt.xticks([]), plt.yticks([])
    
    plt.subplot(2, 3, 3)
    plt.title("Iy")
    plt.imshow(dy, cmap='gray')
    plt.xticks([]), plt.yticks([])
    
    
    plt.subplot(2, 3, 4)
    plt.title("Ixx")
    plt.imshow(dx2, cmap='gray')
    plt.xticks([]), plt.yticks([])
    
    plt.subplot(2, 3, 5)
    plt.title("Iyy")
    plt.imshow(dy2, cmap='gray')
    plt.xticks([]), plt.yticks([])
    
    plt.subplot(2, 3, 6)
    plt.title("Ixy")
    plt.imshow(dxy, cmap='gray')
    plt.xticks([]), plt.yticks([])
    plt.savefig('f2.png')
    plt.show()
    exit(0)
    offset = int( window_size / 2 )
    #   Step 3 - Calcular a soma dos produtos das derivadas para cada pixel (Sx2, Sy2 e Sxy)
    print ("Finding Corners...")
    for y in range(offset, height-offset):
        for x in range(offset, width-offset):
            Sx2 = np.sum(dx2[y-offset:y+1+offset, x-offset:x+1+offset])
            Sy2 = np.sum(dy2[y-offset:y+1+offset, x-offset:x+1+offset])
            Sxy = np.sum(dxy[y-offset:y+1+offset, x-offset:x+1+offset])

            #   Step 4 - Define the matrix H(x,y)=[[Sx2,Sxy],[Sxy,Sy2]]
            H = np.array([[Sx2,Sxy],[Sxy,Sy2]])

            #   Step 5 - Calculate the response function ( R=det(H)-k(Trace(H))^2 )
            det=np.linalg.det(H)
            tr=np.matrix.trace(H)
            R=det-k*(tr**2)
            matrix_R[y-offset, x-offset]=R
    
    #   Step 6 - Apply a threshold
    cv2.normalize(matrix_R, matrix_R, 0, 1, cv2.NORM_MINMAX)
    for y in range(offset, height-offset):
        for x in range(offset, width-offset):
            value=matrix_R[y, x]
            if value>threshold:
                # cornerList.append([x, y, value])
                cv2.circle(img,(x,y),3,(0,255,0))
                
    # cv2.imwrite("%s_threshold_%s.png"%(img_dir[5:-4],threshold), img)
    plt.figure("Manually implemented Harris detector")
    plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB)), plt.title("Manually implemented Harris detector")
    plt.xticks([]), plt.yticks([])
    plt.savefig('My_harris_detector-thresh_%s.png'%(threshold), bbox_inches='tight')
    plt.show()

my_harris("plane.bmp", 3, 0.04, 0.8) # Change this path to one that will lead to your image