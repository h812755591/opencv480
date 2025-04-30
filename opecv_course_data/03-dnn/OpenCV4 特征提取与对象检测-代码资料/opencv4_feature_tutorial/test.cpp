#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/images/building.png");
	imshow("input", src);
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	vector<Point> corners;
	goodFeaturesToTrack(gray, corners, 400, 0.015, 10);
	for (size_t t = 0; t < corners.size(); t++) {
		circle(src, corners[t], 2, Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("½Çµã¼ì²â", src);
	waitKey(0);
	return 0;
}