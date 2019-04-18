#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 二值图像分析(对轮廓圆与椭圆拟合)
 */
int main() {
    Mat src = imread("../images/stuff.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 去噪声与二值化
    Mat dst, gray, binary;
    Canny(src, binary, 80, 160);

    Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    dilate(binary, binary, k);

    // 轮廓发现与绘制
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
    for (size_t t = 0; t < contours.size(); t++) {
        // 寻找适配圆
        RotatedRect rrt = fitEllipse(contours[t]);
        ellipse(src, rrt, Scalar(0,0,255), 2);
    }

    imshow("contours", src);

    waitKey(0);
    return 0;
}