#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 均值迁移模糊
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat dst;
    pyrMeanShiftFiltering(src, dst, 15, 30);
    imshow("mean_shift_blur", dst);

    waitKey(0);
    return 0;
}