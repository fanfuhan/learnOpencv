"""
二维码检测与识别
"""

import cv2 as cv
import numpy as np

src = cv.imread("images/fanfan.jpg")
cv.imshow("image", src)
gray = cv.cvtColor(src, cv.COLOR_BGR2GRAY)
qrcoder = cv.QRCodeDetector()
codeinfo, points, straight_qrcode = qrcoder.detectAndDecode(gray)
print(points)
result = np.copy(src)
cv.drawContours(result, [np.int32(points)], 0, (0, 0, 255), 2)
print("qrcode : %s" % codeinfo)
cv.imshow("result", result)
code_roi = np.uint8(straight_qrcode)
cv.namedWindow("qrcode roi", cv.WINDOW_NORMAL)
cv.imshow("qrcode roi", code_roi)

cv.waitKey(0)
cv.destroyAllWindows()