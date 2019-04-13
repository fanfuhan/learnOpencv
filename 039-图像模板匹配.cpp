#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const float t = 0.95;

/*
 * 图像模板匹配
 */
int main() {
    Mat src = imread("../images/llk.jpg");
    Mat tpl = imread("../images/llk_tpl.png");
    if (src.empty() || tpl.empty()) {
        cout << "could not load image.." << endl;
    }
    imshow("input", src);
    imshow("match_template", tpl);

    int res_h = src.rows - tpl.rows + 1;
    int res_w = src.cols - tpl.cols + 1;
    Mat result = Mat::zeros(Size(res_w, res_h), CV_32FC1);
    matchTemplate(src, tpl, result, TM_CCOEFF_NORMED);
    imshow("result", result);

    for (int row = 0; row < result.rows; ++row) {
        for (int col = 0; col < result.cols; ++col) {
            float v = result.at<float>(row, col);
            if (v > t){
                rectangle(src, Point(col, row),
                        Point(col + tpl.cols, row+tpl.rows), Scalar(255,0,0));
            }
        }
    }
    imshow("template_result", src);

    waitKey(0);
    return 0;
}