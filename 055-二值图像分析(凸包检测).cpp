#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 二值图像分析(凸包检测)
 */
int main() {
    Mat src = imread("../images/hand.jpg");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 二值化
    Mat gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // 删除干扰块
    Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    morphologyEx(binary, binary, MORPH_OPEN, k);
    imshow("binary", binary);

    // 轮廓发现与绘制
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
    for (size_t t = 0; t < contours.size(); t++) {
        vector<Point> hull;
        convexHull(contours[t], hull);
        bool isHull = isContourConvex(contours[t]);
        printf("test convex of the contours %s", isHull?"y":"n");
        int len = hull.size();
        for (int i = 0; i < len; ++i) {
            circle(src, hull[i], 4, Scalar(255,0,0), 2);
            line(src, hull[i%len], hull[(i+1)%len], Scalar(0,0,255),2);
        }
    }

    imshow("contours", src);

    waitKey(0);
    return 0;
}