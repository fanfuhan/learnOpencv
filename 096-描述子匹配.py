"""
描述子匹配
"""

import cv2 as cv

box = cv.imread("images/box.png")
box_in_scene = cv.imread("images/box_in_scene.png")
cv.imshow("box", box)
cv.imshow("box_in_scene", box_in_scene)

# 创建ORB特征检测器
orb = cv.ORB_create()

# 得到特征关键点和描述子
kp1, des1 = orb.detectAndCompute(box, None)
kp2, des2 = orb.detectAndCompute(box_in_scene, None)

# 暴力匹配
bf = cv.BFMatcher(cv.NORM_HAMMING, crossCheck=True)
matchers = bf.match(des1, des2)

# 绘制匹配
matchers = sorted(matchers, key=lambda x: x.distance)
result = cv.drawMatches(box, kp1, box_in_scene, kp2, matchers[:15], None)
cv.imshow("orb-match", result)

cv.waitKey(0)
cv.destroyAllWindows()