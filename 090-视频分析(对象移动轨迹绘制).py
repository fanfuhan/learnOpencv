"""
视频分析(对象移动轨迹绘制)
"""

import cv2 as cv
import numpy as np

cap = cv.VideoCapture('images/balltest.mp4')
if not cap.isOpened():
    print("could not read video")
    exit(0)

# 读取第一帧
ret, frame = cap.read()

# 选择ROI区域
x, y, w, h = cv.selectROI("CAM Demo", frame, True, False)
track_window = (x, y, w, h)

# 获取ROI直方图
roi = frame[y:y + h, x:x + w]
hsv_roi = cv.cvtColor(roi, cv.COLOR_BGR2HSV)
mask = cv.inRange(hsv_roi, (26, 43, 46), (34, 255, 255))
roi_hist = cv.calcHist([hsv_roi], [0], mask, [180], [0, 180])
cv.normalize(roi_hist, roi_hist, 0, 255, cv.NORM_MINMAX)

# 搜索跟踪分析
tracking_path = []
term_crit = (cv.TERM_CRITERIA_EPS | cv.TERM_CRITERIA_COUNT, 10, 1)
while True:
    ret, frame = cap.read()
    if not ret:
        break

    hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
    dst = cv.calcBackProject([hsv], [0], roi_hist, [0, 180], 1)

    # 搜索更新roi区域,保持运行轨迹
    track_box = cv.CamShift(dst, track_window, term_crit)
    track_window = track_box[1]
    pt = np.int32(track_box[0][0])
    if pt[0] > 0 and pt[1] > 0:
        tracking_path.append(pt)

    # 绘制窗口
    cv.ellipse(frame, track_box[0], (0, 0, 255), 3, 8)

    # 绘制运动轨迹
    if len(tracking_path) > 40:
        tracking_path = tracking_path[-40:-1]
    for i in range(1, len(tracking_path)):
        cv.line(frame, (tracking_path[i-1][0], tracking_path[i-1][1]),
                (tracking_path[i][0], tracking_path[i][1]), (255, 0, 0),
                2, 8, 0)


    cv.imshow("CAM Demo", frame)

    k = cv.waitKey(50) & 0xff
    if k == 27:
        break

cv.destroyAllWindows()
cap.release()
