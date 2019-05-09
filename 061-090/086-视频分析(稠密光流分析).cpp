#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 视频分析(稠密光流分析)
 */
int main() {
    VideoCapture capture("../images/vtest.avi");
    if (!capture.isOpened()) {
        cout << "could not open video..." << endl;
        return -1;
    }

    // 读取第一帧
    Mat preFrame, preGray;
    capture.read(preFrame);
    cvtColor(preFrame, preGray, COLOR_BGR2GRAY);

    // 进行色彩展示
    Mat hsv = Mat::zeros(preFrame.size(), preFrame.type());
    vector<Mat> mv;
    split(hsv, mv); //将hsv三通道分离
    Mat mag = Mat::zeros(hsv.size(), CV_32FC1);
    Mat ang = Mat::zeros(hsv.size(), CV_32FC1);
    Mat xpts = Mat::zeros(hsv.size(), CV_32FC1);
    Mat ypts = Mat::zeros(hsv.size(), CV_32FC1);

    // 光流参数
    Mat frame, gray;
    Mat_<Point2f> flow;

    while (true) {
        bool ret = capture.read(frame);
        if (!ret) break;
        imshow("frame", frame);
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        // 计算稠密光流
        calcOpticalFlowFarneback(preGray, gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
        for (int row = 0; row < flow.rows; row++)
        {
            for (int col = 0; col < flow.cols; col++)
            {
                const Point2f& flow_xy = flow.at<Point2f>(row, col);
                xpts.at<float>(row, col) = flow_xy.x;
                ypts.at<float>(row, col) = flow_xy.y;
            }
        }
        // 将光流坐标转化到极坐标下
        cartToPolar(xpts, ypts, mag, ang);
        ang = ang * 180.0 / CV_PI / 2.0;
        normalize(mag, mag, 0, 255, NORM_MINMAX);
        convertScaleAbs(mag, mag);
        convertScaleAbs(ang, ang);
        mv[0] = ang;
        mv[1] = Scalar(255);
        mv[2] = mag;
        merge(mv, hsv);  // 三通道合并
        Mat bgr;
        cvtColor(hsv, bgr, COLOR_HSV2BGR);
        imshow("result", bgr);

        int ch = waitKey(5);
        if (ch == 27) {
            break;
        }
    }

    waitKey(0);
    return 0;
}