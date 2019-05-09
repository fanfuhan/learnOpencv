#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像形态学(顶帽操作)
 */
int main() {
    Mat src = imread("../images/cells.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 二值化
    Mat gray, binary, result;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // 开操作
    Mat se = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(binary, result, MORPH_OPEN, se);
    imshow("open_demo", result);

    // 顶帽操作
    morphologyEx(binary, result, MORPH_TOPHAT, se);
    imshow("tophat_demo", result);

    waitKey(0);
    return 0;
}