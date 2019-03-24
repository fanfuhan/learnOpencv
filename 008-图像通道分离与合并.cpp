#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像通道分离与合并
 */
int main() {
    Mat src = imread("../images/baboon.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    vector<Mat> mv; // mv用于存储图像分离后各通道像素
    Mat dst1, dst2, dst3;

    // 令蓝色通道为0
    split(src, mv);
    mv[0] = Scalar(0);
    merge(mv, dst1);
    imshow("blue == 0", dst1);

    // 令绿色通道为0
    split(src, mv);
    mv[1] = Scalar(0);
    merge(mv, dst2);
    imshow("green == 0", dst2);

    // 令红色通道为0
    split(src, mv);
    mv[2] = Scalar(0);
    merge(mv, dst3);
    imshow("red == 0", dst3);

    waitKey(0);
    return 0;
}