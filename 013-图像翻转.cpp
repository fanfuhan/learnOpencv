#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像翻转
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat dst;
    // X轴 倒影
    flip(src, dst, 0);
    imshow("x_flip", dst);

    // Y轴 镜像
    flip(src, dst, 1);
    imshow("y_flip", dst);

    // XY轴 对角
    flip(src, dst, -1);
    imshow("xy_flip", dst);

    waitKey(0);
    return 0;
}