#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 自动阈值寻找与二值化
 */
int main() {
    Mat src = imread("../images/text1.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 自动阈值寻找与二值化
    Mat gray, binary1, binary2;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    // int T = mean(src)[0];
    // threshold(gray, binary1, T, 255, THRESH_BINARY);
    adaptiveThreshold(gray, binary2, 255, ADAPTIVE_THRESH_GAUSSIAN_C,
            THRESH_BINARY, 25, 10);
    // imshow("binary_T=mean", binary1);
    imshow("binary_adaptive", binary2);

    waitKey(0);
    return 0;
}