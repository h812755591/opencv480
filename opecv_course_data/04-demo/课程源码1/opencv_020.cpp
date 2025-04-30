#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/zhigang/opencv4_images/t3.jpg");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("input", gray);
	threshold(gray, binary, 200, 255, THRESH_BINARY);
	imshow("threshold binary", binary);

	threshold(gray, binary, 127, 255, THRESH_BINARY_INV);
	imshow("threshold binary invert", binary);

	threshold(gray, binary, 127, 255, THRESH_TRUNC);
	imshow("threshold TRUNC", binary);

	threshold(gray, binary, 127, 255, THRESH_TOZERO);
	imshow("threshold to zero", binary);

	threshold(gray, binary, 127, 255, THRESH_TOZERO_INV);
	imshow("threshold to zero invert", binary);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
