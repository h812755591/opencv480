#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
RNG rng(12345);
void ccl_stats_demo(Mat &image);
int main(int argc, char** argv) {
	Mat src = imread("D:/images/morph3.png");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// 二值化
	GaussianBlur(src, src, Size(3, 3), 0);
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	// 轮廓发现
	imshow("binary", binary);
	vector<vector<Point>> contours;
	vector<Vec4i> hirearchy;
	findContours(binary, contours, hirearchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
	for (size_t t = 0; t < contours.size(); t++) {
		drawContours(src, contours, t, Scalar(0, 0, 255), 2, 8);
	}
	imshow("find contours demo", src);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
