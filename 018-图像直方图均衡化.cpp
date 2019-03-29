#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像直方图均衡化
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }

    Mat gray, dst;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    equalizeHist(gray, dst);
    imshow("input", gray);
    imshow("eq", dst);

    waitKey(0);
    return 0;
}