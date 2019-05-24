"""
利用KMeans图像分割进行主色彩提取
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

# 生成主色彩条形卡片
card = np.zeros((50, w, 3), dtype=np.uint8)
clusters = np.zeros([4], dtype=np.int32)
for i in range(len(label)):
    clusters[label[i][0]] += 1
# 计算各类别像素的比率
clusters = np.float32(clusters) / float(h*w)
center = np.int32(center)
x_offset = 0
for c in range(num_clusters):
    dx = np.int(clusters[c] * w)
    b = center[c][0]
    g = center[c][1]
    r = center[c][2]
    cv.rectangle(card, (x_offset, 0), (x_offset+dx, 50),
                 (int(b),int(g),int(r)), -1)
    x_offset += dx

cv.imshow("color table", card)

cv.waitKey(0)
cv.destroyAllWindows()