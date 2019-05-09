#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void process_frame(Mat &image);

/*
 * 识别与跟踪视频中的特定颜色对象
 */
int main() {
    VideoCapture capture("../images/color_object.mp4");
    if (!capture.isOpened()) {
        printf("could not open camera...\n");
        return -1;
    }

    int fps = capture.get(CAP_PROP_FPS);
    int width = capture.get(CAP_PROP_FRAME_WIDTH);
    int height = capture.get(CAP_PROP_FRAME_HEIGHT);
    int num_of_frames = capture.get(CAP_PROP_FRAME_COUNT);
    printf("frame width: %d, frame height: %d, FPS : %d \n", width, height, fps);

    Mat frame;
    while (true) {
        bool ret = capture.read(frame);
        if (!ret) break;
        imshow("input", frame);
        char c = waitKey(50);
        process_frame(frame);
        imshow("result", frame);
        if (c == 27) {
            break;
        }
    }
    waitKey(0);
    return 0;

    waitKey(0);
    return 0;
}

void process_frame(Mat &image) {
    Mat hsv, mask;
    // 转换色彩空间
    cvtColor(image, hsv, COLOR_BGR2HSV);

    // 提取颜色区域mask
    inRange(hsv, Scalar(0, 43, 46), Scalar(10, 255, 255), mask);
    Mat se = getStructuringElement(MORPH_RECT, Size(15, 15));
    morphologyEx(mask, mask, MORPH_OPEN, se);

    // 寻找最大轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    int index = -1;
    int max = 0;
    for (size_t t = 0; t < contours.size(); t++) {
        double area = contourArea(contours[t]);
        if (area > max) {
            max = area;
            index = t;
        }
    }

    // 绘制外接轮廓
    if (index >= 0) {
        RotatedRect rect = minAreaRect(contours[index]);
        ellipse(image, rect, Scalar(0, 255, 0), 2);
        circle(image, rect.center, 2, Scalar(255, 0, 0), 2);
    }
}