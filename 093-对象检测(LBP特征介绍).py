"""
对象检测(LBP特征介绍)
"""

import cv2 as cv

capture = cv.VideoCapture(0)
detector = cv.CascadeClassifier("D:/software/opencv4/build/etc/lbpcascades/lbpcascade_frontalface_improved.xml")

while True:
    ret, image = capture.read()
    if not ret:
        break

    faces = detector.detectMultiScale(image, scaleFactor=1.05,
                                      minNeighbors=1, minSize=(30, 30), maxSize=(300, 300))
    for x, y, width, height in faces:
        cv.rectangle(image, (x, y), (x + width, y + height), (0, 0, 255),
                     2, cv.LINE_8, 0)
    cv.imshow("faces", image)

    c = cv.waitKey(50)
    if c == 27:
        break

cv.destroyAllWindows()
