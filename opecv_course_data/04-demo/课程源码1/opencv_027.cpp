#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void fit_circle_demo(Mat &image);
int main(int argc, char** argv) {
	Mat src = imread("D:/images/stuff.png");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	fit_circle_demo(src);
	/*
	// 二值化
	GaussianBlur(src, src, Size(3, 3), 0);
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	// 轮廓发现
	imshow("binary", binary);
	vector<vector<Point>> contours;
	vector<Vec4i> hirearchy;
	findContours(binary, contours, hirearchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());

	// 多边形逼近演示程序
	for (size_t t = 0; t < contours.size(); t++) {
		Moments mm = moments(contours[t]);
		double cx = mm.m10 / mm.m00;
		double cy = mm.m01 / mm.m00;
		circle(src, Point(cx, cy), 3, Scalar(255, 0, 0), 2, 8, 0);

		double area = contourArea(contours[t]);
		double clen = arcLength(contours[t], true);

		Mat result;
		approxPolyDP(contours[t], result, 4, true);
		printf("corners : %d , contour area : %.2f, contour length : %.2f \n", result.rows, area, clen);
		if (result.rows == 6) {
			putText(src, "poly", Point(cx, cy - 10), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 0, 255), 1, 8);
		}
		if (result.rows == 4) {
			putText(src, "rectangle", Point(cx, cy - 10), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 255, 255), 1, 8);
		}
		if (result.rows == 3) {
			putText(src, "triangle", Point(cx, cy - 10), FONT_HERSHEY_PLAIN, 1.0, Scalar(255, 0, 255), 1, 8);
		}
		if (result.rows  > 10) {
			putText(src, "circle", Point(cx, cy - 10), FONT_HERSHEY_PLAIN, 1.0, Scalar(255, 255, 0), 1, 8);
		}

	}
	imshow("find contours demo", src);
	*/
	waitKey(0);
	destroyAllWindows();
	return 0;
}

void fit_circle_demo(Mat &image) {
	// 二值化
	Mat gray, binary;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	// 轮廓发现
	imshow("binary", binary);
	vector<vector<Point>> contours;
	vector<Vec4i> hirearchy;
	findContours(binary, contours, hirearchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());

	// 拟合圆或者椭圆
	for (size_t t = 0; t < contours.size(); t++) {
		// drawContours(image, contours, t, Scalar(0, 0, 255), 2, 8);
		RotatedRect rrt = fitEllipse(contours[t]);
		float w = rrt.size.width;
		float h = rrt.size.height;
		Point center = rrt.center;
		circle(image, center, 3, Scalar(255, 0, 0), 2, 8, 0);
		ellipse(image, rrt, Scalar(0, 255, 0), 2, 8);
	}
	imshow("fit result", image);
}
