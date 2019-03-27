#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像插值
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    int h = src.rows;
    int w = src.cols;
    float fx = 0.0, fy = 0.0;
    Mat dst = Mat::zeros(src.size(), src.type());
    Size S(w * 2, h * 2);

    resize(src, dst, S, fx, fy, INTER_NEAREST);
    imshow("INTER_NEAREST", dst);

    resize(src, dst, S, fx, fy, INTER_LINEAR);
    imshow("INTER_LINEAR", dst);

    resize(src, dst, S, fx, fy, INTER_CUBIC);
    imshow("INTER_CUBIC", dst);

    resize(src, dst, S, fx, fy, INTER_LANCZOS4);
    imshow("INTER_LANCZOS4", dst);

    waitKey(0);
    return 0;
}