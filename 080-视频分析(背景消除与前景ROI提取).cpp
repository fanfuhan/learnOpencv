#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void process_frame(Mat &image);
Ptr<BackgroundSubtractor> pMOG2 = createBackgroundSubtractorMOG2(500, 100, false);

/*
 * 视频分析(背景消除与前景ROI提取)
 */
int main() {
    VideoCapture capture("../images/vtest.avi");
    if (!capture.isOpened()) {
        printf("could not open camera...\n");
        return -1;
    }

    Mat frame;
    while (true) {
        bool ret = capture.read(frame);
        if (!ret) break;
        imshow("input", frame);
        process_frame(frame);
        imshow("result", frame);
        char c = waitKey(50);
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
    Mat mask;
    pMOG2->apply(image, mask);

    // 开操作
    Mat se = getStructuringElement(MORPH_RECT, Size(1, 5));
    morphologyEx(mask, mask, MORPH_OPEN, se);

    // 寻找最大轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    for (size_t t = 0; t < contours.size(); t++) {
        double area = contourArea(contours[t]);
        if (area < 100) {
            continue;
        }
        RotatedRect rect = minAreaRect(contours[t]);
        ellipse(image, rect, Scalar(0, 255, 0), 2);
        circle(image, rect.center, 2, Scalar(255, 0, 0), 2);
    }
}