#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void process_frame(Mat &image);

RNG rng(12345);

/*
 * 角点检测(Harris角点检测)
 */
int main() {
    Mat src = imread("../images/box.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    process_frame(src);
    imshow("result", src);

    waitKey(0);
    return 0;
}

void process_frame(Mat &image) {
    // detector paraments
    int blockSize = 2;
    int kSize = 3;
    double k = 0.04;

    // detecting corners
    Mat gray, dst;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    cornerHarris(gray, dst, blockSize, kSize, k);

    // normalizing
    Mat dst_norm = Mat::zeros(dst.size(), dst.type());
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX);
    convertScaleAbs(dst_norm, dst_norm);

    // drawing a circle around corners
    for (int row = 0; row < dst_norm.rows; ++row) {
        for (int col = 0; col < dst_norm.cols; ++col) {
            int rsp = dst_norm.at<uchar>(row, col);
            if (rsp > 100) {
                int b = rng.uniform(0, 256);
                int g = rng.uniform(0, 256);
                int r = rng.uniform(0, 256);
                circle(image, Point(row, col), 5, Scalar(b, g, r), 2);
            }
        }
    }
}