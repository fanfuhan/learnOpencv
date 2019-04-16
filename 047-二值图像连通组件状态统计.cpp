#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

RNG rng(12345);

void componentwithstats_demo(Mat &image);

/*
 * 二值图像连通组件状态统计
 */
int main() {
    Mat src = imread("../images/rice.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    componentwithstats_demo(src);

    waitKey(0);
    return 0;
}

void componentwithstats_demo(Mat &image) {
    // extract labels
    Mat gray, binary;
    GaussianBlur(image, image, Size(3, 3), 0);
    cvtColor(image, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    Mat labels = Mat::zeros(image.size(), CV_32S);
    Mat stats, centroids;
    int num_labels = connectedComponentsWithStats(binary, labels, stats, centroids, 8, 4);
    cout << "total labels : " << num_labels - 1 << endl;
    vector<Vec3b> colors(num_labels);

    // 背景颜色
    colors[0] = Vec3b(0, 0, 0);

    // 目标颜色
    for (int i = 1; i < num_labels; ++i) {
        colors[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
    }

    // 抽取统计信息
    Mat dst = image.clone();
    for (int i = 1; i < num_labels; ++i) {
        // 中心位置
        int cx = centroids.at<double>(i, 0);
        int cy = centroids.at<double>(i, 1);

        // 统计信息
        int x = stats.at<int>(i, CC_STAT_LEFT);
        int y = stats.at<int>(i, CC_STAT_TOP);
        int w = stats.at<int>(i, CC_STAT_WIDTH);
        int h = stats.at<int>(i, CC_STAT_HEIGHT);
        int area = stats.at<int>(i, CC_STAT_AREA);

        // 中心位置绘制
        circle(dst, Point(cx, cy), 2, Scalar(0, 255, 0), 2);

        // 外接矩形
        Rect rect(x, y, w, h);
        rectangle(dst, rect, colors[i]);
        putText(dst, format("num:%d", i), Point(x, y), FONT_HERSHEY_SIMPLEX,
                .5, Scalar(0, 0, 255), 1);
        printf("num : %d, rice area : %d\n", i, area);
    }

    imshow("result", dst);
}