"""
Brisk特征提取与描述子匹配
"""

import cv2 as cv

box = cv.imread("images/box.png")
box_in_scene = cv.imread("images/box_in_scene.png")

# 创建Brisk特征检测器
brisk = cv.BRISK_create()

# 得到特征关键点和描述子
kp1, des1 = brisk.detectAndCompute(box, None)
kp2, des2 = brisk.detectAndCompute(box_in_scene, None)

# 暴力匹配
bf = cv.BFMatcher(cv.NORM_HAMMING, crossCheck=True)
matchers = bf.match(des1, des2)

# 绘制匹配
result = cv.drawMatches(box, kp1, box_in_scene, kp2, matchers, None)
cv.imshow("brisk-match", result)

cv.waitKey(0)
cv.destroyAllWindows()