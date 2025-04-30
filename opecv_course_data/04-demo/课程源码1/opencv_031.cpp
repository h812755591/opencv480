#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/images/building.jpg");

	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("input", gray);

	Mat basic_grad, inter_grad, exter_grad;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(gray, basic_grad, MORPH_GRADIENT, kernel, Point(-1, -1), 1);
	imshow("basic gradient", basic_grad);

	Mat dst1, dst2;
	erode(gray, dst1, kernel);
	dilate(gray, dst2, kernel);

	subtract(gray, dst1, inter_grad);
	subtract(dst2, gray, exter_grad);
	imshow("internal gradient", inter_grad);
	imshow("external gradient", exter_grad);

	threshold(basic_grad, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);


	waitKey(0);
	destroyAllWindows();
	return 0;
}