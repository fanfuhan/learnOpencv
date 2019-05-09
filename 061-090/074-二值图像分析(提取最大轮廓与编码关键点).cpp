#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 二值图像分析(提取最大轮廓与编码关键点)
 */
int main() {
    Mat src = imread("../images/case6.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 图像二值化
    Mat gray, binary;
    GaussianBlur(src, src, Size(5, 5), 0);
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // 闭操作
    Mat se = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(binary, binary, MORPH_CLOSE, se);

    // 发现最大轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    int height = src.rows;
    int width = src.cols;
    int index = -1;
    int max = 0;
    for (size_t t = 0; t < contours.size(); ++t) {
        Rect rect = boundingRect(contours[t]);
        if (rect.height >= height || rect.width >= width) {
            continue;
        }
        double area = contourArea(contours[t]);
        if (area > max) {
            max = area;
            index = t;
        }
    }

    // 绘制关键点
    Mat result = Mat::zeros(src.size(), src.type());
    Mat pts;
    drawContours(src, contours, index, Scalar(0, 0, 255));
    approxPolyDP(contours[index], pts, 4, true);
    for (int i = 0; i < pts.rows; ++i) {
        Vec2i pt = pts.at<Vec2i>(i, 0);
        circle(src, Point(pt[0], pt[1]), 2, Scalar(0, 255, 0), 2);
        circle(result, Point(pt[0], pt[1]), 2, Scalar(0, 255, 0), 2);
    }

    imshow("result", src);
    imshow("result_binary", result);
    waitKey(0);
    return 0;
}