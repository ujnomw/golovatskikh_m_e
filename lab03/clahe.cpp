#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using  namespace cv;
using namespace std;
int main() {
    Mat original_image = imread("../pictures/fruits.png");
    int const ROWS = original_image.rows;
    int const COLS = original_image.cols;
    Mat gray_image;
    cvtColor(original_image, gray_image, COLOR_RGB2GRAY);
    vector<int> histData(255, 0);
    int maxElement = 0;
    for (int i_row = 0; i_row < ROWS; i_row++ )
        for (int i_col = 0; i_col < COLS; i_col++ ){
            int color = gray_image.at<uchar>(i_row, i_col);
            maxElement = maxElement < ++histData[color] ? histData[color] : maxElement;
        }
    Mat histImage = Mat(ROWS, COLS, CV_8UC1);
    for (int i = 0; i < 255; i++){
        int color = round(histData[i]* 255./maxElement);

    }

    imshow("grsy", gray_image);
    waitKey(0);
    return 0;
}