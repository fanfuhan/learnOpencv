"""
特征提取之关键点检测(GFTTDetector)
"""

import cv2 as cv

image = cv.imread("images/test4.jpg")
cv.imshow("input", image)

# 创建GFTT特征检测器
gftt = cv.GFTTDetector_create(100, 0.01, 1, 3, False, 0.04)
kp1 = gftt.detect(image, None)
for marker in kp1:
    result = cv.drawMarker(image, tuple(int(i) for i in marker.pt), color=(0, 255, 0))

cv.imshow("GFTT-Keypoint-Detect", result)
cv.waitKey(0)
cv.destroyAllWindows()
