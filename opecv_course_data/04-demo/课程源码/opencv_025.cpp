#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
RNG rng(12345);
void ccl_stats_demo(Mat &image);
int main(int argc, char** argv) {
	Mat src = imread("D:/images/zhifang_ball.png");
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
	threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

	// 轮廓发现
	imshow("binary", binary);
	vector<vector<Point>> contours;
	vector<Vec4i> hirearchy;
	findContours(binary, contours, hirearchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
	for (size_t t = 0; t < contours.size(); t++) {
		double area = contourArea(contours[t]);
		double len = arcLength(contours[t], true);
		if (area < 100 || len < 10) continue;
		Rect box = boundingRect(contours[t]);
		// rectangle(src, box, Scalar(0, 0, 255), 2, 8, 0);
		RotatedRect rrt = minAreaRect(contours[t]);
		// ellipse(src, rrt, Scalar(255, 0, 0), 2, 8);
		Point2f pts[4];
		rrt.points(pts);
		for (int i = 0; i < 4; i++) {
			line(src, pts[i], pts[(i + 1) % 4], Scalar(0, 255, 0), 2, 8);
		}
		printf("area : %.2f, contour lenght : %.2f, angle:%.2f\n", area, len, rrt.angle);
		// drawContours(src, contours, t, Scalar(0, 0, 255), -1, 8);
	}
	imshow("find contours demo", src);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
