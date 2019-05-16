"""
SIFT特征提取之关键点提取
"""

import cv2 as cv

src = cv.imread("images/test4.jpg")
cv.imshow("input", src)

sift = cv.xfeatures2d.SIFT_create()
kps = sift.detect(src)
# opencv4 python版中好像没有 cv.drawKeypoints()
# result = cv.drawKeypoints(src, kps, None, (0, 255, 0), cv.DrawMatchesFlags_DEFAULT)
result = src.copy()
for marker in kps:
    result = cv.drawMarker(src, tuple(int(i) for i in marker.pt), color=(0, 255, 0))

cv.imshow("result", result)
cv.waitKey(0)
cv.destroyAllWindows()
