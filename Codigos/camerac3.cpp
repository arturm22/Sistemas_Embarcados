#include <iostream>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat image, output;
    raspicam::RaspiCam_Cv cap;
    if (!cap.isOpened())
    {
        cout << "Could not initialize capturing...\n";
        return 0;
    }
    int frameNumber = 0;
    while (1)
    {
        cap.grab();
        cap.retrieve(output);
        imshow("webcam input", output);
        string filename = "frame" + to_string(frameNumber) + ".jpg";
        imwrite(filename, output);
        frameNumber++;
        char c = (char)waitKey(10);
        if (c == 27)
            break;
    }
}
