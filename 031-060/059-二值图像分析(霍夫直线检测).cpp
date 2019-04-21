#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 二值图像分析(霍夫直线检测)
 */
int main() {
    Mat src = imread("../images/sudoku.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 去噪声与二值化
    Mat binary;
    Canny(src, binary, 80, 160);

    // 标准霍夫直线检测
    vector<Vec2f> lines;
    HoughLines(binary, lines, 1, CV_PI / 180, 150);

    // 绘制直线
    Point pt1, pt2;
    for (size_t i = 0; i < lines.size(); ++i) {
        float rho = lines[i][0];
        float theta = lines[i][1];
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(src, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
    }

    imshow("contours", src);

    waitKey(0);
    return 0;
}