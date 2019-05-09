#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 二值图像分析(缺陷检测一)
 */
int main() {
    Mat src = imread("../images/ce_02.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 二值图像
    Mat gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

    // 开操作,去掉一些小块
    Mat se = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(binary, binary, MORPH_OPEN, se);

    // 绘制轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    int height = src.rows;
    for (size_t t = 0; t < contours.size(); t++) {
        Rect rect = boundingRect(contours[t]);
        double area = contourArea(contours[t]);
        if (rect.height > (height / 2)) {
            continue;
        }
        if (area < 150) {
            continue;
        }
        // 绘制外接矩形
        rectangle(src, rect, Scalar(0, 0, 255),2);
        // 绘制轮廓
        drawContours(src, contours, t, Scalar(0, 255, 0), 2);
    }

    imshow("result", src);

    waitKey(0);
    return 0;
}