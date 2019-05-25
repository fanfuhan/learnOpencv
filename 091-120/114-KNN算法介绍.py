"""
KNN算法介绍
"""

import cv2 as cv
import numpy as np

# 读取数据
img = cv.imread("images/digits.png")
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
cells = [np.hsplit(row, 100) for row in np.vsplit(gray, 50)]
x = np.array(cells)

# 创建训练与测试数据
train = x[:, :50].reshape(-1, 400).astype(np.float32)
test = x[:, 50:100].reshape(-1, 400).astype(np.float32)
k = np.arange(10)
train_labels = np.repeat(k,250)[:, np.newaxis]
test_labels = train_labels.copy()

# 训练KNN
knn = cv.ml.KNearest_create()
knn.train(train, cv.ml.ROW_SAMPLE, train_labels)
ret, result, neighbours, dist = knn.findNearest(test, k=5)

# 计算准确率
matches = result == test_labels
correct = np.count_nonzero(matches)
acc = correct * 100.0 / result.size
print("预测准确率：", acc)

