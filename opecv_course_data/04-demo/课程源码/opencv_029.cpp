#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main(int argc, char** argv) {
	Mat src = imread("D:/images/test_coins.png");
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, Size(9, 9), 2, 2);
	imshow("gray", gray);
	vector<Vec3f> circles;
	double minDist = 20;
	double min_radius = 10;
	double max_radius = 50;
	HoughCircles(gray, circles, HOUGH_GRADIENT, 3, minDist, 100, 100, min_radius, max_radius);
	for (size_t t = 0; t < circles.size(); t++) {
		Point center(circles[t][0], circles[t][1]);
		int radius = round(circles[t][2]);
		// »æÖÆÔ²
		circle(src, center, radius, Scalar(0, 0, 255), 2, 8, 0);
		circle(src, center, 3, Scalar(255, 0, 0), 2, 8, 0);
	}
	imshow("hough circle demo", src);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
