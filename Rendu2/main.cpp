#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void calculateImageHistogram(const Mat& src, Mat& hist) {
    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = {range};
    calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange, true, false);
}

void displayHistogram(const Mat& histData, const string& title) {
    int histWidth = 800, histHeight = 600;
    int binSize = cvRound((double)histWidth / 256);
    Mat histVisual(histHeight, histWidth, CV_8UC3, Scalar(255, 255, 255));

    normalize(histData, histData, 0, histHeight, NORM_MINMAX);

    for (int i = 0; i < 256; i++) {
        line(histVisual, 
             Point(i * binSize, histHeight), 
             Point(i * binSize, histHeight - cvRound(histData.at<float>(i))), 
             Scalar(0, 0, 255), 
             2);
    }

    imshow(title, histVisual);
}

void adjustImageContrast(const Mat& input, Mat& result) {
    double minIntensity, maxIntensity;
    minMaxLoc(input, &minIntensity, &maxIntensity);
    double scale = 255.0 / (maxIntensity - minIntensity);
    double offset = -minIntensity * scale;
    input.convertTo(result, CV_8UC1, scale, offset);
}

int main() {
    Mat img = imread("AI_totoro.png", IMREAD_GRAYSCALE);
    if (img.empty()) {
        cerr << "Erreur : l'image n'a pas pu être chargée." << endl;
        return -1;
    }

    Mat adjustedImg;
    adjustImageContrast(img, adjustedImg);

    Mat histOrig, histAdjusted;
    calculateImageHistogram(img, histOrig);
    calculateImageHistogram(adjustedImg, histAdjusted);

    imshow("Original Image", img);
    imshow("Adjusted Image", adjustedImg);
    displayHistogram(histOrig, "Original Histogram");
    displayHistogram(histAdjusted, "Adjusted Histogram");

    waitKey(0);
    destroyAllWindows();

    return 0;
}