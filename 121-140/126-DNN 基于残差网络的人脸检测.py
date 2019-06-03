"""
DNN 基于残差网络的人脸检测
"""

import cv2 as cv

model_bin ="opencv_face_detector_uint8.pb"
config_text = "opencv_face_detector.pbtxt"

# load tensorflow model
net = cv.dnn.readNetFromTensorflow(model_bin, config=config_text)
image = cv.imread("images/persons.jpg")
h = image.shape[0]
w = image.shape[1]

# 人脸检测
blobImage = cv.dnn.blobFromImage(image, 1.0, (300, 300), (104.0, 177.0, 123.0), False, False)
net.setInput(blobImage)
cvOut = net.forward()

# Put efficiency information.
t, _ = net.getPerfProfile()
label = 'Inference time: %.2f ms' % (t * 1000.0 / cv.getTickFrequency())
cv.putText(image, label, (0, 15), cv.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0))

# 绘制检测矩形
for detection in cvOut[0,0,:,:]:
    score = float(detection[2])
    objIndex = int(detection[1])
    if score > 0.5:
        left = detection[3]*w
        top = detection[4]*h
        right = detection[5]*w
        bottom = detection[6]*h

        # 绘制
        cv.rectangle(image, (int(left), int(top)), (int(right), int(bottom)), (255, 0, 0), thickness=2)
        cv.putText(image, "score:%.2f"%score, (int(left), int(top)), cv.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 1)

cv.imshow('face-detection-demo', image)

cv.waitKey(0)
cv.destroyAllWindows()