#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void backProjection_demo(Mat &mat, Mat &model);

/*
 * 图像直方图反向投影
 */
int main() {
    Mat src = imread("../images/target.png");
    Mat model = imread("../images/sample.png");
    if (src.empty() || model.empty()) {
        cout << "could not load image.." << endl;
    }
    namedWindow("model", WINDOW_NORMAL);
    imshow("input", src);
    imshow("model", model);

    backProjection_demo(src, model);

    waitKey(0);
    return 0;
}

void backProjection_demo(Mat &image, Mat &model) {
    Mat image_hsv, model_hsv;
    cvtColor(image, image_hsv, COLOR_BGR2HSV);
    cvtColor(model, model_hsv, COLOR_BGR2HSV);

    // 定义直方图参数与属性
    int h_bins = 32, s_bins = 32;
    int histSize[] = {h_bins, s_bins};
    float h_ranges[] = {0, 180}, s_ranges[] = {0, 256};
    const float* ranges[] = {h_ranges, s_ranges};
    int channels[] = {0, 1};

    Mat roiHist;
    calcHist(&model_hsv, 1, channels, Mat(), roiHist, 2, histSize, ranges);
    normalize(roiHist, roiHist, 0, 255, NORM_MINMAX, -1, Mat());
    MatND backproj;
    calcBackProject(&image_hsv, 1, channels, roiHist, backproj, ranges);
    imshow("BackProj", backproj);
}