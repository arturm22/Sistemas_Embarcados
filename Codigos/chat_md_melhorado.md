#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

using namespace cv;

int main() {
    Mat img = imread("4.jpg", IMREAD_COLOR);
    resize(img, img, Size(620, 480));

    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    bilateralFilter(gray, gray, 11, 17, 17);
    Mat edged;
    Canny(gray, edged, 30, 200);

    vector<vector<Point>> cnts;
    findContours(edged.clone(), cnts, RETR_TREE, CHAIN_APPROX_SIMPLE);
    cnts = imutils::grab_contours(cnts);
    sort(cnts.begin(), cnts.end(), [](const vector<Point>& a, const vector<Point>& b) {
        return contourArea(a) > contourArea(b);
    });
    vector<Point> screenCnt;

    for (const auto& c : cnts) {
        double peri = arcLength(c, true);
        vector<Point> approx;
        approxPolyDP(c, approx, 0.018 * peri, true);

        if (approx.size() == 4) {
            screenCnt = approx;
            break;
        }
    }

    int detected = 0;
    if (!screenCnt.empty()) {
        detected = 1;
        drawContours(img, vector<vector<Point>>{screenCnt}, -1, Scalar(0, 255, 0), 3);

        Mat mask = Mat::zeros(gray.size(), CV_8UC1);
        drawContours(mask, vector<vector<Point>>{screenCnt}, 0, Scalar(255), -1);
        Mat newImage;
        bitwise_and(img, img, newImage, mask);

        Rect cropRect = boundingRect(screenCnt);
        Mat cropped = gray(cropRect);

        // Pré-processamento adicional na imagem recortada para melhorar o reconhecimento de letras
        Mat blurred;
        GaussianBlur(cropped, blurred, Size(5, 5), 0);
        Mat thresholded;
        threshold(blurred, thresholded, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

        tesseract::TessBaseAPI tess;
        tess.Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
        tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
        tess.SetImage((uchar*)thresholded.data, thresholded.cols, thresholded.rows, 1, thresholded.cols);

        char* outText = tess.GetUTF8Text();
        printf("Detected Number is: %s\n", outText);

        imshow("image", img);
        imshow("Cropped", cropped);
        imshow("Thresholded", thresholded);
    } else {
        printf("No contour detected\n");
    }

    waitKey(0);
    destroyAllWindows();

    return 0;
}
