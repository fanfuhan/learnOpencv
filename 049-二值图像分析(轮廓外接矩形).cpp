#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 二值图像分析(轮廓外接矩形)
 */
int main() {
    Mat src = imread("../images/stuff.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 提取边缘
    Mat binary;
    Canny(src, binary, 80, 160);
    imshow("binary", binary);

    // 膨胀
    Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    dilate(binary, binary, k);

    // 轮廓发现于绘制
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
    for (size_t t = 0; t < contours.size(); ++t) {
        // 最大外接矩形
        Rect rect = boundingRect(contours[t]);
        rectangle(src, rect, Scalar(0, 0, 255));

        // 最小外接矩形
        RotatedRect rrt = minAreaRect(contours[t]);
        Point2f pts[4];
        rrt.points(pts);

        // 绘制旋转矩形与中心位置
        for (int i = 0; i < 4; ++i) {
            line(src, pts[i % 4], pts[(i + 1) % 4], Scalar(0, 255, 0), 2);
        }
        Point2f cpt = rrt.center;
        circle(src, cpt, 2, Scalar(255, 0, 0), 2);
    }

    imshow("contours", src);

    waitKey(0);
    return 0;
}