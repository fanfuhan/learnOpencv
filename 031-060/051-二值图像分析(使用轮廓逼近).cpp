#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 二值图像分析(使用轮廓逼近)
 */
int main() {
    Mat src = imread("../images/contours.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 去噪声与二值化
    Mat gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // 轮廓发现与绘制
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
    Scalar color = Scalar(255, 0, 0);
    for (size_t t = 0; t < contours.size(); ++t) {
        RotatedRect rrt = minAreaRect(contours[t]);
        Point2f cpt = rrt.center;
        circle(src, cpt, 2, Scalar(0, 255, 0), 2);

        Mat result;
        approxPolyDP(contours[t], result, 4, true);
        if (result.rows == 6) {
            putText(src, "poly", cpt, FONT_HERSHEY_SIMPLEX, .7, color);
        }
        if (result.rows == 3) {
            putText(src, "triangle", cpt, FONT_HERSHEY_SIMPLEX, .7, color);
        }
        if (result.rows == 4) {
            putText(src, "rectangle", cpt, FONT_HERSHEY_SIMPLEX, .7, color);
        }
        if(result.rows > 10) {
            putText(src, "circle", cpt, FONT_HERSHEY_SIMPLEX, .7, color);
        }
    }

    imshow("contours", src);

    waitKey(0);
    return 0;
}