#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 形态学操作(击中击不中)
 */
int main() {
    Mat src = imread("../images/cross.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 二值图像
    Mat gray, binary, result;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

    // 击中击不中
    Mat se = getStructuringElement(MORPH_CROSS, Size(11,11));
    morphologyEx(binary, result, MORPH_HITMISS, se);

    imshow("bit_and_miss", result);

    waitKey(0);
    return 0;
}