#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/*
 * 图像对象创建和赋值
 */
int main(){
    Mat src = imread("../images/liuyifei_1.png");

    // 通过克隆或复制创建图像对象，m1和src指向不同内存块
    Mat m1 = src.clone();
    Mat m2;
    src.copyTo(m2);

    // 赋值法，m3和src指向同一内存块
    Mat m3 = src;

    // 创建空白图像
    Mat m4 = Mat::zeros(src.size(),src.type());
    Mat m5 = Mat::zeros(Size(512,512),CV_8UC3);
    Mat m6 = Mat::ones(Size(512,512),CV_8UC3);

    // kernel: [0, -1, 0
    //          -1, 5, -1
    //          0, -1, 0]
    Mat kernel = (Mat_<char>(3,3)<<0,-1,0,-1,5,-1,0,-1,0);

    waitKey(0);
    return 0;
}