#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像二值寻找算法 – OTSU
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 自动阈值寻找与二值化
    Mat gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    double T = threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    cout << "threshold : " << T << endl;
    imshow("binary", binary);

    waitKey(0);
    return 0;
}