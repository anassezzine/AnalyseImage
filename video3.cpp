#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(){

    cv::namedWindow("Image");
    cv::Mat image = cv::imread("/home/anass/Bureau/FISA/S7/AnalyseImage/IIA_images/images/bear.jpg");
    cv::Mat logo = cv::imread("/home/anass/Bureau/FISA/S7/AnalyseImage/IIA_images/images/smalllogo.png");

    cv::Mat imageROI(image, cv::Rect(image.cols-logo.cols, 
                                    image.rows-logo.rows, 
                                    logo.cols, 
                                    logo.rows));

    logo.copyTo(imageROI);

    cv::imshow("Image", image);
    cv::waitKey(0);

    image= cv::imread("/home/anass/Bureau/FISA/S7/AnalyseImage/IIA_images/images/bear.jpg");

    imageROI = image(cv::Rect(image.cols-logo.cols, 
                            image.rows-logo.rows, 
                            logo.cols, 
                            logo.rows));

    // imageROI = image(cv::Range(image.rows-logo.rows, image.rows), 
    //                  cv::Range(image.cols-logo.cols, image.cols));

    // cv::Mat imageROI = image.rowRange(start, end);
    // cv::Mat imageROI = image.colRange(start, end);


    cv::Mat mask(logo);

    logo.copyTo(imageROI, mask);

    cv::imshow("Image", image);
    cv::waitKey(0);

    return 0;

}

