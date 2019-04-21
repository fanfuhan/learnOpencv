#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像锐化
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat sharpen_op = (Mat_<char>(3,3) << -1, -1, -1,
            -1, 9, -1,
            -1, -1, -1);

    // Mat sharpen_op1 = (Mat_<char>(3,3) << 0, -1, 0,
    //        -1, 9, -1,
    //        0, -1, 0);

    Mat dst;
    filter2D(src, dst, CV_32F, sharpen_op);
    convertScaleAbs(dst, dst);

    imshow("sharpen", dst);

    waitKey(0);
    return 0;
}