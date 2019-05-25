"""
HOG特征描述子之提取描述子
"""

import cv2 as cv

src = cv.imread("images/test.png")
src = cv.resize(src, (72, 128))
print("shape of image: ", src.shape)

hog = cv.HOGDescriptor()
# 先变成灰度图像再进行描述子计算
gray = cv.cvtColor(src, cv.COLOR_BGR2GRAY)
des = hog.compute(gray, winStride=(8, 8), padding=(0, 0))
print("提取的描述子数量：", len(des))
print("描述子：")
print(des)

cv.waitKey(0)
cv.destroyAllWindows()