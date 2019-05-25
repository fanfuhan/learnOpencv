"""
使用HOG进行对象检测
"""

import cv2 as cv
import numpy as np

image = cv.imread("images/elec_watch/test/scene_01.jpg")
test_image = cv.resize(image, (0, 0), fx=0.2, fy=0.2)
cv.imshow("input", test_image)

gray = cv.cvtColor(test_image, cv.COLOR_BGR2GRAY)
print(test_image.shape)
h, w = test_image.shape[:2]
svm = cv.ml.SVM_load("svm_data.dat")
sum_x = 0
sum_y = 0
count = 0
hog = cv.HOGDescriptor()

for row in range(64, h-64, 4):
    for col in range(32, w-32, 4):
        win_roi = gray[row-64:row+64,col-32:col+32]
        hog_desc = hog.compute(win_roi, winStride=(8, 8), padding=(0, 0))
        one_fv = np.zeros([len(hog_desc)], dtype=np.float32)
        for i in range(len(hog_desc)):
            one_fv[i] = hog_desc[i][0]
        one_fv = np.reshape(one_fv, [-1, len(hog_desc)])
        result = svm.predict(one_fv)[1]
        if result[0][0] > 0:
            sum_x += (col-32)
            sum_y += (row-64)
            count += 1

x = sum_x // count
y = sum_y // count
cv.rectangle(test_image, (x, y), (x+64, y+128), (0, 0, 255), 2, 8, 0)
cv.imshow("result", test_image)

cv.waitKey(0)
cv.destroyAllWindows()
