#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using  namespace cv;
using namespace std;
int main() {
    Mat original_image = imread("../pictures/apple_256x256.png");
    vector<int> save_params;
    save_params.push_back(IMWRITE_JPEG_QUALITY);
    save_params.push_back(65);
    // default quality is 95
    imwrite("../pictures/apple_95_quality.jpeg", original_image);
    imwrite("../pictures/apple_65_quality.jpeg", original_image, save_params);
    return 0;
}