#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 基本阈值操作
 */
int main() {
    Mat src = imread("../images/master.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    int T = mean(src)[0];
    Mat gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    for (int i = 0; i < 5; ++i) {
//        THRESH_BINARY = 0
//        THRESH_BINARY_INV = 1
//        THRESH_TRUNC = 2
//        THRESH_TOZERO = 3
//        THRESH_TOZERO_INV = 4
        threshold(gray, binary, T, 255, i);
        imshow(format("binary_%d", i), binary);
    }

    waitKey(0);
    return 0;
}