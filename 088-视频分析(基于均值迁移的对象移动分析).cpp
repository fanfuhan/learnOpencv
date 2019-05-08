#include <opencv2/opencv.hpp>
#include <iostream>
#include <ctype.h>

using namespace cv;
using namespace std;

Mat image;
int trackObject = 0;

/*
 * 视频分析(基于均值迁移的对象移动分析)
 */
int main() {
    VideoCapture cap("../images/balltest.mp4");
    Rect trackWindow;
    int hsize = 16;
    float hranges[] = {0, 180};
    const float *phranges = hranges;

    if (!cap.isOpened()) {
        printf("could not open camera...\n");
        return -1;
    }

    Mat frame, hsv, hue, mask, hist = Mat::zeros(200, 320, CV_8UC3), backproj;
    cap.read(frame);
    Rect selection = selectROI("CamShift Demo", frame, true, false);

    while (true) {
        bool ret = cap.read(frame);
        if (!ret) break;
        frame.copyTo(image);

        cvtColor(image, hsv, COLOR_BGR2HSV);

        inRange(hsv, Scalar(26, 43, 46), Scalar(34, 255, 255), mask);
        int ch[] = {0, 0};
        hue.create(hsv.size(), hsv.depth());
        mixChannels(&hsv, 1, &hue, 1, ch, 1);

        if (trackObject <= 0) {
            // Object has been selected by user, set up CAMShift search properties once
            Mat roi(hue, selection), maskroi(mask, selection);
            calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
            normalize(hist, hist, 0, 255, NORM_MINMAX);

            trackWindow = selection;
            trackObject = 1; // Don't set up again, unless user selects new ROI
        }

        // Perform meanShift
        calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
        backproj &= mask;
        meanShift(backproj, trackWindow, TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1));
        rectangle(image, trackWindow, Scalar(0, 0, 255), 3, LINE_AA);

        imshow("CamShift Demo", image);
        char c = (char) waitKey(50);
        if (c == 27)
            break;
    }

    return 0;
}
