#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像去水印/修复
 */
int main() {
    Mat src = imread("../images/wm.jpg");
    //Mat src = imread("../images/master2.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat hsv, mask, result;
    // 得到mask
    cvtColor(src, hsv, COLOR_BGR2HSV);
    inRange(hsv, Scalar(100, 43, 46), Scalar(124, 255, 255), mask);
    Mat se = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(mask, mask, se);
    imshow("mask", mask);

    // 修复
    inpaint(src, mask, result, 3, INPAINT_TELEA);
    imshow("result", result);

    waitKey(0);
    return 0;
}