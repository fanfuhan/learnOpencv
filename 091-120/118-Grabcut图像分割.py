"""
Grabcut图像分割
"""

import cv2 as cv
import numpy as np

src = cv.imread("../images/master.jpg")
cv.imshow("input", src)

mask = np.zeros(src.shape[:2], dtype=np.uint8)
rect = (53, 12, 356, 622)
iterCount = 5
bgdmodel = np.zeros((1, 13 * iterCount), np.float64)
fgdmodel = np.zeros((1, 13 * iterCount), np.float64)

cv.grabCut(src, mask, rect, bgdmodel, fgdmodel, iterCount, mode=cv.GC_INIT_WITH_RECT)
mask2 = np.where((mask == 1) + (mask == 3), 255, 0).astype('uint8')
print(mask2.shape)
result = cv.bitwise_and(src, src, mask=mask2)

cv.imshow("result", result)
cv.waitKey(0)
cv.destroyAllWindows()
