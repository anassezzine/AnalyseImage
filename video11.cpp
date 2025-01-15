#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include<math.h>

void wave(const cv::Mat &image, cv::Mat &result){

    cv::Mat srcX(image.rows, image.cols, CV_32F);
    cv::Mat srcY(image.rows, image.cols, CV_32F);

    for(int i=0; i<image.rows; i++){
        for(int j=0; j<image.cols; j++){
            srcX.at<float>(i,j) = j;
            srcY.at<float>(i,j) = i + 3*sin(j/6.0);

            //srcX.at<float>(i,j) = image.cols - j -1;
            //srcY.at<float>(i,j) = i;
        }
    }
    cv::remap(image, result, srcX, srcY, cv::INTER_LINEAR);
}


int main(){

    cv::Mat image = cv::imread("IIA_images/images/boldt.jpg", 0);
    cv::Mat result;
    wave(image, result);

    cv::namedWindow("Image");
    cv::imshow("Image", image);

    cv::namedWindow("Image - wave");
    cv::imshow("Image - wave", result);

    cv::waitKey(0);

    return 0;
}

