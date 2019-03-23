#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/*
 * 读取与显示图像
 */
int main() {
    // Mat image = imread("../images/liuyifei_1.png");
    // 读取的时候加参数，使读取后为灰度图像
    Mat image = imread("../images/liuyifei_1.png",IMREAD_GRAYSCALE);

    if (image.empty()) {
        cout << "could not load image..." << endl;
        return -1;
    }

    namedWindow("input");
    imshow("input",image);
    waitKey(0);
    return 0;
}