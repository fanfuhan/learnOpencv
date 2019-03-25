#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像像素值统计及应用（普通图像转化为二值图像）
 */
int main() {
    Mat src_bgr = imread("../images/test.png");
    Mat src_gray;
    cvtColor(src_bgr, src_gray, COLOR_BGR2GRAY);
    if (src_bgr.empty() || src_gray.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input_bgr", src_bgr);

    // 计算灰度图像的最大最小值
    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(src_gray, &minVal, &maxVal, &minLoc, &maxLoc);
    cout << "paramenters of src_gray:" << endl;
    printf("min:%.2f, max:%.2f \n", minVal, maxVal);
    printf("min loc: (%d, %d) \n", minLoc.x, minLoc.y);
    printf("max loc: (%d, %d) \n", maxLoc.x, maxLoc.y);

    // 普通图像转二值图像
    Mat mean, stddev;
    meanStdDev(src_bgr, mean, stddev);
    cout << "paramenters of src_bgr:" << endl;
    printf("blue channel mean:%.2f, stddev: %.2f \n", mean.at<double>(0, 0), stddev.at<double>(0, 0));
    printf("green channel mean:%.2f, stddev: %.2f \n", mean.at<double>(1, 0), stddev.at<double>(1, 0));
    printf("red channel mean:%.2f, stddev: %.2f \n", mean.at<double>(2, 0), stddev.at<double>(2, 0));
    for (int row = 0; row < src_bgr.rows; ++row) {
        for (int col = 0; col < src_bgr.cols; ++col) {
            Vec3b bgr = src_bgr.at<Vec3b>(row, col);
            bgr[0] = bgr[0] < mean.at<double>(0, 0) ? 0 : 255;
            bgr[1] = bgr[1] < mean.at<double>(1, 0) ? 0 : 255;
            bgr[2] = bgr[2] < mean.at<double>(2, 0) ? 0 : 255;
            src_bgr.at<Vec3b>(row, col) = bgr;
        }
    }
    imshow("binary", src_bgr);

    waitKey(0);
    return 0;
}