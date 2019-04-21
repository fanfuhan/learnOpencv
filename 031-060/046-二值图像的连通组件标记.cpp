#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

RNG rng(12345);

void connected_component_demo(Mat &image);

/*
 * 二值图像的连通组件标记
 */
int main() {
    Mat src = imread("../images/rice.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    connected_component_demo(src);

    waitKey(0);
    return 0;
}

void connected_component_demo(Mat &image) {
    // extract labels
    Mat gray, binary;
    GaussianBlur(image, image, Size(3, 3), 0);
    cvtColor(image, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    Mat labels = Mat::zeros(image.size(), CV_32S);
    int num_labels = connectedComponents(binary, labels, 8, CV_32S);
    cout << "total labels : " << num_labels - 1 << endl;
    vector<Vec3b> colors(num_labels);

    // 背景颜色
    colors[0] = Vec3b(0, 0, 0);

    // 目标颜色
    for (int i = 1; i < num_labels; ++i) {
        colors[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
    }

    // 给结果着色
    Mat dst = Mat::zeros(image.size(), image.type());
    for (int row = 0; row < image.rows; ++row) {
        for (int col = 0; col < image.cols; ++col) {
            int label = labels.at<int>(row, col);
            if (label == 0) continue;
            dst.at<Vec3b>(row, col) = colors[label];
        }
    }

    imshow("result", dst);
}