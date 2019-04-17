#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void contours_info(Mat &image, vector<vector<Point>> &pts);

/*
 * 二值图像分析(使用Hu矩实现轮廓匹配)
 */
int main() {
    Mat src = imread("../images/abc.png");
    Mat src2 = imread("../images/a5.png");
    if (src.empty() || src2.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);
    imshow("input1", src2);

    // 轮廓发现
    vector<vector<Point>> contours1;
    vector<vector<Point>> contours2;
    contours_info(src, contours1);
    contours_info(src2, contours2);

    // 几何矩计算与hu矩计算
    Moments mm2 = moments(contours2[0]);
    Mat hu2;
    HuMoments(mm2, hu2);

    // 轮廓匹配
    for (size_t t = 0; t < contours1.size(); ++t) {
        Moments mm = moments(contours1[t]);
        Mat hu;
        HuMoments(mm, hu);
        double dist = matchShapes(hu, hu2, CONTOURS_MATCH_I1, 0);
        if (dist < 1) {
            drawContours(src, contours1, t, Scalar(0,0,255), 2);
        }
    }

    imshow("match_result", src);

    waitKey(0);
    return 0;
}

void contours_info(Mat &image, vector<vector<Point>> &pts) {
    Mat gray, binary;
    vector<Vec4i> hierarchy;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    findContours(binary, pts, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
}