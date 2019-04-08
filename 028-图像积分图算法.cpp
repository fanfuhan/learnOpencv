#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void blur_demo(Mat &image, Mat &sum);
void edge_demo(Mat &image, Mat &sum);
int getblockSum(Mat &sum, int x1, int y1, int x2, int y2, int i);

/*
 * 图像积分图算法
 */
int main() {
    Mat src = imread("../images/test.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 计算积分图
    Mat sum, sqrsum;
    integral(src, sum, sqrsum);

    /*
     * 积分图应用
    */
    int type = 0;
    // 模糊应用
    blur_demo(src, sum);
    // 边缘检测
    edge_demo(src, sum);

    waitKey(0);
    return 0;
}

void blur_demo(Mat &image, Mat &sum) {
    int w = image.cols;
    int h = image.rows;
    Mat result = Mat::zeros(image.size(), image.type());
    int x2 = 0, y2 = 0;
    int x1 = 0, y1 = 0;
    int ksize = 5;
    int radius = ksize / 2;
    int ch = image.channels();
    int cx = 0, cy = 0;
    for (int row = 0; row < h + radius; row++) {
        y2 = (row + 1)>h ? h : (row + 1);
        y1 = (row - ksize) < 0 ? 0 : (row - ksize);
        for (int col = 0; col < w + radius; col++) {
            x2 = (col + 1)>w ? w : (col + 1);
            x1 = (col - ksize) < 0 ? 0 : (col - ksize);
            cx = (col - radius) < 0 ? 0 : col - radius;
            cy = (row - radius) < 0 ? 0 : row - radius;
            int num = (x2 - x1)*(y2 - y1);
            for (int i = 0; i < ch; i++) {
                // 积分图查找和表，计算卷积
                int s = getblockSum(sum, x1, y1, x2, y2, i);
                result.at<Vec3b>(cy, cx)[i] = saturate_cast<uchar>(s / num);
            }
        }
    }
    imshow("blur_demo", result);
}
/**
* 3x3 sobel 垂直边缘检测演示
*/
void edge_demo(Mat &image, Mat &sum) {
    int w = image.cols;
    int h = image.rows;
    Mat result = Mat::zeros(image.size(), CV_32SC3);
    int x2 = 0, y2 = 0;
    int x1 = 0, y1 = 0;
    int ksize = 3; // 算子大小，可以修改，越大边缘效应越明显
    int radius = ksize / 2;
    int ch = image.channels();
    int cx = 0, cy = 0;
    for (int row = 0; row < h + radius; row++) {
        y2 = (row + 1)>h ? h : (row + 1);
        y1 = (row - ksize) < 0 ? 0 : (row - ksize);
        for (int col = 0; col < w + radius; col++) {
            x2 = (col + 1)>w ? w : (col + 1);
            x1 = (col - ksize) < 0 ? 0 : (col - ksize);
            cx = (col - radius) < 0 ? 0 : col - radius;
            cy = (row - radius) < 0 ? 0 : row - radius;
            int num = (x2 - x1)*(y2 - y1);
            for (int i = 0; i < ch; i++) {
                // 积分图查找和表，计算卷积
                int s1 = getblockSum(sum, x1, y1, cx, y2, i);
                int s2 = getblockSum(sum, cx, y1, x2, y2, i);
                result.at<Vec3i>(cy, cx)[i] = saturate_cast<int>(s2 - s1);
            }
        }
    }
    Mat dst, gray;
    convertScaleAbs(result, dst);
    normalize(dst, dst, 0, 255, NORM_MINMAX);
    cvtColor(dst, gray, COLOR_BGR2GRAY);
    imshow("edge_demo", gray);
}
int getblockSum(Mat &sum, int x1, int y1, int x2, int y2, int i) {
    int tl = sum.at<Vec3i>(y1, x1)[i];
    int tr = sum.at<Vec3i>(y2, x1)[i];
    int bl = sum.at<Vec3i>(y1, x2)[i];
    int br = sum.at<Vec3i>(y2, x2)[i];
    int s = (br - bl - tr + tl);
    return s;
}