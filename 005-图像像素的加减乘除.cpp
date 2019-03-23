#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/*
 * 图像像素的加减乘除
 */
    int main(){
    Mat src1 = imread("../images/opencv_images/LinuxLogo.jpg");
    Mat src2 = imread("../images/opencv_images/WindowsLogo.jpg");
    if(src1.empty() || src2.empty()){
        cout<<"conld not read image..."<<endl;
        return -1;
    }
    imshow("input1", src1);
    imshow("input2", src2);

    // 加法
    Mat add_result = Mat::zeros(src1.size(),src1.type());
    add(src1, src2, add_result);
    imshow("add_result", add_result);

    // 减法
    Mat sub_result = Mat::zeros(src1.size(),src1.type());
    subtract(src1, src2, sub_result);
    imshow("sub_result", sub_result);

    // 乘法
    Mat mul_result = Mat::zeros(src1.size(),src1.type());
    multiply(src1, src2, mul_result);
    imshow("mul_result", mul_result);

    // 除法
    Mat div_result = Mat::zeros(src1.size(),src1.type());
    add(src1, src2, div_result);
    imshow("div_result", div_result);

    // 自己实现加法操作
    int b1 = 0, g1 = 0, r1 = 0;
    int b2 = 0, g2 = 0, r2 = 0;
    int b = 0, g = 0, r = 0;

    Mat my_add_result = Mat::zeros(src1.size(), src1.type());
    for (int row = 0; row < src1.rows; ++row) {
        for (int col = 0; col < src1.cols; ++col) {
            b1 = src1.at<Vec3b>(row, col)[0];
            g1 = src1.at<Vec3b>(row, col)[1];
            r1 = src1.at<Vec3b>(row, col)[2];

            b2 = src2.at<Vec3b>(row, col)[0];
            g2 = src2.at<Vec3b>(row, col)[1];
            r2 = src2.at<Vec3b>(row, col)[2];

            // b1:0~255,b2:0~255, b1+b2可能大于255，所以需要转换，通过saturate_cast<uchar>()
            my_add_result.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b1 + b2);
            my_add_result.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g1 + g2);
            my_add_result.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r1 + r2);
        }
    }
    imshow("my_add_result", my_add_result);

    waitKey(0);
    return 0;
}