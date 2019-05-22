"""
AKAZE特征与描述子
"""

import cv2 as cv

box = cv.imread("images/box.png")
box_in_scene = cv.imread("images/box_in_scene.png")

# 创建AKAZE特征检测器
akaze = cv.AKAZE_create()

# 得到特征关键点和描述子
kp1, des1 = akaze.detectAndCompute(box, None)
kp2, des2 = akaze.detectAndCompute(box_in_scene, None)

# 暴力匹配
bf = cv.BFMatcher(cv.NORM_HAMMING, crossCheck=True)
matchers = bf.match(des1, des2)

# 绘制匹配
result = cv.drawMatches(box, kp1, box_in_scene, kp2, matchers, None)
cv.imshow("orb-match", result)

cv.waitKey(0)
cv.destroyAllWindows()