#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void process_frame(Mat &image);
void process2(Mat &image);
auto pMOG2 = createBackgroundSubtractorMOG2(500, 100, false);
int main(int argc, char** argv) {
	VideoCapture capture("D:/images/video/vtest.avi");
	if (!capture.isOpened()) {
		printf("could not open the camera...\n");
	}
	namedWindow("frame", WINDOW_AUTOSIZE);
	Mat frame;
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		imshow("frame", frame);
		process2(frame);
		char c = waitKey(1);
		if (c == 27) { // ESC
			break;
		}
	}
	capture.release();

	waitKey(0);
	destroyAllWindows();
}

void process2(Mat &image) {
	Mat mask, bg_image;
	pMOG2->apply(image, mask);
	// ÐÎÌ¬Ñ§²Ù×÷
	Mat se = getStructuringElement(MORPH_RECT, Size(1, 5), Point(-1, -1));
	morphologyEx(mask, mask, MORPH_OPEN, se);
	imshow("mask", mask);

	vector<vector<Point>> contours;
	vector<Vec4i> hirearchy;
	findContours(mask, contours, hirearchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
	for (size_t t = 0; t < contours.size(); t++) {
		double area = contourArea(contours[t]);
		if (area < 100) {
			continue;
		}
		Rect box = boundingRect(contours[t]);
		RotatedRect rrt = minAreaRect(contours[t]);
		// rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
		circle(image, rrt.center, 2, Scalar(255, 0, 0), 2, 8, 0);
		ellipse(image, rrt, Scalar(0, 0, 255), 2, 8);
	}
	imshow("result", image);
}

void process_frame(Mat &image) {
	Mat mask, bg_image;
	pMOG2->apply(image, mask);
	pMOG2->getBackgroundImage(bg_image);
	imshow("mask", mask);
	imshow("background", bg_image);
}
