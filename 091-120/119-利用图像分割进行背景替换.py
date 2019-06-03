"""
利用Grabcut图像分割进行背景替换
"""

import cv2 as cv
import numpy as np

src = cv.imread("../images/master.jpg")
h, w = src.shape[:2]
background = cv.imread("images/land.jpg")
background = cv.resize(background, (w, h))
cv.imshow("input", src)
cv.imshow("background", background)

# 分割，得到mask区域
h, w, ch = src.shape
mask = np.zeros(src.shape[:2], dtype=np.uint8)
rect = (53,12,w-100,h-12)
bgdmodel = np.zeros((1,65),np.float64)
fgdmodel = np.zeros((1,65),np.float64)
cv.grabCut(src,mask,rect,bgdmodel,fgdmodel,5,mode=cv.GC_INIT_WITH_RECT)
mask2 = np.where((mask==1) + (mask==3), 255, 0).astype('uint8')

# 高斯模糊
se = cv.getStructuringElement(cv.MORPH_RECT, (3, 3))
cv.dilate(mask2, se, mask2)
mask2 = cv.GaussianBlur(mask2, (5, 5), 0)
cv.imshow('background-mask',mask2)

# 虚化背景
background = cv.GaussianBlur(background, (0, 0), 15)

# 混合图像
result = np.zeros((h, w, ch), dtype=np.uint8)
for row in range(h):
    for col in range(w):
        w1 = mask2[row, col] / 255.0
        b, g, r = src[row, col]
        b1,g1,r1 = background[row, col]
        b = (1.0-w1) * b1 + b * w1
        g = (1.0-w1) * g1 + g * w1
        r = (1.0-w1) * r1 + r * w1
        result[row, col] = (b, g, r)

cv.imshow("result", result)
cv.waitKey(0)
cv.destroyAllWindows()