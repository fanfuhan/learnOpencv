#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 二值图像介绍
 */
int main() {
    Mat src = imread("../images/master.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 转为灰度图像
    Mat gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    int t = 127;
    Scalar m = mean(src);
    int t_mean = m[0];

    // 转二值图像
    binary = Mat::zeros(src.size(), CV_8UC1);
    for (int row = 0; row < src.rows; ++row) {
        for (int col = 0; col < src.cols; ++col) {
            int pv = gray.at<uchar>(row, col);
            pv > t ? binary.at<uchar>(row, col) = 255
                    : binary.at<uchar>(row, col) = 0;
        }
    }

    imshow("binary_t=127", binary);
    //imshow("binary_t=mean", binary);

    waitKey(0);
    return 0;
}