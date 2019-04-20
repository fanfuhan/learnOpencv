#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像形态学(膨胀与腐蚀)
 */
int main() {
    Mat src = imread("../images/master.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat dresult, eresult;
    // 定义结构元素3*3大小的矩形
    Mat se = getStructuringElement(MORPH_RECT, Size(3,3));
    // 膨胀
    dilate(src, dresult, se);
    // 腐蚀
    erode(src, eresult, se);

    imshow("dilate", dresult);
    imshow("erode", eresult);

    waitKey(0);
    return 0;
}