#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/**
 * 读取图像，实现像素反转
 */
int main() {
    Mat src = imread("../images/liuyifei_1.png");
    Mat src_copy = src.clone();
    int height = src.rows;
    int width = src.cols;
    int ch = src.channels();
    imshow("input", src);

    // 直接读取图像像素
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            if (ch == 3) {
                Vec3b bgr = src.at<Vec3b>(row, col);
                bgr[0] = 255 - bgr[0];
                bgr[1] = 255 - bgr[1];
                bgr[2] = 255 - bgr[2];
                src.at<Vec3b>(row, col) = bgr;
            } else if (ch == 1) {
                int gray = src.at<uchar>(row, col);
                src.at<uchar>(row, col) = 255 - gray;
            }
        }
    }
    imshow("output1", src);

    // 指针读取
    Mat result = Mat::zeros(src_copy.size(), src_copy.type());
    int blue = 0, green = 0, red = 0;
    int gray;
    for (int row = 0; row < height; ++row) {
        // curr_row为第row行的首地址，遍历时，前三个字节表示的是第一个像素的BGR值，
        // 注意BGR值顺序，接下来三个字节是第二个像素的值。
        uchar *curr_row = src_copy.ptr<uchar>(row);
        uchar *result_row = result.ptr<uchar>(row);
        for (int col = 0; col < width; ++col) {
            if (ch == 3) {
                blue = *curr_row++;
                green = *curr_row++;
                red = *curr_row++;

                *result_row++ = 255 - blue;
                *result_row++ = 255 - green;
                *result_row++ = 255 - red;
            } else if (ch == 1) {
                gray = *curr_row++;
                *result_row++ = gray;
            }
        }
    }

    imshow("output2", result);

    waitKey(0);
    return 0;
}