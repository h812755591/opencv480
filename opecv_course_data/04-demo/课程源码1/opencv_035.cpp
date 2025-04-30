#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	VideoCapture capture("D:/images/video/01.mp4");
	if (!capture.isOpened()) {
		printf("could not open the camera...\n");
		return -1;
	}
	namedWindow("frame", WINDOW_AUTOSIZE);

	Mat frame, hsv, mask, result;
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		imshow("frame", frame);
		cvtColor(frame, hsv, COLOR_BGR2HSV);
		imshow("hsv", hsv);
		inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);
		bitwise_not(mask, mask);
		bitwise_and(frame, frame, result, mask);
		imshow("mask", mask);
		imshow("result", result);
		char c = waitKey(5);
		if (c == 27) { // ESC
			break;
		}
	}
	capture.release();

	waitKey(0);
	destroyAllWindows();
}