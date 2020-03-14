#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using  namespace cv;
using namespace std;
int main() {
    Mat original_image = imread("../pictures/fruits.png");
    const int COLS = original_image.cols;
    const int ROWS = original_image.rows;
    Mat quality_65_image = imread("../pictures/fruits_65_quality.jpeg");
    Mat quality_95_image = imread("../pictures/fruits_95_quality.jpeg");
    Mat result(2*original_image.rows, 5*original_image.cols, CV_8UC3);
    quality_65_image.copyTo(result(Rect(4*COLS, 0*ROWS, COLS, ROWS)));
    quality_95_image.copyTo(result(Rect(4*COLS, 1*ROWS, COLS, ROWS)));
    vector<Mat> images[3];
//    images.push_back(quality_65_image);
//    images.push_back(quality_95_image);
    Mat diff;
    Mat q65_chans[3], q95_chans[3];
    absdiff(original_image, quality_65_image, diff);
    split(diff, q65_chans);
    absdiff(original_image, quality_95_image, diff);
    split(diff, q95_chans);
    for (int i = 0; i < 3 ; i++){
        Mat q65_cur_chans[3], q65_cur_image;
        Mat q95_cur_chans[3], q95_cur_image;
        for (int i_chanel = 0; i_chanel < 3; i_chanel++) {
            q65_cur_chans[i_chanel] = i_chanel == i ? q65_chans[i_chanel] : Mat::zeros(ROWS, COLS, CV_8UC1);
            q95_cur_chans[i_chanel] = i_chanel == i ? q95_chans[i_chanel] : Mat::zeros(ROWS, COLS, CV_8UC1);
        }
        merge(q65_cur_chans,3, q65_cur_image);
        q65_cur_image.copyTo(result(Rect( i*COLS, 0, COLS, ROWS )));
        merge(q95_cur_chans,3, q95_cur_image);
        q95_cur_image.copyTo(result(Rect( i*COLS, ROWS, COLS, ROWS )));
    }
    Mat hsv_original, hsv_q65, hsv_q95;
    cvtColor(original_image, hsv_original, COLOR_BGR2HSV);
    cvtColor(quality_65_image, hsv_q65, COLOR_BGR2HSV);
    cvtColor(quality_95_image, hsv_q95, COLOR_BGR2HSV);
    Mat q65_diff_hsv, q95_diff_hsv;
    absdiff(hsv_original, hsv_q65, q65_diff_hsv);
    absdiff(hsv_original, hsv_q95, q95_diff_hsv);
    Mat hsv_planes[3];
    vector<Mat> images_hsv;
    images_hsv.push_back(q65_diff_hsv);
    images_hsv.push_back(q95_diff_hsv);
    for (int i = 0; i < 2; i++){
        Mat cur_image = images_hsv[i];
        cv::split(cur_image, hsv_planes);
        hsv_planes[0] = hsv_planes[1] =  Mat::zeros(ROWS, COLS, CV_8UC1);
        cv::merge(hsv_planes, 3, cur_image);
        cvtColor(cur_image, cur_image, COLOR_HSV2BGR);
        cur_image.copyTo(result(Rect(3*COLS, i*ROWS, COLS, ROWS)));
    }
    imshow("res", result);
    waitKey(0);
}