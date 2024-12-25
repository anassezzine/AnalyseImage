#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void onMouse(int event, int x, int y, int flags, void* param){
    cv::Mat *im = reinterpret_cast<cv::Mat*>(param);
    switch(event){
        case cv::EVENT_LBUTTONDOWN:
            std::cout << "at (" << x << ", " << y << ") value is: " << static_cast<int>(im->at<uchar>(cv::Point(x, y))) << std::endl;
            break;
    }
}


int main(){

    cv::Mat image;
    std::cout << "This image is " << image.rows << " x " << image.cols << std::endl;

    image = cv::imread("/home/anass/Bureau/FISA/S7/AnalyseImage/image.jpeg", cv::IMREAD_GRAYSCALE);
    if(image.empty()){
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    cv::namedWindow("Original Image");
    cv::imshow("Original Image", image);

    cv::Mat result;
    cv::flip(image, result, 1);

    cv::namedWindow("Output Image");
    cv::imshow("Output Image", result);
    cv::imwrite("output.jpg", result);

    cv::namedWindow("Drawing on an image");
    cv::circle(image,
               cv::Point(200,100),
               65,
               0,
               3);
    cv::putText(image,
                "This is a tree",
                cv::Point(155,150),
                cv::FONT_HERSHEY_SIMPLEX,
                0.4,
                255,
                2);

    cv::imshow("Drawing on an image", image);


    cv::waitKey(0);

    return 0; 
}