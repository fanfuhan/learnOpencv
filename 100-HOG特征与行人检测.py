"""
HOG特征与行人检测
"""

import cv2 as cv

src = cv.imread("images/pedestrian.png")
hog = cv.HOGDescriptor()
hog.setSVMDetector(cv.HOGDescriptor_getDefaultPeopleDetector())
# detect people in image
(rects, weights) = hog.detectMultiScale(src, winStride=(4, 4),
                                        padding=(8, 8), scale=1.25,
                                        useMeanshiftGrouping=False)

for (x, y, w, h) in rects:
    cv.rectangle(src, (x, y), (x + w, y + h), (0, 255, 0), 2)

cv.imshow("hog-detector", src)

cv.waitKey(0)
cv.destroyAllWindows()
