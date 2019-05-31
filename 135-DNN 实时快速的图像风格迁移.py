"""
DNN 实时快速的图像风格迁移
"""

import cv2 as cv
import numpy as np

styles = ["composition_vii.t7", "starry_night.t7", "la_muse.t7", "the_wave.t7",
          "mosaic.t7", "the_scream.t7", "feathers.t7", "candy.t7", "udnie.t7"]

# 加载模型
index = 2
net = cv.dnn.readNetFromTorch(styles[index])

# 读取图片
frame = cv.imread("images/test.png")
cv.imshow("input", frame)

# 执行风格迁移
blob = cv.dnn.blobFromImage(frame, 1.0, (256, 256),
                           (103.939, 116.779, 123.68), swapRB=False, crop=False)
net.setInput(blob)
out = net.forward()
print(out.shape)

# 解析输出
out = out.reshape(3, out.shape[2], out.shape[3])
print(out.shape)
out[0] += 103.939
out[1] += 116.779
out[2] += 123.68
out /= 255.0
out = out.transpose(1, 2, 0)
print(out.shape)
out = np.clip(out, 0.0, 1.0)

# rescale与中值模糊，消除极值点噪声
cv.normalize(out, out, 0, 255, cv.NORM_MINMAX)
out = cv.medianBlur(out, 5)

# resize and show
h, w = frame.shape[:2]
result = np.uint8(cv.resize(out, (w, h)))
cv.imshow('Fast Style Demo', result)

cv.waitKey(0)
cv.destroyAllWindows()