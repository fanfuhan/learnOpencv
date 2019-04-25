#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void process_frame(Mat &image, int opts);

/*
 * 视频读取与处理
 */
int main() {
    VideoCapture capture("../images/roadcars.avi");
    if (!capture.isOpened()){
        cout << "could not open video.." << endl;
        return -1;
    }
    namedWindow("input");

    int fps = capture.get(CAP_PROP_FPS);
    int width = capture.get(CAP_PROP_FRAME_WIDTH);
    int height = capture.get(CAP_PROP_FRAME_HEIGHT);
    int num_of_frames = capture.get(CAP_PROP_FRAME_COUNT);
    printf("frame width: %d, frame height: %d, FPS : %d \n", width, height, fps);

    Mat frame;
    int index = 0;
    while(capture.isOpened()){
        bool ret = capture.read(frame);
        if (!ret) break;
        imshow("input", frame);
        char c = waitKey(50);
        if (c >= 49){
            index = c - 49;
        }
        process_frame(frame, index);
        imshow("result", frame);
        if (c == 27){
            break;
        }
    }

    waitKey(0);
    return 0;
}

void process_frame(Mat &image, int opts) {
    Mat dst = image.clone();
    if (opts == 0){
        bitwise_not(image, dst);
    }
    if (opts == 1){
        GaussianBlur(image, dst, Size(0,0), 15);
    }
    if (opts == 2){
        Canny(image, dst, 100, 200);
    }
    dst.copyTo(image);
    dst.release();
}