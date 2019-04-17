#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 色彩空间及其应用
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // RGB ==> HSV  YUV  YCrCb
    Mat hsv, yuv, ycrcb;
    cvtColor(src, hsv, COLOR_BGR2HSV);
    cvtColor(src, yuv, COLOR_BGR2YUV);
    cvtColor(src, ycrcb, COLOR_BGR2YCrCb);
    imshow("hsv", hsv);
    imshow("yuv", yuv);
    imshow("ycrcb", ycrcb);

    /*
     * 提取图像前景和背景
     */
    Mat src2 = imread("../images/boy.jpg");
    imshow("input boy", src2);
    cvtColor(src2, hsv, COLOR_BGR2HSV);
    // 从HSV表中查到绿色的最低值和最高值，建立掩模
    Mat mask, mask_not;
    inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);
    imshow("mask", mask);
    Mat fg, bg;
    // 提取背景
    bitwise_and(src2, src2, bg, mask);
    // 提取前景
    bitwise_not(mask, mask_not);
    imshow("mask_not", mask_not);
    bitwise_and(src2, src2, fg, mask_not);
    imshow("background", bg);
    imshow("foreground" ,fg);

    waitKey(0);
    return 0;
}