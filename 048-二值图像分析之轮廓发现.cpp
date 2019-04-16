#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 二值图像分析之轮廓发现
 */
int main() {
    Mat src1 = imread("../images/master.jpg");
    Mat src2 = imread("../images/coins.jpg");
    if (src1.empty() || src2.empty()) {
        cout << "could not load image.." << endl;
    }
    //imshow("input_1", src1);
    imshow("input_2", src2);

    // 去噪声与二值化
    Mat dst, gray, binary;
    GaussianBlur(src2, dst, Size(3, 3), 0, 0);
    cvtColor(dst, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("binary", binary);

    // 轮廓发现与绘制
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
    for (auto t = 0; t < contours.size(); ++t) {
        drawContours(src2, contours, t, Scalar(0,0,255), 2, 8);
    }
    imshow("contours", src2);

    waitKey(0);
    return 0;
}