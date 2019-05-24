"""
利用KMeans图像分割进行背景替换
"""

import cv2 as cv
import numpy as np

image = cv.imread('images/toux.jpg')
cv.imshow("input", image)
h, w, ch = image.shape

# 构建图像数据
data = image.reshape((-1, 3))
data = np.float32(data)

# 图像分割
criteria = (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, 10, 1.0)
num_clusters = 4
ret, label, center = cv.kmeans(data, num_clusters, None, criteria, num_clusters, cv.KMEANS_RANDOM_CENTERS)

# 生成mask区域
index = label[0][0]
center = np.uint8(center)
color = center[0]
mask = np.zeros((h, w), dtype=np.uint8)
label = np.reshape(label, (h, w))
mask[label == index] = 255

# 高斯模糊
se = cv.getStructuringElement(cv.MORPH_RECT, (3, 3))
cv.dilate(mask, se, mask)
mask = cv.GaussianBlur(mask, (5, 5), 0)
cv.imshow("background-mask", mask)

# 背景替换
result = np.zeros((h, w, ch), dtype=np.uint8)
for row in range(h):
    for col in range(w):
        w1 = mask[row, col] / 255.0
        b, g, r = image[row, col]
        b = w1 * 255 + b * (1.0 - w1)
        g = w1 * 0 + g * (1.0 - w1)
        r = w1 * 255 + r * (1.0 - w1)
        result[row, col] = (b, g, r)
cv.imshow("background-substitution", result)

cv.waitKey(0)
cv.destroyAllWindows()
