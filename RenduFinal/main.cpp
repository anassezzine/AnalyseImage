#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;
using namespace cv;
using namespace std;

int filterSize = 1;
int scalingFactor = 1;
int offset = 0;
int minEdgeThreshold = 50;
int maxEdgeThreshold = 150;

string selectedFilter = "sobel";
Mat inputImage, outputImage;

void applySobel(const Mat& source, Mat& destination, int size, int scale, int delta) {
    Mat gradientX, gradientY;
    Mat absGradientX, absGradientY;

    Sobel(source, gradientX, CV_16S, 1, 0, size, scale, delta);
    Sobel(source, gradientY, CV_16S, 0, 1, size, scale, delta);

    convertScaleAbs(gradientX, absGradientX);
    convertScaleAbs(gradientY, absGradientY);

    addWeighted(absGradientX, 0.5, absGradientY, 0.5, 0, destination);
}

void applyLaplacian(const Mat& source, Mat& destination, int size, int scale, int delta) {
    Mat laplaceResult;
    Laplacian(source, laplaceResult, CV_16S, size, scale, delta);
    convertScaleAbs(laplaceResult, destination);
}

void applyCanny(const Mat& source, Mat& destination, int lowThresh, int highThresh) {
    Canny(source, destination, lowThresh, highThresh);
}

void refreshEdges(int, void*) {
    if (inputImage.empty()) return;

    if (selectedFilter == "sobel") {
        if (filterSize % 2 == 0) filterSize++;
        applySobel(inputImage, outputImage, filterSize, scalingFactor, offset);
    } else if (selectedFilter == "laplacian") {
        if (filterSize % 2 == 0) filterSize++;
        applyLaplacian(inputImage, outputImage, filterSize, scalingFactor, offset);
    } else if (selectedFilter == "canny") {
        applyCanny(inputImage, outputImage, minEdgeThreshold, maxEdgeThreshold);
    }

    imshow("Edge Detection Result", outputImage);
}

bool checkNeighborhood(const Mat& refImage, int x, int y, Mat& refMask) {
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < refImage.cols && ny >= 0 && ny < refImage.rows) {
                if (refImage.at<uchar>(ny, nx) == 0 && refMask.at<uchar>(ny, nx) == 0) {
                    refMask.at<uchar>(ny, nx) = 255;
                    return true;
                }
            }
        }
    }
    return false;
}

void evaluateDetection(const Mat& detected, const Mat& reference) {
    if (detected.size() != reference.size() || detected.type() != reference.type()) {
        cout << "Error: Images must have the same size and type for comparison." << endl;
        return;
    }

    int detectedEdges = 0;
    int referenceEdges = 0;
    int correctEdges = 0;

    Mat referenceMask = Mat::zeros(reference.size(), CV_8U);

    for (int y = 0; y < detected.rows; ++y) {
        for (int x = 0; x < detected.cols; ++x) {
            uchar detectedPixel = detected.at<uchar>(y, x);

            if (detectedPixel > 0) {
                detectedEdges++;
                if (checkNeighborhood(reference, x, y, referenceMask)) {
                    correctEdges++;
                }
            }

            if (reference.at<uchar>(y, x) == 0) {
                referenceEdges++;
            }
        }
    }

    int falsePositives = detectedEdges - correctEdges;
    int falseNegatives = referenceEdges - correctEdges;

    double accuracy = correctEdges / (double)(correctEdges + falsePositives + falseNegatives);
    double fpRate = falsePositives / (double)(correctEdges + falsePositives + falseNegatives);
    double fnRate = falseNegatives / (double)(correctEdges + falsePositives + falseNegatives);

    cout << "Detected Edges: " << detectedEdges << endl;
    cout << "Reference Edges: " << referenceEdges << endl;
    cout << "Correct Edges: " << correctEdges << endl;
    cout << "False Positives: " << falsePositives << endl;
    cout << "False Negatives: " << falseNegatives << endl;
    cout << "Accuracy: " << accuracy << endl;
    cout << "False Positive Rate: " << fpRate << endl;
    cout << "False Negative Rate: " << fnRate << endl;
    cout << "*************************************************************" << endl;
}

void analyzeImage(const string& path, const string& method) {
    inputImage = imread(path, IMREAD_GRAYSCALE);
    if (inputImage.empty()) {
        cout << "Could not open or find the image: " << path << endl;
        return;
    }

    selectedFilter = method;

    namedWindow("Edge Detection Result", WINDOW_AUTOSIZE);

    if (method == "sobel" || method == "laplacian") {
        createTrackbar("Filter Size", "Edge Detection Result", nullptr, 31, [](int pos, void*) {
            filterSize = pos % 2 == 0 ? pos + 1 : pos;
            refreshEdges(0, nullptr);
        });
        createTrackbar("Scaling Factor", "Edge Detection Result", nullptr, 10, [](int pos, void*) {
            scalingFactor = pos;
            refreshEdges(0, nullptr);
        });
        createTrackbar("Offset", "Edge Detection Result", nullptr, 100, [](int pos, void*) {
            offset = pos;
            refreshEdges(0, nullptr);
        });
    } else if (method == "canny") {
        createTrackbar("Min Threshold", "Edge Detection Result", nullptr, 255, [](int pos, void*) {
            minEdgeThreshold = pos;
            refreshEdges(0, nullptr);
        });
        createTrackbar("Max Threshold", "Edge Detection Result", nullptr, 255, [](int pos, void*) {
            maxEdgeThreshold = pos;
            refreshEdges(0, nullptr);
        });
    }

    refreshEdges(0, nullptr);
    waitKey(0);
}

int main() {
    vector<string> imageFiles;
    vector<string> referenceFiles;
    string imageDirectory = "images/";
    string referenceDirectory = "refs/";

    for (const auto& entry : fs::directory_iterator(imageDirectory)) {
        if (entry.is_regular_file()) {
            imageFiles.push_back(entry.path().string());
        }
    }

    for (const auto& entry : fs::directory_iterator(referenceDirectory)) {
        if (entry.is_regular_file()) {
            referenceFiles.push_back(entry.path().string());
        }
    }

    if (imageFiles.empty() || referenceFiles.empty()) {
        cout << "No images found in the directories." << endl;
        return -1;
    }

    if (imageFiles.size() != referenceFiles.size()) {
        cout << "Mismatch: The number of images in 'images' and 'references' directories must be the same." << endl;
        return -1;
    }

    int selection;
    cout << "Choose edge detection method:\n1. Sobel\n2. Laplacian\n3. Canny\n";
    cin >> selection;

    string method;
    switch (selection) {
        case 1: method = "sobel"; break;
        case 2: method = "laplacian"; break;
        case 3: method = "canny"; break;
        default:
            cout << "Invalid selection!" << endl;
            return -1;
    }

    for (size_t i = 0; i < imageFiles.size(); ++i) {
        analyzeImage(imageFiles[i], method);

        Mat referenceImage = imread(referenceFiles[i], IMREAD_GRAYSCALE);

        if (!referenceImage.empty() && !outputImage.empty()) {
            evaluateDetection(outputImage, referenceImage);
        } else {
            cout << "Reference image missing or invalid for: " << imageFiles[i] << endl;
        }
    }

    return 0;
}