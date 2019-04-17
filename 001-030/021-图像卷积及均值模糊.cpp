#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像卷积及均值模糊
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 均值模糊
    Mat dst;
    blur(src, dst, Size(15, 15), Point(-1, -1), 4);
    imshow("dst", dst);

    // 3x3 均值模糊，自定义版本实现
    for (int row = 1; row < h-1; row++) {
        for (int col = 1; col < w-1; col++) {
            Vec3b p1 = src.at<Vec3b>(row-1, col-1);
            Vec3b p2 = src.at<Vec3b>(row-1, col);
            Vec3b p3 = src.at<Vec3b>(row-1, col+1);
            Vec3b p4 = src.at<Vec3b>(row, col-1);
            Vec3b p5 = src.at<Vec3b>(row, col);
            Vec3b p6 = src.at<Vec3b>(row, col+1);
            Vec3b p7 = src.at<Vec3b>(row+1, col-1);
            Vec3b p8 = src.at<Vec3b>(row+1, col);
            Vec3b p9 = src.at<Vec3b>(row+1, col+1);

            int b = p1[0] + p2[0] + p3[0] + p4[0] + p5[0] + p6[0] + p7[0] + p8[0] + p9[0];
            int g = p1[1] + p2[1] + p3[1] + p4[1] + p5[1] + p6[1] + p7[1] + p8[1] + p9[1];
            int r = p1[2] + p2[2] + p3[2] + p4[2] + p5[2] + p6[2] + p7[2] + p8[2] + p9[2];

            dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b / 9);
            dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g / 9);
            dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r / 9);
        }
    }

    waitKey(0);
    return 0;
}