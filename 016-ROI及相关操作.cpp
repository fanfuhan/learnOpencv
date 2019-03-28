#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * ROI及相关操作
 */
int main() {
    Mat src = imread("../images/test.png");
    imshow("input", src);
    int h = src.rows;
    int w = src.cols;
    // 获取ROI
    int cy = h / 2;
    int cx = w / 2;
    Rect rect(cx - 100, cy - 100, 200, 200);
    // 注意：roi 与 src指向同一块内存区域，改变roi,src也会改变
    Mat roi = src(rect);
    imshow("roi", roi);

    // 人物背景图，换背景
    // load image
    Mat image = imread("../images/boy.jpg");
    imshow("input", image);
    // generate mask
    Mat hsv, mask, mask_not;
    cvtColor(image, hsv, COLOR_BGR2HSV);
    inRange(hsv, Scalar(35, 43, 46), Scalar(99, 255, 255), mask);
    imshow("mask", mask);
    // extract person
    Mat person;
    bitwise_not(mask, mask_not);
    imshow("mask_not", mask_not);
    bitwise_and(image, image, person, mask_not);
    imshow("person", person);
    // gengerate background
    Mat background = Mat::zeros(image.size(), image.type());
    background.setTo(Scalar(255, 0 ,0));
    imshow("background", background);
    // combine background + person
    Mat dst;
    bitwise_or(person, background, dst, mask);
    add(dst, person, dst);
    imshow("dst", dst);

    waitKey(0);
    return 0;
}