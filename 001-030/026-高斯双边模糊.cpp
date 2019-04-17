#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 高斯双边模糊
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat dst;
    bilateralFilter(src, dst, 0, 100, 10, 4);
    imshow("gaussian_bilater_blur", dst);

    waitKey(0);
    return 0;
}