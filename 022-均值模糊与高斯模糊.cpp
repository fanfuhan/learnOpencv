#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 均值模糊与高斯模糊
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat dst1, dst2, dst3;
    blur(src, dst1, Size(5, 5));
    GaussianBlur(src, dst2, Size(5, 5), 15, 0);
    GaussianBlur(src, dst3, Size(15, 15), 15, 0);

    imshow("blur ksize=5", dst1);
    imshow("gaussian ksize=5", dst2);
    imshow("gaussian ksize=15", dst3);

    waitKey(0);
    return 0;
}