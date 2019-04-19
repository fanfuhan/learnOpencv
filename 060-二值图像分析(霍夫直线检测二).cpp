#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 二值图像分析(霍夫直线检测二)
 */
int main() {
    Mat src = imread("../images/line.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 去噪声与二值化
    Mat binary;
    Canny(src, binary, 80, 160);

    // 霍夫直线检测
    vector<Vec4i> lines;
    HoughLinesP(binary, lines, 1, CV_PI / 180, 80, 30, 10);

    // 绘制直线
    Mat result = Mat::zeros(src.size(), src.type());
    for (size_t i = 0; i < lines.size(); ++i) {
        line(result, Point(lines[i][0], lines[i][1]),
             Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255));
    }

    imshow("contours", result);

    waitKey(0);
    return 0;
}