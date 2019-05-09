#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 二值图像分析(霍夫圆检测)
 */
int main() {
    Mat src = imread("../images/coins.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 转换为灰度空间与高斯模糊
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gray, Size(9, 9), 2, 2);

    // 霍夫圆检测
    int dp = 2; // 在其它参数保持不变的情况下。dp的取值越高，越容易检测到圆
    int min_radius = 20;
    int max_radius = 100;
    int minDist = 10;
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, dp, minDist,
                 100, 100, min_radius, max_radius);
    for (size_t i = 0; i < circles.size(); ++i) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // 绘制圆
        circle(src, center, radius, Scalar(0, 0, 255), 3);
        circle(src, center, 3, Scalar(0, 255, 0), -1); //绘制圆心
    }

    imshow("result_dp=2", src);

    waitKey(0);
    return 0;
}