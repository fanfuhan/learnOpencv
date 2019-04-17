#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void add_gaussian_noise(Mat &image);

/*
 * 图像去噪
 */
int main() {
    Mat src = imread("../images/test.png");
    Mat src_clone = src.clone();
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 产生高斯噪声
    add_gaussian_noise(src);

    Mat res1, res2, res3, res4;
    // 均值去噪
    blur(src, res1, Size(3, 3));
    imshow("mean_blur", res1);

    // 高斯去噪
    GaussianBlur(src, res2, Size(5, 5), 0);
    imshow("gaussian_blur", res2);

    // 中值去噪
    medianBlur(src, res3, 3);
    imshow("median_blur", res3);

    // 非局部均值去噪
    fastNlMeansDenoisingColored(src, res4);
    imshow("NLmeans_blur", res4);

    waitKey(0);
    return 0;
}

void add_gaussian_noise(Mat &image) {
    Mat noise = Mat::zeros(image.size(), image.type());
    // 产生高斯噪声
    randn(noise, (15, 15, 15), (30, 30, 30));
    Mat dst;
    add(image, noise, dst);
    imshow("gaussian_noise", dst);
    dst.copyTo(image);
}