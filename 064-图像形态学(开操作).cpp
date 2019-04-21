#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像形态学(开操作)
 */
int main() {
    Mat src = imread("../images/shuini.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 二值化
    Mat gray, binary, result;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gray, Size(9, 9), 0, 0);
    adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_GAUSSIAN_C,
            THRESH_BINARY_INV, 45, 15);
    imshow("binary", binary);

    // 开操作
    Mat se = getStructuringElement(MORPH_RECT, Size(5,5));
    morphologyEx(binary, result, MORPH_OPEN, se);
    imshow("open demo", result);

    waitKey(0);
    return 0;
}