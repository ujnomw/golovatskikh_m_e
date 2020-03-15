#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using  namespace cv;
using namespace std;
int main() {
    int white = 255;
    int gray = 127;
    int black = 0;
    Mat images[6];
    int COLS  = 256;
    int ROWS = 256;
    // IMAGE CREATION
    Mat result(2*ROWS, 3*COLS, CV_8UC1);
    images[0] = Mat (256,256, CV_8UC1, white );
    images[1] = Mat (256,256, CV_8UC1, black );
    images[2] = Mat (256,256, CV_8UC1, gray );
    images[3] = Mat (256,256, CV_8UC1, black );
    images[4] = Mat (256,256, CV_8UC1, gray );
    images[5] = Mat (256,256, CV_8UC1, white );
    cv::circle(images[0], cv::Point(127,127), 64, gray, -1);
    cv::circle(images[1], cv::Point(127,127), 64, white, -1);
    cv::circle(images[2], cv::Point(127,127), 64, black, -1);
    cv::circle(images[3], cv::Point(127,127), 64, white, -1);
    cv::circle(images[4], cv::Point(127,127), 64, black, -1);
    cv::circle(images[5], cv::Point(127,127), 64, gray, -1);
    for (int i_cols = 0 ; i_cols < 3; i_cols++ ){
        for (int i_rows = 0; i_rows < 2; i_rows++){
            images[i_cols + i_rows].copyTo(result(Rect(i_cols*COLS, i_rows*ROWS, COLS, ROWS)));
        }
    }
    images[5].copyTo(result(Rect(2*COLS, 1*ROWS, COLS, ROWS)));
    // FILTERING
    Mat_<int> kernel(3,3), kernelT(3,3);;
    kernel << 1, 2, 1, 0, 0 , 0, -1, -2, -1;
    kernelT << 1, 0, -1, 2, 0 , -2, 1, 0 , -1;
    Mat filtered, filteredT, filterComb,filtered_float, filteredT_float;
    filter2D(result, filtered, CV_16S, kernel);
    filter2D(result, filteredT, CV_16S, kernelT);
    Mat filter8u = filtered + 127;
    Mat filterT8u = filteredT + 127;
    filter8u.convertTo(filter8u, CV_8U);
    filterT8u.convertTo(filterT8u, CV_8U);
    filtered = filter8u;
    filteredT = filterT8u;
    filtered.convertTo(filtered_float, CV_32FC1, 1.0/ 255.0);
    filteredT.convertTo(filteredT_float, CV_32FC1, 1.0/ 255.0);
    cv::pow(filtered_float,2,filtered_float);
    cv::pow(filteredT_float,2,filteredT_float);
    filterComb = filtered_float + filteredT_float;
    cv::pow(filterComb,0.5,filterComb);
    // 4 IMAGES
    imshow("result", result);
    imshow("filtered", filtered);
    imshow("filteredt", filteredT);
    imshow("filterComb", filterComb);
    waitKey(0);
    return 0;
}