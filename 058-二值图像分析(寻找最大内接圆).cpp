#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 二值图像分析(寻找最大内接圆)
 */
int main() {
    const int r = 100;
    Mat src = Mat::zeros(Size(4 * r, 4 * r), CV_8U);
    vector<Point2f> vert(6);
    vert[0] = Point(3 * r / 2, static_cast<int>(1.34 * r));
    vert[1] = Point(1 * r, 2 * r);
    vert[2] = Point(3 * r / 2, static_cast<int>(2.866 * r));
    vert[3] = Point(5 * r / 2, static_cast<int>(2.866 * r));
    vert[4] = Point(3 * r, 2 * r);
    vert[5] = Point(5 * r / 2, static_cast<int>(1.34 * r));
    for (int i = 0; i < 6; ++i) {
        line(src, vert[i], vert[(i + 1) % 6], Scalar(255), 3);
    }
    imshow("input", src);

    // 点多边形测试
    vector<vector<Point> > contours;
    findContours(src, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
    Mat raw_dist(src.size(), CV_32F);
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            raw_dist.at<float>(i, j) = (float) pointPolygonTest(contours[0],
                                                                Point2f((float) j, (float) i), true);
        }
    }

    // 获取最大内接圆半径
    double minval, maxval;
    Point maxDistPt;// save circle center
    minMaxLoc(raw_dist, &minval, &maxval, NULL, &maxDistPt);
    minval = abs(minval);
    maxval = abs(maxval);

    Mat drawing = Mat::zeros(src.size(), CV_8UC3);
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            if (raw_dist.at<float>(i, j) < 0) {
                drawing.at<Vec3b>(i, j)[0] = (uchar) (255 - abs(raw_dist.at<float>(i, j)) * 255 / minval);
            } else if (raw_dist.at<float>(i, j) > 0) {
                drawing.at<Vec3b>(i, j)[2] = (uchar) (255 - raw_dist.at<float>(i, j) * 255 / maxval);
            } else {
                drawing.at<Vec3b>(i, j)[0] = 255;
                drawing.at<Vec3b>(i, j)[1] = 255;
                drawing.at<Vec3b>(i, j)[2] = 255;
            }
        }
    }

    // 绘制内接圆
    circle(drawing, maxDistPt, (int)maxval, Scalar(255,255,255));
    imshow("distance_inscribed_circle", drawing);

    waitKey(0);
    return 0;
}