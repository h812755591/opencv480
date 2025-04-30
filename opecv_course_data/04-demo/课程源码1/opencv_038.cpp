#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void process_frame(Mat &image);
int main(int argc, char** argv) {
	VideoCapture capture("D:/images/video/color_object.mp4");
	if (!capture.isOpened()) {
		printf("could not open the camera...\n");
	}
	namedWindow("frame", WINDOW_AUTOSIZE);
	Mat frame;
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		imshow("frame", frame);
		process_frame(frame);
		char c = waitKey(1);
		if (c == 27) { // ESC
			break;
		}
	}
	capture.release();

	waitKey(0);
	destroyAllWindows();
}

void process_frame(Mat &image) {
	Mat hsv, mask;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	inRange(hsv, Scalar(0, 43, 46), Scalar(10, 255, 255), mask);
	Mat se = getStructuringElement(MORPH_RECT, Size(15, 15));
	morphologyEx(mask, mask, MORPH_OPEN, se);

	vector<vector<Point>> contours;
	vector<Vec4i> hirearchy;
	findContours(mask, contours, hirearchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
	int index = -1;
	double max_area = 0;
	for (size_t t = 0; t < contours.size(); t++) {
		double area = contourArea(contours[t]);
		if (area > max_area) {
			max_area = area;
			index = t;
		}
	}

	// 进行轮廓离合于输出
	if (index >= 0) {
		RotatedRect rrt = minAreaRect(contours[index]);
		ellipse(image, rrt, Scalar(255, 0, 0), 2, 8);
		circle(image, rrt.center, 4, Scalar(0, 255, 0), 2, 8, 0);
	}
	imshow("color object detection", image);
}
