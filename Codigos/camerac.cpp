#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int, char**)
{
	Mat frame; 
	
	VideoCapture cap;
	
	int deviceID = 0;
	int apiID = cv::CAP_ANY;
	
	cap.open(deviceID, apiID);
	
	
	if(!cap.isOpened()){
		cerr << "ERROR! Unable to open camera\n";
		return -1;
		}
	
	cout << "Start grabbing" << endl
	<< "Press any key to terminate" << endl;
	
	for (;;)
	{
	
	cap.read(frame);
	
	if(frame.empty()){
		cerr << "ERROR! blank frame grabbed\n";
	break;
	}
	
	
	imshow ("Live", frame);
	
	if (waitKey(0) >= 0)
	break;
	}
	while (1)
    {
       cap.grab();
        cap.retrieve("../Imagem/fteste.jpg");
        imshow("webcam input", "../Imagem/fteste.jpg");
        string filename = "frame" + to_string(frameNumber) + ".jpg";
        imwrite(filename, output);
        frameNumber++;
        char c = (char)waitKey(10);
        if (c == 27)
           break;
    }
	return 0;
	
}	
