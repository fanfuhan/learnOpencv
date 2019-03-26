#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像像素归一化
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    // imshow("input", src);

    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    imshow("input", gray);

    // 显示图像用uchar类型，计算时转为float类型
    gray.convertTo(gray, CV_32F);

    // NORM_MINMAX
    Mat dst = Mat::zeros(gray.size(), CV_32FC1);
    normalize(gray, dst, 1.0, 0, NORM_MINMAX);
    Mat res = dst * 255;
    res.convertTo(dst, CV_8UC1); // 显示图像用uchar类型
    imshow("NORM_MINMAX", dst);

    // scale and shift by NORM_INF
    normalize(gray, dst, 1.0, 0, NORM_INF);
    res = dst * 255;
    res.convertTo(dst, CV_8UC1);
    imshow("NORM_INF", dst);

    // scale and shift by NORM_L1
    normalize(gray, dst, 1.0, 0, NORM_L1);
    res = dst * 10000000;
    res.convertTo(dst, CV_8UC1);
    imshow("NORM_L1", dst);

    // scale and shift by NORM_L2
    normalize(gray, dst, 1.0, 0, NORM_L2);
    res = dst * 10000;
    res.convertTo(dst, CV_8UC1);
    imshow("NORM_L2", dst);

    waitKey(0);
    return 0;
}