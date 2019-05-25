"""
KMeans进行数据分类
"""

import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt

X = np.random.randint(25, 50, (25, 2))
Y = np.random.randint(60, 85, (25, 2))
pts = np.vstack((X, Y))

# 初始化数据
data = np.float32(pts)
print(data.shape)

# 定义停止条件
criteria = (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, 10, 1.0)

# kmeans分类
ret, label, center = cv.kmeans(data, 2, None, criteria, 2, cv.KMEANS_RANDOM_CENTERS)
print(label.shape)
print(center)

# 获取不同标签的点
A = data[label.ravel() == 0]
B = data[label.ravel() == 1]

# plot the data
plt.scatter(A[:, 0], A[:, 1])
plt.scatter(B[:, 0], B[:, 1], c='r')
plt.scatter(center[:, 0], center[:, 1], s=80, c='y', marker='s')
plt.xlabel("x1")
plt.ylabel("x2")
plt.show()

cv.waitKey(0)
cv.destroyAllWindows()