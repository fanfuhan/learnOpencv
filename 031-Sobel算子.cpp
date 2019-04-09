#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * Sobel算子
 */
int main() {
    Mat src = imread("../images/test3.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat grad_x, grad_y, grad;
    // 求取x方向和y方向梯度
    Sobel(src, grad_x, CV_32F, 1, 0);
    Sobel(src, grad_y, CV_32F, 0, 1);
    convertScaleAbs(grad_x, grad_x);
    convertScaleAbs(grad_y, grad_y);
    // 求取总梯度
    add(grad_x, grad_y, grad, Mat(), CV_16S);
    convertScaleAbs(grad, grad);

    imshow("grad_x", grad_x);
    imshow("grad_y", grad_y);
    imshow("grad", grad);

    waitKey(0);
    return 0;
}