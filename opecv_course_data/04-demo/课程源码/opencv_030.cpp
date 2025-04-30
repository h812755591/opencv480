#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void erode_dilate_demo();
int main(int argc, char** argv) {
	Mat src = imread("D:/images/fill.png");

	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	imshow("input", binary);

	Mat dst;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 1), Point(-1, -1));
	morphologyEx(binary, dst, MORPH_OPEN, kernel, Point(-1, -1), 1);
	imshow("open-demo", dst);

	waitKey(0);
	destroyAllWindows();
	return 0; 
}

void erode_dilate_demo() {
	Mat src = imread("D:/images/morph.png");
	imshow("input", src);
	/*
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	*/
	Mat dst1, dst2;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	erode(src, dst1, kernel);
	dilate(src, dst2, kernel);

	imshow("erode", dst1);
	imshow("dilate", dst2);

}
