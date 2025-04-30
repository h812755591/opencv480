#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/images/cross.png");
	imshow("input", src);

	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);

	threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	imshow("binary", binary);

	// Mat k = getStructuringElement(MORPH_ELLIPSE, Size(15, 15), Point(-1, -1));
	// Mat hothat;
	// morphologyEx(binary, hothat, MORPH_TOPHAT, k);
	// imshow("top hat demo", hothat);

	// morphologyEx(binary, hothat, MORPH_BLACKHAT, k);
	// imshow("black hat demo", hothat);

	Mat hitmiss;
	Mat k = getStructuringElement(MORPH_CROSS, Size(15, 15), Point(-1, -1));
	morphologyEx(binary, hitmiss, MORPH_HITMISS, k);
	imshow("hit and miss", hitmiss);


	waitKey(0);
	destroyAllWindows();
	return 0;
}