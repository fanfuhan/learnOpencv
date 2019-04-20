#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像形态学(膨胀与腐蚀-获取结构元素)
 */
int main() {
    Mat src = imread("../images/coins.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 二值化
    Mat gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("binary", binary);

    Mat dresult, eresult;
    // 定义结构元素3*3大小的矩形
    Mat se = getStructuringElement(MORPH_RECT, Size(3,3));
    // 膨胀
    dilate(binary, dresult, se);
    // 腐蚀
    erode(binary, eresult, se);

    imshow("dilate", dresult);
    imshow("erode", eresult);

    waitKey(0);
    return 0;
}