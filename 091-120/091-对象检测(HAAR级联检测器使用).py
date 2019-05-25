"""
对象检测(HAAR级联检测器使用)
"""

import cv2 as cv

capture = cv.VideoCapture(0)
detector = cv.CascadeClassifier(cv.data.haarcascades + "haarcascade_frontalface_alt.xml")

while True:
    ret, image = capture.read()
    if not ret:
        break

    faces = detector.detectMultiScale(image, scaleFactor=1.05,
                                      minNeighbors=1, minSize=(30, 30), maxSize=(200, 200))
    for x, y, width, height in faces:
        cv.rectangle(image, (x, y), (x + width, y + height), (0, 0, 255),
                     2, cv.LINE_8, 0)
    cv.imshow("faces", image)

    c = cv.waitKey(50)
    if c == 27:
        break

cv.destroyAllWindows()
