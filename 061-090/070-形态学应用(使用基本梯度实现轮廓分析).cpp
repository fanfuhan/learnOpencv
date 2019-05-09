#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 形态学应用(使用基本梯度实现轮廓分析)
 */
int main() {
    Mat src = imread("../images/address.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat basic, gray, binary;
    // 基本梯度
    Mat se = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(src, basic, MORPH_GRADIENT, se);

    // 二值化
    cvtColor(basic, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // 膨胀
    se = getStructuringElement(MORPH_RECT, Size(1, 5));
    morphologyEx(binary, binary, MORPH_DILATE, se);

    // 轮廓绘制
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    for (size_t c = 0; c < contours.size(); c++) {
        Rect rect = boundingRect(contours[c]);
        double area = contourArea(contours[c]);
        if (area < 200) {
            continue;
        }
        int h = rect.height;
        int w = rect.width;
        if (h > (3 * w) || h < 20) {
            continue;
        }
        rectangle(src, rect, Scalar(0, 0, 255));
    }
    imshow("result", src);

    waitKey(0);
    return 0;
}