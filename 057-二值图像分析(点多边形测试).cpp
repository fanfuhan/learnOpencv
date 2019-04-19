#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 二值图像分析(点多边形测试)
 */
int main() {
    Mat src = imread("../images/my_mask.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 二值化
    Mat dst, gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // 轮廓发现与绘制
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());

    Mat image = Mat::zeros(src.size(), CV_32FC3);
    // 对轮廓内外的点进行分类
    for (int row = 0; row < src.rows; ++row) {
        for (int col = 0; col < src.cols; ++col) {
            double dist = pointPolygonTest(contours[0], Point(col, row), true);
            if (dist == 0) {
                image.at<Vec3f>(row, col) = Vec3f(255, 255, 255);
            } else if (dist > 0) {
                image.at<Vec3f>(row, col) = Vec3f(255 - dist, 0, 0);
            } else {
                image.at<Vec3f>(row, col) = Vec3f(0, 0, 255 + dist);
            }
        }
    }
    convertScaleAbs(image, image);
    imshow("points", image);

    waitKey(0);
    return 0;
}