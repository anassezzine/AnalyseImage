#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


int main(){

    cv::Mat image = cv::imread("/home/anass/Bureau/FISA/S7/AnalyseImage/IIA_images/images/boldt.jpg");  
    if(!image.data) return 0;

    cv::Rect rectangle(50, 25, 210, 180);

    cv::Mat result;
    cv::Mat bgModel, fgModel;

    cv::grabCut(image, result, rectangle, bgModel, fgModel, 5, cv::GC_INIT_WITH_RECT);
    cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
    cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));

    image.copyTo(foreground, result);
    cv::rectangle(image, rectangle, cv::Scalar(255, 255, 255), 1);

    cv::namedWindow("Image");
    cv::imshow("Image", image);
    cv::namedWindow("Result");
    cv::imshow("Result", foreground);
    cv::waitKey(0);

}