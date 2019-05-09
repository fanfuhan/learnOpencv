#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像形态学(闭操作)
 */
int main() {
    Mat src = imread("../images/cells.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 二值图像
    Mat gray, binary, result;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("binary", binary);

    // 闭操作
    Mat se1 = getStructuringElement(MORPH_RECT, Size(25, 5), Point(-1, -1));
    Mat se2 = getStructuringElement(MORPH_RECT, Size(5, 25), Point(-1, -1));
    morphologyEx(binary, result, MORPH_CLOSE, se1);
    morphologyEx(result, result, MORPH_CLOSE, se2);
    imshow("close_demo 25*5 5*25", result);

    // 去除中间小方黑块
    Mat se3 = getStructuringElement(MORPH_CROSS, Size(31, 21));
    morphologyEx(result, result, MORPH_CLOSE, se3);
    // imshow("cross", result);
    morphologyEx(result, result, MORPH_CLOSE, se1);
    morphologyEx(result, result, MORPH_CLOSE, se2);
    imshow("final", result);

    waitKey(0);
    return 0;
}