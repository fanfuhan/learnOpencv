#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像像素的逻辑操作
 */
int main() {
    // create image one, CV_8UC3创建三通道图像
    Mat src1 = Mat::zeros(Size(400, 400), CV_8UC3);
    Rect rect(100,100,100,100);
    // Scalar() 参数为BGR三通道值，绿色和红色加起来是黄色
    src1(rect) = Scalar(0, 255, 255);
    imshow("input1", src1);

    // create image two
    Mat src2 = Mat::zeros(Size(400, 400), CV_8UC3);
    rect.x = 150;
    rect.y = 150;
    src2(rect) = Scalar(0, 0, 255);
    imshow("input2", src2);

    // 逻辑操作
    Mat dst1, dst2, dst3;
    bitwise_and(src1, src2, dst1);
    bitwise_xor(src1, src2, dst2);
    bitwise_or(src1, src2, dst3);
    imshow("and", dst1);
    imshow("xor", dst2);
    imshow("or", dst3);

    // 演示取反操作
    Mat src = imread("../images/test1.jpg");
    Mat dst;
    imshow("input", src);
    bitwise_not(src,dst);
    imshow("not", dst);

    waitKey(0);
    return 0;
}