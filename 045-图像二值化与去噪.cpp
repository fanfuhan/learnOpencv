#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像二值化与去噪
 */
int main() {
    Mat src = imread("../images/coins.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat gray, blurred, binary;

    // 直接二值化
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("binary_direct", binary);

    // 先高斯模糊，再二值化
    GaussianBlur(src, blurred, Size(3,3), 0, 0);
    cvtColor(blurred, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("binary_gaussian", binary);

    // 先均值迁移模糊，再二值化
    pyrMeanShiftFiltering(src, blurred, 10, 100);
    cvtColor(blurred, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("binary_pyrmean", binary);

    waitKey(0);
    return 0;
}