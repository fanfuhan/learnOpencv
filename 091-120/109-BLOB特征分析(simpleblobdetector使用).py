"""
BLOB特征分析(simpleblobdetector使用)
"""

import cv2 as cv

frame = cv.imread("images/zhifang_ball.png")
cv.imshow("input", frame)
gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
params = cv.SimpleBlobDetector_Params()

# change thresholds
params.minThreshold = 0
params.maxThreshold = 256

# filter by area
params.filterByArea = True
params.minArea = 100

# filter by circularity
params.filterByCircularity = True
params.minCircularity = 0.1

# Filter by Convexity
params.filterByConvexity = True
params.minConvexity = 0.5

# Filter by Inertia
params.filterByInertia = True
params.minInertiaRatio = 0.5

# 提取关键点
detector = cv.SimpleBlobDetector_create(params)
keypoints = detector.detect(gray)
for marker in keypoints:
    result = cv.drawMarker(frame, tuple(int(i) for i in marker.pt), color=(0, 255, 0))
cv.imshow("result", result)

cv.waitKey(0)
cv.destroyAllWindows()