import cv2 as C

# Đọc ảnh
image_path = "image01.png"
image = C.imread(image_path)
# Nhập vào vị trí của điểm ảnh (pixel)
x = 100
y = 50
# Hiển thị dấu cộng tại vị trí của pixel
C.drawMarker(image, (x, y), (0, 255, 0), C.MARKER_CROSS, markerSize=10, thickness=2)

# Hiển thị thông tin tọa độ phía trên dấu cộng
text = f"Toa do: ({x}, {y})"
C.putText(image, text, (x, y - 10), C.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 1)

# Hiển thị ảnh
C.imshow("Image with Cross Marker", image)
C.waitKey(0)
C.destroyAllWindows()
