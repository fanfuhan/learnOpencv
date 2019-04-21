#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * USM 锐化增强算法
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat blur_img, usm;
    GaussianBlur(src, blur_img, Size(0,0), 25);
    addWeighted(src, 1.5, blur_img, -0.5, 0, usm);
    imshow("usm", usm);

    waitKey(0);
    return 0;
}