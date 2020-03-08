#include <iostream>
#include <opencv2/opencv.hpp>
using  namespace cv;
using namespace std;
int main() {
    Mat M(128, 256*3, CV_8UC3 ,Scalar(0));
    for (int i_cols = 0; i_cols < M.cols; i_cols++)
        M.col(i_cols).setTo(i_cols/3);
    Mat M_float, M_float_pow, M_new;
    M.convertTo(M_float, CV_32FC1, 1.0/255.0);
    cv::pow(M_float, 2.2, M_float_pow);
    M_float_pow.convertTo(M_new, CV_8UC3, 255);
    Mat image(256,256*3, CV_8UC3);
    M.copyTo(image(Rect(0,0, M.cols,M.rows)));
    M_new.copyTo( image(Rect(0,128,M_new.cols,M_new.rows)));
    imshow("Result", image);
    waitKey(0);
}
