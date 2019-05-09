#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像形态学(黑帽操作)
 */
int main() {
    Mat src = imread("../images/morph.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 二值图像
    Mat gray, binary, result;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // 黑帽操作
    Mat se = getStructuringElement(MORPH_RECT, Size(15, 15), Point(-1, -1));
    morphologyEx(binary, result, MORPH_CLOSE, se);
    imshow("close_op", result);
    morphologyEx(binary, result, MORPH_BLACKHAT, se);
    imshow("blackhat_op", result);

    waitKey(0);
    return 0;
}