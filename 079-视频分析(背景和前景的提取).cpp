#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 视频分析(背景和前景的提取)
 */
int main() {
    VideoCapture capture("../images/color_object.mp4");
    if (!capture.isOpened()) {
        printf("could not open camera...\n");
        return -1;
    }
    namedWindow("input", WINDOW_NORMAL);
    namedWindow("mask", WINDOW_NORMAL);
    namedWindow("background image", WINDOW_NORMAL);

    Mat frame, mask, back_img;
    Ptr<BackgroundSubtractor> pMOG2 = createBackgroundSubtractorMOG2(500, 1000, false);
    while (true) {
        bool ret = capture.read(frame);
        if (!ret) break;
        pMOG2->apply(frame, mask);
        pMOG2->getBackgroundImage(back_img);
        imshow("input", frame);
        imshow("mask", mask);
        imshow("background image", back_img);
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