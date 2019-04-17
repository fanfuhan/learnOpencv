#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void add_salt_pepper_noise(Mat &image);

void add_gaussian_noise(Mat &image);

/*
 * 噪声生成
 */
int main() {
    Mat src = imread("../images/test.png");
    Mat src_clone = src.clone();
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    //imshow("input", src);

    // 产生椒盐噪声
    add_salt_pepper_noise(src_clone);
    // 产生高斯噪声
    add_gaussian_noise(src);

    waitKey(0);
    return 0;
}

void add_gaussian_noise(Mat &image) {
    Mat noise = Mat::zeros(image.size(), image.type());
    // 产生高斯噪声
    randn(noise, (15,15,15), (30,30,30));
    Mat dst;
    add(image, noise, dst);
    imshow("gaussian_noise", dst);
}

void add_salt_pepper_noise(Mat &image) {
    // 随机数产生器
    RNG rng(12345);
    for (int i = 0; i < 1000; ++i) {
        int x = rng.uniform(0, image.rows);
        int y = rng.uniform(0, image.cols);
        if (i % 2 == 1) {
            image.at<Vec3b>(y, x) = Vec3b(255, 255, 255);
        } else {
            image.at<Vec3b>(y, x) = Vec3b(0, 0, 0);
        }
    }
    imshow("saltp_epper", image);
}