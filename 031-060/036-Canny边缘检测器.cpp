#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * Canny边缘检测器
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat edges, edges_src;
    Canny(src, edges, 100, 300);
    // 提取彩色边缘
    bitwise_and(src, src, edges_src, edges);
    imshow("edges", edges);
    imshow("edges_src", edges_src);

    waitKey(0);
    return 0;
}