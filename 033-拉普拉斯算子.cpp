#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 *  拉普拉斯算子(二阶导数算子)
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    Mat blured, dst;
    GaussianBlur(src, blured, Size(3,3), 0);
    Laplacian(blured, dst, CV_32F, 1, 1.0, 127.0);
    convertScaleAbs(dst, dst);
    imshow("Laplacian", dst);

    waitKey(0);
    return 0;
}