#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void pyramid_up(Mat &image, vector<Mat> &pyramid_images, int level);
void pyramid_down(vector<Mat> &pyramid_images);

/*
 * 图像金字塔
 */
int main() {
    Mat src = imread("../images/test1.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    vector<Mat> p_images;
    pyramid_up(src, p_images, 2);
    pyramid_down(p_images);

    waitKey(0);
    return 0;
}

void pyramid_down(vector<Mat> &pyramid_images) {
    for (int i = pyramid_images.size() - 1; i > -1; --i) {
        Mat dst;
        pyrUp(pyramid_images[i], dst);
        imshow(format("pyramid_down_%d", i), dst);
    }
}

void pyramid_up(Mat &image, vector<Mat> &pyramid_images, int level) {
    Mat temp = image.clone();
    Mat dst;
    for (int i = 0; i < level; ++i) {
        pyrDown(temp, dst);
        imshow(format("pyramid_up_%d", i), dst);
        temp = dst.clone();
        pyramid_images.push_back(temp);
    }
}