#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<Point2f> featurePoints;
RNG rng(12345);

/*
 * 视频分析(移动对象的KLT光流跟踪算法)
 */
int main() {
    VideoCapture capture("../images/vtest.avi");
    if (!capture.isOpened()) {
        cout << "could not open video..." << endl;
        return -1;
    }

    // 角点检测参数
    double qualityLevel = 0.01;
    int minDistance = 10;
    int maxCorners = 100;

    // KLT光流跟踪参数
    vector<Point2f> pts[2];
    vector<uchar> status;
    vector<float> err;

    // 读取第一帧及其角点
    Mat old_frame, old_gray;
    capture.read(old_frame);
    cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
    goodFeaturesToTrack(old_gray, featurePoints, maxCorners,
                        qualityLevel, minDistance, Mat());

    pts[0].insert(pts[0].end(), featurePoints.begin(), featurePoints.end());
    int width = capture.get(CAP_PROP_FRAME_WIDTH);
    int height = capture.get(CAP_PROP_FRAME_HEIGHT);
    Rect roi(0, 0, width, height);

    Mat gray, frame;

    while (true) {
        bool ret = capture.read(frame);
        if (!ret) break;
        imshow("frame", frame);
        roi.x = 0;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // 计算光流
        calcOpticalFlowPyrLK(old_gray, gray, pts[0], pts[1],
                             status, err, Size(31, 31));
        size_t i, k;
        for (int i = k = 0; i < pts[1].size(); ++i) {
            // 根据状态选择
            if (status[i]){
                pts[0][k] = pts[0][i];
                pts[1][k++] = pts[1][i];
                int b = rng.uniform(0, 256);
                int g = rng.uniform(0, 256);
                int r = rng.uniform(0, 256);
                Scalar color(b, g, r);
                // 绘制跟踪线
                circle(frame, pts[1][i], 4, color, -1);
                line(frame, pts[0][i], pts[1][i], color, 2);
            }
        }

        // resize 有用特征点
        pts[0].resize(k);
        pts[1].resize(k);
        imshow("result", frame);
        roi.x = width;
        char c = waitKey(50);
        if (c == 27) break;

        // 更新old
        std::swap(pts[1], pts[0]);
        cv::swap(old_gray, gray);
    }

    return 0;
}