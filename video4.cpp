#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <random>


void salt(cv::Mat image, int n){
    std::default_random_engine generator;
    std::uniform_int_distribution<int> randomRow(0, image.rows-1);
    std::uniform_int_distribution<int> randomCol(0, image.cols-1);
    for(int k=0; k<n; k++){
        int i = randomRow(generator);
        int j = randomCol(generator);
        if(image.type() == CV_8UC1){
            image.at<uchar>(i,j) = 255;
        }else if(image.type() == CV_8UC3){
            image.at<cv::Vec3b>(i,j)[0] = 255;
            image.at<cv::Vec3b>(i,j)[1] = 255;
            image.at<cv::Vec3b>(i,j)[2] = 255;

            //or simply
            //image.at<cv::Vec3b>(i,j) = cv::Vec3b(255,255,255);
        }
    }
}

int main(){
    cv::Mat image = cv::imread("/home/anass/Bureau/FISA/S7/AnalyseImage/IIA_images/images/boldt.jpg", 1);
    salt(image, 3000);

    cv::namedWindow("Image");
    cv::imshow("Image", image);

    cv::waitKey(0);
    return 0;
}