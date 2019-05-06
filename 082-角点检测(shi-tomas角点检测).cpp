#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void process_frame(Mat &image);

RNG rng(12345);

/*
 * 角点检测(shi-tomas角点检测)
 */
int main() {
    VideoCapture capture("../images/color_object.mp4");
    if (!capture.isOpened()) {
        cout << "could not open video..." << endl;
        return -1;
    }

    Mat frame;
    while (true) {
        bool ret = capture.read(frame);
        imshow("input", frame);
        if (!ret) break;

        process_frame(frame);
        imshow("result", frame);

        char c = waitKey(5);
        if (c == 27) {
            break;
        }
    }

    waitKey(0);
    return 0;
}

void process_frame(Mat &image) {
    // Detector parameters
    int maxCorners = 100;
    double quality_level = 0.01;
    double minDistance = 0.04;

    // detecting corners
    Mat gray, dst;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    vector<Point2f> corners;
    goodFeaturesToTrack(gray, corners, maxCorners, quality_level,
                        minDistance, Mat(), 3, false);

    // drawing corner
    for (int i = 0; i < corners.size(); ++i) {
        int b = rng.uniform(0, 255);
        int g = rng.uniform(0, 255);
        int r = rng.uniform(0, 255);
        circle(image, corners[i], 5, Scalar(b, g, r), 3);
    }
}