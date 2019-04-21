#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void pyramid_up(Mat &image, vector<Mat> &pyramid_images, int level);

void laplaian_demo(vector<Mat> &pyramid_images, Mat &image);

/*
 * 拉普拉斯金字塔
 */
int main() {
    Mat src = imread("../images/test1.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    vector<Mat> p_images;
    pyramid_up(src, p_images, 2);
    laplaian_demo(p_images, src);

    waitKey(0);
    return 0;
}

void laplaian_demo(vector<Mat> &pyramid_images, Mat &image) {
    for (int i = pyramid_images.size() - 1; i > -1; --i) {
        Mat dst;
        if (i - 1 < 0) {
            pyrUp(pyramid_images[i], dst, image.size());
            subtract(image, dst, dst);
            dst = dst + Scalar(127, 127, 127);
            imshow(format("laplaian_layer_%d", i), dst);
        } else {
            pyrUp(pyramid_images[i], dst, pyramid_images[i-1].size());
            subtract(pyramid_images[i - 1], dst, dst);
            dst = dst + Scalar(127, 127, 127);
            imshow(format("laplaian_layer_%d", i), dst);
        }
    }
}

void pyramid_up(Mat &image, vector<Mat> &pyramid_images, int level) {
    Mat temp = image.clone();
    Mat dst;
    for (int i = 0; i < level; ++i) {
        pyrDown(temp, dst);
        //imshow(format("pyramid_up_%d", i), dst);
        temp = dst.clone();
        pyramid_images.push_back(temp);
    }
}