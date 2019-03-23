#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

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
    waitKey(0);
    return 0;
}

