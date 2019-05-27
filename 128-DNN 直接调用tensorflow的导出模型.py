"""
DNN 直接调用tensorflow的导出模型
"""

import cv2 as cv

inference_pb = "frozen_inference_graph.pb"
graph_text = "graph.pbtxt"

# load tensorflow model
net = cv.dnn.readNetFromTensorflow(inference_pb, graph_text)
image = cv.imread("images/dog_person_horse.jpg")
h = image.shape[0]
w = image.shape[1]

# 获得所有层名称与索引
layerNames = net.getLayerNames()
lastLayerId = net.getLayerId(layerNames[-1])
lastLayer = net.getLayer(lastLayerId)
print(lastLayer.type)

# 检测
net.setInput(cv.dnn.blobFromImage(image, size=(300, 300), swapRB=True, crop=False))
cvOut = net.forward()
for detection in cvOut[0, 0, :, :]:
    score = float(detection[2])
    if score > 0.5:
        left = detection[3] * w
        top = detection[4] * h
        right = detection[5] * w
        bottom = detection[6] * h

        # 绘制
        cv.rectangle(image, (int(left), int(top)), (int(right), int(bottom)), (0, 255, 0), thickness=2)

cv.imshow('faster-rcnn-demo', image)
cv.waitKey(0)
cv.destroyAllWindows()
