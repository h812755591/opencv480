#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat model = imread("D:/projects/opencv_tutorial/data/images/sample.png");
	Mat src = imread("D:/projects/opencv_tutorial/data/images/target.png");
	if (src.empty() || model.empty()) {
		printf("could not find image files");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	imshow("sample", model);

	Mat model_hsv, image_hsv;
	cvtColor(model, model_hsv, COLOR_BGR2HSV);
	cvtColor(src, image_hsv, COLOR_BGR2HSV);

	int h_bins = 48, s_bins = 48;
	int histSize[] = { h_bins, s_bins };
	int channels[] = { 0, 1 };
	Mat roiHist;
	float h_range[] = { 0, 180 };
	float s_range[] = { 0, 255 };
	const float* ranges[] = { h_range, s_range };
	calcHist(&model_hsv, 1, channels, Mat(), roiHist, 2, histSize, ranges, true, false);
	normalize(roiHist, roiHist, 0, 255, NORM_MINMAX, -1, Mat());
	MatND backproj;
	calcBackProject(&image_hsv, 1, channels, roiHist, backproj, ranges, 1.0);
	imshow("back projection demo", backproj);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
