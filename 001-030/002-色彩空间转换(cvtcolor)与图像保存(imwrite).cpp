#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/*
 * 色彩空间转换和图像保存
 */
int main(){
    Mat src = imread("../images/liuyifei_1.png");

    if (src.empty()){
        cout << "could not load image..." << endl;
        return -1;
    }
    namedWindow("input");
    imshow("input",src);

    Mat dst;
    cvtColor(src,dst,COLOR_BGR2GRAY);
    imwrite("../images/result1.png",dst);
    namedWindow("output gray");
    imshow("output gray",dst);

    waitKey(0);

    return 0;
}
