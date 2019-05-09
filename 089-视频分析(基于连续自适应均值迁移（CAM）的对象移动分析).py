'''
视频分析(基于连续自适应均值迁移（CAM）的对象移动分析)
'''

import cv2 as cv

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
term_crit = (cv.TERM_CRITERIA_EPS | cv.TERM_CRITERIA_COUNT, 10, 1)
while True:
    ret, frame = cap.read()
    if not ret:
        break

    hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
    dst = cv.calcBackProject([hsv], [0], roi_hist, [0, 180], 1)

    # 搜索更新roi区域
    track_box = cv.CamShift(dst, track_window, term_crit)
    track_window = track_box[1]
    # print(track_box)

    # 绘制窗口
    cv.ellipse(frame, track_box[0], (0, 0, 255), 3, 8)
    cv.imshow("CAM Demo", frame)

    k = cv.waitKey(50) & 0xff
    if k == 27:
        break

cv.destroyAllWindows()
cap.release()