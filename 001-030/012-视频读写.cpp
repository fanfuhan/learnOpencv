#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 视频读写
 */
int main() {
    // 打开摄像头
    // VideoCapture capture(0);
    // 打开视频文件
    VideoCapture capture;
    capture.open("../images/vtest.avi");
    if (!capture.isOpened()) {
        cout << "could not load video.." << endl;
        return -1;
    }

    Size S = Size((int) capture.get(CAP_PROP_FRAME_WIDTH), (int) capture.get(CAP_PROP_FRAME_HEIGHT));
    int fps = capture.get(CAP_PROP_FPS);
    cout << "capture fps: " << fps << endl;
    VideoWriter writer("D:/test.mp4", cv::VideoWriter::fourcc('D', 'I','V','X'), fps, S, true);

    Mat frame;
    while(capture.read(frame)){
        imshow("input", frame);
        writer.write(frame);
        char c = waitKey(50);
        if(c == 27){
            break;
        }
    }
    capture.release();
    writer.release();

    waitKey(0);
    return 0;
}