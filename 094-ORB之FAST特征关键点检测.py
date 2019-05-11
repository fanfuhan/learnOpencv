"""
ORB之FAST特征关键点检测
"""

import cv2 as cv

src = cv.imread("images/test4.jpg")
cv.imshow("input", src)

orb = cv.ORB().create()
kps = orb.detect(src)
# opencv4 python版中好像没有 cv.drawKeypoints()
# result = cv.drawKeypoints(src, kps, None, (0, 255, 0), cv.DrawMatchesFlags_DEFAULT)
result = src.copy()
for marker in kps:
    result = cv.drawMarker(src, tuple(int(i) for i in marker.pt), color=(0, 255, 0))

cv.imshow("result", result)
cv.waitKey(0)
cv.destroyAllWindows()
