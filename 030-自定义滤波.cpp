#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 自定义滤波
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat dst1, dst2, dst3;

    // 均值模糊
    Mat kernel1 = Mat::ones(5, 5, CV_32F) / (float) (25);
    filter2D(src, dst1, -1, kernel1);

    // 锐化
    Mat kernel2 = (Mat_<char>(3, 3) << 0, -1, 0,
            -1, 5, -1,
            0, -1, 0);
    filter2D(src, dst2, -1, kernel2);

    // 梯度
    Mat kernel3 = (Mat_<int>(2, 2) << 1, 0, 0, -1);
    filter2D(src, dst3, CV_32F, kernel3);
    convertScaleAbs(dst3, dst3);  // 转换为字节类型，非常重要

    imshow("blur=5x5", dst1);
    imshow("shape=3x3", dst2);
    imshow("gradient=2x2", dst3);

    waitKey(0);
    return 0;
}