"""
DNN模块 获取导入模型各层信息
"""

import cv2 as cv
import numpy as np

bin_model = "bvlc_googlenet.caffemodel"
protxt = "bvlc_googlenet.prototxt"

# load CNN model
net = cv.dnn.readNet(bin_model, protxt)

# 获取各层信息
layer_names = net.getLayerNames()
for name in layer_names:
    id = net.getLayerId(name)
    layer = net.getLayer(id)
    print("layer id : {}, type : {}, name : {}"
          .format(id, layer.type, layer.name))

print("successfully loaded model...")

cv.waitKey(0)
cv.destroyAllWindows()
