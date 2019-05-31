"""
DNN ENet实现图像分割
"""

import cv2 as cv
import numpy as np

# load CNN model
bin_model = "model-best.net"
net = cv.dnn.readNetFromTorch(bin_model)

# read input data
frame = cv.imread("images/cityscapes_test.jpg")
blob = cv.dnn.blobFromImage(frame, 0.00392, (1024, 512), (0, 0, 0), True, False)
cv.namedWindow("input", cv.WINDOW_NORMAL)
cv.imshow("input", frame)

# Run a model
net.setInput(blob)
score = net.forward()
print(score.shape)

# Put efficiency information.
t, _ = net.getPerfProfile()
label = 'Inference time: %.2f ms' % (t * 1000.0 / cv.getTickFrequency())

# generate color table
color_lut = []
n, con, h, w = score.shape
for i in range(con):
    b = np.random.randint(0, 256)
    g = np.random.randint(0, 256)
    r = np.random.randint(0, 256)
    color_lut.append((b, g, r))

# find max score for 20 channels on pixel-wise
maxCl = np.zeros((h, w), dtype=np.int32)
maxVal = np.zeros((h, w), dtype=np.float32)
for i in range(con):
    for row in range(h):
        for col in range(w):
            t = maxVal[row, col]
            s = score[0, i, row, col]
            if s > t:
                maxVal[row, col] = s
                maxCl[row, col] = i

# colorful the segmentation image
segm = np.zeros((h, w, 3), dtype=np.uint8)
for row in range(h):
    for col in range(w):
        index = maxCl[row, col]
        segm[row, col] = color_lut[index]

h, w = frame.shape[:2]
segm = cv.resize(segm, (w, h), None, 0, 0, cv.INTER_NEAREST)
print(segm.shape, frame.shape)
cv.namedWindow("result", cv.WINDOW_NORMAL)
cv.imshow("result", segm)

frame_segm = cv.addWeighted(frame, 0.2, segm, 0.8, 0.0)
cv.putText(frame_segm, label, (0, 15), cv.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0))
cv.namedWindow("input_result", cv.WINDOW_NORMAL)
cv.imshow("input_result", frame_segm)

cv.waitKey(0)
cv.destroyAllWindows()