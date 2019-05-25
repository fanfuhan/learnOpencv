"""
基于描述子匹配的已知对象定位
"""

import cv2 as cv
import numpy as np

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

# 发现匹配
maxdist = 0
goodMatches = []
for m in matchers:
    maxdist = max(maxdist, m.distance)
for m in matchers:
    if m.distance < 0.4 * maxdist:
        goodMatches.append(m)


# 找到本地化对象
obj_pts = np.float32([kp1[m.queryIdx].pt for m in goodMatches]).reshape(-1, 1, 2)
scene_pts = np.float32([kp2[m.trainIdx].pt for m in goodMatches]).reshape(-1, 1, 2)

# findHomography 函数是计算变换矩阵
# 参数cv.RANSAC / cv.RHO是使用RANSAC算法寻找一个最佳单应性矩阵H，即返回值M
# 返回值：M 为变换矩阵，mask是掩模
M, mask = cv.findHomography(obj_pts, scene_pts, cv.RANSAC)

# 获取box的图像尺寸
h, w, _ = box.shape
# obj_corners是图像box的四个顶点
obj_corners = np.float32([[0, 0], [w, 0], [w, h], [0, h]]).reshape(-1, 1, 2)
# 计算变换后的四个顶点坐标位置,透视变换
scene_corners = cv.perspectiveTransform(obj_corners, M)

# 根据四个顶点坐标位置在img2图像画出变换后的边框
box_in_scene = cv.polylines(box_in_scene, [np.int32(scene_corners)], True, (0, 0, 255), 3, cv.LINE_AA)

# 绘制
result = cv.drawMatches(box, kp1, box_in_scene, kp2, goodMatches, None)
cv.imshow("orb-match", result)

cv.waitKey(0)
cv.destroyAllWindows()
