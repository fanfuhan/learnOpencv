#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 中值模糊
 */
int main() {
    Mat src = imread("../images/sp_noise.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat dst;
    medianBlur(src, dst, 5);
    imshow("medianBlur", dst);

    waitKey(0);
    return 0;
}