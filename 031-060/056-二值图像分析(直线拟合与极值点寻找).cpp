#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 二值图像分析(直线拟合与极值点寻找)
 */
int main() {
    Mat src = imread("../images/twolines.png");
    if (src.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);

    // 去噪声与二值化
    Mat binary;
    Canny(src, binary, 80, 160, 3, false);
    imshow("binary", binary);

    Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    dilate(binary, binary, k);

    // 轮廓发现于绘制
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
    for (size_t t = 0; t < contours.size(); ++t) {
        // 最大外接轮廓
        Rect rect = boundingRect(contours[t]);
        int m = max(rect.width, rect.height);
        if (m < 30) continue;

        // 直线拟合
        Vec4f oneline;
        fitLine(contours[t], oneline, DIST_L1, 0, 0.01, 0.01);
        float dx = oneline[0];
        float dy = oneline[1];
        float x0 = oneline[2];
        float y0 = oneline[3];

        // 直线参数斜率k 和 截距b
        float k = dy / dx;
        float b = y0 - k * x0;

        // 寻找轮廓极值点
        int minx = 0, miny = 10000;
        int maxx = 0, maxy = 0;
        for (int i = 0; i < contours[t].size(); ++i) {
            Point pt = contours[t][i];
            if (miny > pt.y) {
                miny = pt.y;
            }
            if (maxy < pt.y) {
                maxy = pt.y;
            }
            maxx = (maxy - b) / k;
            minx = (miny - b) / k;
            line(src, Point(maxx, maxy), Point(minx, miny), Scalar(0,0,255), 2);
        }
    }

    imshow("contours", src);

    waitKey(0);
    return 0;
}