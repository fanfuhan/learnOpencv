#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<Point2f> featurePoints;
vector<Scalar> color_lut;
RNG rng(12345);

void draw_lines(Mat &image, vector<Point2f> pt1, vector<Point2f> pt2);

/*
 * 视频分析(移动对象的KLT光流跟踪算法_删除静止点与绘制跟踪轨迹)
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
    vector<Point2f> initPoints;

    // 读取第一帧及其角点
    Mat old_frame, old_gray;
    capture.read(old_frame);
    cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
    goodFeaturesToTrack(old_gray, featurePoints, maxCorners,
                        qualityLevel, minDistance, Mat());

    pts[0].insert(pts[0].end(), featurePoints.begin(), featurePoints.end());
    initPoints.insert(initPoints.end(), featurePoints.begin(), featurePoints.end());
    int width = capture.get(CAP_PROP_FRAME_WIDTH);
    int height = capture.get(CAP_PROP_FRAME_HEIGHT);

    VideoWriter writer("D:/test.mp4", VideoWriter::fourcc('D', 'I', 'V', 'X'),
            10, Size(width * 2, height), true);
    Mat result = Mat::zeros(Size(width * 2, height), CV_8UC3);
    Rect roi(0, 0, width, height);

    Mat gray, frame;

    while (true) {
        bool ret = capture.read(frame);
        if (!ret) break;
        imshow("frame", frame);
        roi.x = 0;
        frame.copyTo(result(roi));
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // 计算光流
        calcOpticalFlowPyrLK(old_gray, gray, pts[0], pts[1],
                             status, err, Size(31, 31));
        size_t i, k;
        for (int i = k = 0; i < pts[1].size(); ++i) {
            // 距离与状态测量,删除静止点
            double dist = abs(pts[0][i].x - pts[1][i].x) +
                          abs(pts[0][i].y - pts[1][i].y);
            if (status[i] && dist > 2) {
                pts[0][k] = pts[0][i];
                initPoints[k] = initPoints[i];
                pts[1][k++] = pts[1][i];
                circle(frame, pts[1][i], 4, Scalar(0, 255, 0), -1);
            }
        }

        // resize 有用特征点
        pts[0].resize(k);
        pts[1].resize(k);
        initPoints.resize(k);

        // 绘制跟踪轨迹
        draw_lines(frame, initPoints, pts[1]);
        imshow("result", frame);
        roi.x = width;
        frame.copyTo(result(roi));
        char c = waitKey(50);
        if (c == 27) break;

        // 更新old
        std::swap(pts[1], pts[0]);
        cv::swap(old_gray, gray);

        // 重新初始化角点
        if (initPoints.size() < 40){
            goodFeaturesToTrack(old_gray, featurePoints, maxCorners,
                                qualityLevel, minDistance, Mat());
            pts[0].insert(pts[0].end(), featurePoints.begin(), featurePoints.end());
            initPoints.insert(initPoints.end(), featurePoints.begin(), featurePoints.end());
        }
        writer.write(result);
    }

    return 0;
}

void draw_lines(Mat &image, vector<Point2f> pt1, vector<Point2f> pt2) {
    if (color_lut.size() < pt1.size()){
        for (size_t i = 0; i < pt1.size(); ++i) {
            int b = rng.uniform(0, 255);
            int g = rng.uniform(0, 255);
            int r = rng.uniform(0, 255);
            Scalar color(b, g, r);
            color_lut.push_back(color);
        }
    }

    for (size_t j = 0; j < pt1.size(); ++j) {
        line(image, pt1[j], pt2[j], color_lut[j], 2);
    }
}