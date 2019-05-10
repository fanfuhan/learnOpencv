"""
对象检测(HAAR特征介绍)
"""
import cv2 as cv

capture = cv.VideoCapture(0)
face_detector = cv.CascadeClassifier(cv.data.haarcascades + "haarcascade_frontalface_alt.xml")
smile_detector = cv.CascadeClassifier(cv.data.haarcascades + "haarcascade_smile.xml")

while True:
    ret, image = capture.read()
    if ret is True:
        faces = face_detector.detectMultiScale(image, scaleFactor=1.05, minNeighbors=3,
                                               minSize=(30, 30), maxSize=(300, 300))
        for x, y, width, height in faces:
            cv.rectangle(image, (x, y), (x + width, y + height), (0, 0, 255), 2, cv.LINE_8, 0)
        roi = image[y:y + height, x:x + width]
        smiles = smile_detector.detectMultiScale(roi, scaleFactor=1.7, minNeighbors=3,
                                                 minSize=(15, 15), maxSize=(100, 100))
        for sx, sy, sw, sh in smiles:
            cv.rectangle(roi, (sx, sy), (sx + sw, sy + sh), (0, 255, 0), 1)

        cv.imshow("faces", image)
        c = cv.waitKey(50)
        if c == 27:
            break
    else:
        break

cv.destroyAllWindows()
