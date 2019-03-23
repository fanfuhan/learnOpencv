#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 自定义LUT
Mat &myColorMap(Mat &image);

/*
 *  Look Up Table(LUT)查找表的使用
 */
int main() {
    Mat src = imread("../images/LinuxLogo.jpg");
    imshow("input", src);

    // 使用LUT
    Mat dst;
    applyColorMap(src, dst, COLORMAP_SUMMER);
    imshow("colorMap", dst);

    // 使用自己的LUT
    Mat my_dst, gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    my_dst = myColorMap(gray);
    imshow("my_dst", my_dst);

    waitKey(0);
    return 0;
}

// 自定义LUT
Mat &myColorMap(Mat &image) {
    int lut[256];
    for (int i = 0; i < 256; ++i) {
        if (i < 127)
            lut[i] = 0;
        else
            lut[i] = 255;
    }

    for (int row = 0; row < image.rows; ++row) {
        for (int col = 0; col < image.cols; ++col) {
            int pv = image.at<uchar>(row, col);
            image.at<uchar>(row, col) = lut[pv];
        }
    }

    return image;
}

