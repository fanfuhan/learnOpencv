#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * Robert算子与Prewitt算子
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // Robert算子
    Mat robert_x = (Mat_<int>(2, 2) << 1, 0, 0, -1);
    Mat robert_y = (Mat_<int>(2, 2) << 0, -1, 1, 0);
    Mat robert_grad_x, robert_grad_y, robert_grad;
    filter2D(src, robert_grad_x, CV_16S, robert_x);
    filter2D(src, robert_grad_y, CV_16S, robert_y);
    convertScaleAbs(robert_grad_x, robert_grad_x);
    convertScaleAbs(robert_grad_y, robert_grad_y);
    add(robert_grad_x, robert_grad_y, robert_grad);
    convertScaleAbs(robert_grad, robert_grad);
    imshow("robert_grad_x", robert_grad_x);
    imshow("robert_grad_y", robert_grad_y);
    imshow("robert_grad", robert_grad);

    // 定义Prewitt算子
    Mat prewitt_x = (Mat_<char>(3, 3) << -1, 0, 1,
            -1, 0, 1,
            -1, 0, 1);
    Mat prewitt_y = (Mat_<char>(3, 3) << -1, -1, -1,
            0, 0, 0,
            1, 1, 1);
    Mat prewitt_grad_x, prewitt_grad_y, prewitt_grad;
    filter2D(src, prewitt_grad_x, CV_32F, prewitt_x);
    filter2D(src, prewitt_grad_y, CV_32F, prewitt_y);
    convertScaleAbs(prewitt_grad_x, prewitt_grad_x);
    convertScaleAbs(prewitt_grad_y, prewitt_grad_y);
    add(prewitt_grad_x, prewitt_grad_y, prewitt_grad);
    convertScaleAbs(prewitt_grad, prewitt_grad);
    imshow("prewitt_grad_x", prewitt_grad_x);
    imshow("prewitt_grad_y", prewitt_grad_y);
    imshow("prewitt_grad", prewitt_grad);

    waitKey(0);
    return 0;
}