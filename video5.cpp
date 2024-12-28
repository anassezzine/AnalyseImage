#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

void colorReduce(cv::Mat image, int div=64) {
    int nl = image.rows; // number of lines
    int nc = image.cols * image.channels(); // total number of elements per line

    for (int j = 0; j < nl; j++) {
        // get the address of row j
        uchar* data = image.ptr<uchar>(j);
        for (int i = 0; i < nc; i++) {
            // process each pixel
            data[i] = data[i] / div * div + div / 2;
        }
    }
}

void colorReduceIO(cv::Mat &image, cv::Mat &result, int div=64) {
    int nl = image.rows; // number of lines
    int nc = image.cols; // total number of elements per line
    int nch = image.channels(); // number of channels

    result.create(image.rows, image.cols, image.type());

    for (int j = 0; j < nl; j++) {
        // get the address of row j
        const uchar* data_in = image.ptr<uchar>(j);
        uchar* data_out = result.ptr<uchar>(j);
        for (int i = 0; i < nc * nch; i++) {
            // process each pixel
            data_out[i] = data_in[i] / div * div + div / 2;
        }
    }
}

void colorReduce6(cv::Mat image, int div=64) {
    int nl = image.rows; // number of lines
    int nc = image.cols * image.channels(); // total number of elements per line

    if(image.isContinuous()) {
        nc = nc * nl;
        nl = 1;
    }

    int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);

    uchar mask = 0xFF << n;
    uchar div2 = div >> 1;

    for (int j = 0; j < nl; j++) {
        // get the address of row j
        uchar* data = image.ptr<uchar>(j);
        for (int i = 0; i < nc; i++) {
            // process each pixel
            *data &= mask;
            *data++ += div2;
        }
    } 

}

void colorReduce7(cv::Mat image, int div=64) {
    if(image.isContinuous()) {
        image.reshape(1, 1);
    }

    int nl = image.rows; // number of lines
    int nc = image.cols * image.channels(); // total number of elements per line

    int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
    uchar mask = 0xFF << n;
    uchar div2 = div >> 1;

    for(int j = 0; j < nl; j++) {
        uchar* data = image.ptr<uchar>(j);
        for(int i = 0; i < nc; i++) {
            *data &= mask;
            *data++ += div2;
        }
    }

    
}

int main() {
    cv::Mat image = cv::imread("/home/anass/Bureau/FISA/S7/AnalyseImage/IIA_images/images/boldt.jpg", 1);
    cv::Mat image2 = cv::imread("/home/anass/Bureau/FISA/S7/AnalyseImage/IIA_images/images/boldt.jpg", 1);
    cv::Mat image3 = cv::imread("/home/anass/Bureau/FISA/S7/AnalyseImage/IIA_images/images/boldt.jpg", 1);
    cv::Mat image4 = cv::imread("/home/anass/Bureau/FISA/S7/AnalyseImage/IIA_images/images/boldt.jpg", 1);
    colorReduce(image);
    colorReduce6(image2);
    colorReduce7(image3);

    cv::Mat result;
    colorReduceIO(image4, result);


    cv::imshow("Image", image);
    cv::imshow("Image2", image2);
    cv::imshow("Image3", image3);
    cv::imshow("Image4", result);
    cv::waitKey(0);

    return 0;
}