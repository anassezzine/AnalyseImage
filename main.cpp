#include <opencv2/opencv.hpp>
#include <iostream>

void drawIntensityProfile(const cv::Mat& grayImage, int y) {
    const int profileHeight = 300;
    const int profileWidth = grayImage.cols;
    cv::Mat profileImage(profileHeight, profileWidth, CV_8UC3, cv::Scalar(0, 0, 0));

    for (int x = 1; x < profileWidth; x++) {
        int intensity1 = grayImage.at<uchar>(y, x-1);
        int intensity2 = grayImage.at<uchar>(y, x);
        
        int y1 = profileHeight - (intensity1 * profileHeight / 255);
        int y2 = profileHeight - (intensity2 * profileHeight / 255);
        
        cv::line(profileImage, 
                cv::Point(x-1, y1), 
                cv::Point(x, y2), 
                cv::Scalar(255, 255, 255), 
                1);
    }
    
    cv::imshow("Intensity Profile", profileImage);
}

void drawLine(cv::Mat& colorImage, const cv::Mat& grayImage, int y) {
    if (y < 0 || y >= colorImage.rows) {
        std::cout << "Invalid y coordinate!" << std::endl;
        return;
    }

    for (int x = 0; x < colorImage.cols; x++) {
        colorImage.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 255);
    }

    drawIntensityProfile(grayImage, y);
    
    cv::imshow("Image", colorImage);
}

void mouseCallback(int event, int x, int y, int flags, void* param) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        auto* images = reinterpret_cast<std::pair<cv::Mat, cv::Mat>*>(param);
        cv::Mat& colorImage = images->first;
        const cv::Mat& grayImage = images->second;
        
        cv::Mat displayImage = colorImage.clone();
        
        drawLine(displayImage, grayImage, y);
    }
}

int main() {
    cv::Mat grayImage = cv::imread("/home/anass/Bureau/FISA/S7/AnalyseImage/IIA_images/images/road.jpg", cv::IMREAD_GRAYSCALE);
    if (grayImage.empty()) {
        std::cout << "Error: Could not read the image!" << std::endl;
        return -1;
    }

    cv::Mat colorImage;
    cv::cvtColor(grayImage, colorImage, cv::COLOR_GRAY2BGR);

    cv::namedWindow("Image");
    std::pair<cv::Mat, cv::Mat> images(colorImage, grayImage);
    cv::setMouseCallback("Image", mouseCallback, &images);

    cv::imshow("Image", colorImage);

    cv::waitKey(0);
    return 0;
}