#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/zhigang/opencv4_images/lene.jpg");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("gray", gray);
	Scalar m = mean(gray);
	printf("means : %.2f\n", m[0]);
	threshold(gray, binary, m[0], 255, THRESH_BINARY);
	imshow("binary", binary);

	double t1 = threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("otsu binary", binary);

	double t2 = threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_TRIANGLE);
	imshow("triangle binary", binary);

	printf("otsu theshold : %.2f, triangle threshold : %.2f \n", t1, t2);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
