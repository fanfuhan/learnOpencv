#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 快速的图像边缘滤波算法
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat dst;
    edgePreservingFilter(src, dst, 1, 60, 0.44);
    imshow("result", dst);

    waitKey(0);
    return 0;
}