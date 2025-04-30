#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/zhigang/opencv4_images/yuan_test.png");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("input", gray);

	double t1 = threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("otsu binary", binary);

	adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 25, 10);
	imshow("ada-binary", binary);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
