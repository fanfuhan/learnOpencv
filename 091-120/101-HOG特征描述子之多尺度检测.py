"""
HOG特征描述子之多尺度检测
"""

import cv2 as cv

src = cv.imread("images/pedestrian_02.png")
hog = cv.HOGDescriptor()
hog.setSVMDetector(cv.HOGDescriptor_getDefaultPeopleDetector())
# detect people in image
(rects, weights) = hog.detectMultiScale(src, winStride=(4, 4),
                                        padding=(8, 8), scale=1.5,
                                        useMeanshiftGrouping=False)

for (x, y, w, h) in rects:
    cv.rectangle(src, (x, y), (x + w, y + h), (0, 255, 0), 2)

cv.imshow("hog-detector scale=1.5", src)

cv.waitKey(0)
cv.destroyAllWindows()
