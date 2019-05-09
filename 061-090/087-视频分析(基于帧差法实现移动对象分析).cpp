#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 视频分析(基于帧差法实现移动对象分析)
 */
int main() {
    VideoCapture capture("../images/bike.avi");
    if (!capture.isOpened()) {
        cout << "could not open video..." << endl;
        return -1;
    }

    // 读取第一帧
    Mat preFrame, preGray;
    capture.read(preFrame);
    cvtColor(preFrame, preGray, COLOR_BGR2GRAY);
    GaussianBlur(preGray, preGray, Size(0, 0), 15);

    Mat diff;
    Mat frame, gray;

    // 定义结构元素
    Mat k = getStructuringElement(MORPH_RECT, Size(7, 7));

    while (true) {
        bool ret = capture.read(frame);
        if (!ret) break;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, gray, Size(0, 0), 15);
        subtract(gray, preGray, diff);
        threshold(diff, diff, 0, 255, THRESH_BINARY | THRESH_OTSU);
        morphologyEx(diff, diff, MORPH_OPEN, k);
        imshow("input", frame);
        imshow("result", diff);

        gray.copyTo(preGray);
        char c = waitKey(5);
        if (c == 27) {
            break;
        }
    }

    waitKey(0);
    return 0;
}