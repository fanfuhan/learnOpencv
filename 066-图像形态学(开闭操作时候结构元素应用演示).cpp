#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


void open_demo();

void close_demo();

/*
 * 图像形态学(开闭操作时候结构元素应用演示)
 */
int main() {
    //open_demo();
    close_demo();

    waitKey(0);
    return 0;
}

void close_demo() {
    // 读取图像
    Mat src = imread("../images/morph3.png");
    imshow("input", src);

    // 二值图像
    Mat gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("binary", binary);

    // 闭操作
    //Mat se = getStructuringElement(MORPH_ELLIPSE, Size(30, 30), Point(-1, -1));
    //Mat se = getStructuringElement(MORPH_RECT, Size(30, 30), Point(-1, -1));
    Mat se = getStructuringElement(MORPH_RECT, Size(35, 35), Point(-1, -1));
    morphologyEx(binary, binary, MORPH_CLOSE, se);
    imshow("close_demo rect=35,35", binary);
}

void open_demo() {
    // 读取图像
    Mat src = imread("../images/fill.png");
    imshow("input", src);

    // 二值图像
    Mat gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    imshow("binary", binary);

    // 开操作
    Mat se = getStructuringElement(MORPH_RECT, Size(25, 1), Point(-1, -1));
    morphologyEx(binary, binary, MORPH_OPEN, se);
    imshow("open_op", binary);

    // 绘制填空位置
    vector<vector<Point>> contours;
    vector<Vec4i> hierarhy;
    findContours(binary, contours, hierarhy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(-1, -1));
    for (size_t t = 0; t < contours.size(); t++) {
        Rect roi = boundingRect(contours[t]);
        roi.y = roi.y - 10;
        roi.height = 12;
        rectangle(src, roi, Scalar(0, 0, 255));
    }

    // 显示结果
    imshow("open_demo", src);
}