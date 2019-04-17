#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 图像直方图比较
 */
int main() {
    Mat src1 = imread("../images/left01.jpg");
    Mat src2 = imread("../images/left13.jpg");
    if (src1.empty() || src2.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input1", src1);
    imshow("input2", src2);

    // 一般在HSV色彩空间进行计算
    Mat hsv1, hsv2;
    cvtColor(src1, hsv1, COLOR_BGR2HSV);
    cvtColor(src2, hsv2, COLOR_BGR2HSV);

    int h_bins = 60, s_bins = 64;
    int histSize[] = {h_bins, s_bins};
    float h_ranges[] = {0, 180};
    float s_ranges[] = {0, 256};
    const float* ranges[] = {h_ranges, s_ranges};
    int channels[] = {0, 1};
    Mat hist1, hist2;
    calcHist(&hsv1, 1, channels, Mat(), hist1, 2, histSize, ranges);
    calcHist(&hsv2, 1, channels, Mat(), hist2, 2, histSize, ranges);

    normalize(hist1, hist1, 0, 1, NORM_MINMAX, -1, Mat());
    normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat());

    // 比较
    double src1_src2_1 = compareHist(hist1, hist2, HISTCMP_CORREL);
    double src1_src2_2 = compareHist(hist1, hist2, HISTCMP_BHATTACHARYYA);
    printf("HISTCMP_CORREL : %.2f\n", src1_src2_1);
    printf("HISTCMP_BHATTACHARYYA : %.2f\n", src1_src2_1);

    waitKey(0);
    return 0;
}