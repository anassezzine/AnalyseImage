#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(){

    cv::Mat image1;
    cv::Mat image2;

    image1 = cv::imread("IIA_images/images/boldt.jpg");
    image2 = cv::imread("IIA_images/images/rain.jpg");

    if(!image1.data){
        return 0;
    }
    if(!image2.data){
        return 0;
    }

    cv::namedWindow("Image1");
    cv::imshow("Image1", image1);
    cv::namedWindow("Image2");
    cv::imshow("Image2", image2);

    cv::Mat result;

    cv::addWeighted(image1, 0.7, image2, 0.9, 0, result);

    cv::namedWindow("Result");
    cv::imshow("Result", result);


    result = 0.7*image1 + 0.9*image2;
    cv::namedWindow("Result2");
    cv::imshow("Result2", result);

    image2 = cv::imread("IIA_images/images/rain.jpg", 0);

    std::vector<cv::Mat> planes;

    cv::split(image1, planes);
    planes[0] += image2;

    cv::merge(planes, result);
    cv::namedWindow("Result3");
    cv::imshow("Result3", result);




    cv::waitKey(0);

}