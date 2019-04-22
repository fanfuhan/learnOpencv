#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像形态学(图像梯度)
 */
int main() {
    Mat src = imread("../images/master.jpg", IMREAD_GRAYSCALE);
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    //定义结构元素
    Mat se = getStructuringElement(MORPH_RECT, Size(3, 3));

    Mat basic, exter, inter;
    // 基本梯度
    morphologyEx(src, basic, MORPH_GRADIENT, se);
    imshow("basic_gradient", basic);

    // 外梯度
    morphologyEx(src, exter, MORPH_DILATE, se);
    subtract(exter, src, exter);
    imshow("exter_gradient", exter);

    // 内梯度
    morphologyEx(src, inter, MORPH_ERODE, se);
    subtract(src, inter, inter);
    imshow("inter_gradient", inter);

    waitKey(0);
    return 0;
}