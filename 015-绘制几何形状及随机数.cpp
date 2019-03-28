#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * 绘制几何形状及随机数
 */
int main() {
    Mat image = Mat::zeros(Size(512, 512), CV_8UC3);
    Rect rect(100, 100, 200, 200);
    // 绘制
    rectangle(image, rect, Scalar(255, 0, 0), 2, LINE_8, 0);
    circle(image, Point(256, 256), 50, Scalar(0, 255, 0), 2, LINE_8, 0);
    ellipse(image, Point(256, 256), Size(150, 50), 360, 0, 360, Scalar(0, 0, 255), 2, LINE_8, 0);
    imshow("image_draw", image);
    // 填充  thickness=-1 or FILLED
    rectangle(image, rect, Scalar(255, 0, 0), FILLED, LINE_8, 0);
    ellipse(image, Point(256, 256), Size(150, 50), 360, 0, 360, Scalar(0, 0, 255), FILLED, LINE_8, 0);
    circle(image, Point(256, 256), 50, Scalar(0, 255, 0), -1, LINE_8, 0);
    imshow("image_fill", image);

    // 随机数
    RNG rng(0xFFFFFF);
    image.setTo(Scalar(0, 0, 0));
    Mat image_copy = image.clone();
    for (int i = 0; i < 100000; ++i) {
        int x1 = rng.uniform(0, 512);
        int y1 = rng.uniform(0, 512);
        int x2 = rng.uniform(0, 512);
        int y2 = rng.uniform(0, 512);

        int b = rng.uniform(0, 256);
        int g = rng.uniform(0, 256);
        int r = rng.uniform(0, 256);

        rect.x = x1;
        rect.y = y1;
        rect.width = x2 - x1;
        rect.height = y2 - y1;
        // LINE_AA 反锯齿
        line(image, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 1, LINE_AA, 0);
        rectangle(image_copy, rect, Scalar(b, g, r), 1, LINE_AA, 0);
        imshow("image_line", image);
        imshow("image_rect", image_copy);
        char c = waitKey(20);
        if (c == 27){
            // ESC
            break;
        }
    }

    waitKey(0);
    return 0;
}