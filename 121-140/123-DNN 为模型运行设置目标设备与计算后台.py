"""
DNN 为模型运行设置目标设备与计算后台
"""

import cv2 as cv
import numpy as np

bin_model = "bvlc_googlenet.caffemodel"
protxt = "bvlc_googlenet.prototxt"

# load names of classes
classes = None
with open("classification_classes_ILSVRC2012.txt", 'rt') as f:
    classes = f.read().rstrip('\n').split('\n')

# load CNN model
net = cv.dnn.readNetFromCaffe(protxt, bin_model)
net.setPreferableBackend(cv.dnn.DNN_BACKEND_OPENCV)
net.setPreferableTarget(cv.dnn.DNN_TARGET_CPU)

# read input data
image = cv.imread("images/airplane.jpg")
blob = cv.dnn.blobFromImage(image, 1.0, (224, 224), (104, 117, 123),
                            False, False)
result = np.copy(image)
cv.imshow("input", image)

# run a model
net.setInput(blob)
out = net.forward()

# get a class with a highest score
out = out.flatten()
classId = np.argmax(out)
confidence = out[classId]

# put efficiency information
t, _ = net.getPerfProfile()
label = 'Inference time: %.2f ms' % (t * 1000.0 / cv.getTickFrequency())
cv.putText(result, label, (0, 15), cv.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0))

# print predicted class
label = '%s : %.4f' % (classes[classId], confidence)
cv.putText(result, label, (50, 50), cv.FONT_HERSHEY_SIMPLEX, 0.75, (0, 0, 255), 2)
cv.imshow("googlenet-demo", result)

cv.waitKey(0)
cv.destroyAllWindows()