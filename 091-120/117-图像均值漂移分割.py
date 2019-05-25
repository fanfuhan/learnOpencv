"""
图像均值漂移分割
"""

import cv2 as cv

src = cv.imread("images/yuan_test.png")
cv.imshow("input", src)
dst = cv.pyrMeanShiftFiltering(src, 25, 40, None, 2)
cv.imshow("result", dst)

cv.waitKey(0)
cv.destroyAllWindows()