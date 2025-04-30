#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	// Mat image = imread("D:/images/butterfly.jpg");
	Mat image = imread("D:/images/mytest.jpg");
	Mat gray, binary;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	findContours(binary, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	int index = -1;
	double max = -1;
	for (int i = 0; i < contours.size(); i++) {
		double area = contourArea(contours[i]);
		if (area > max) {
			max = area;
			index = i;
		}
	}
	drawContours(image, contours, index, Scalar(0, 255, 0), 2, 8);

	Mat approxCurves;
	vector<Point2f> srcPts;
	approxPolyDP(contours[index], approxCurves, 100, true);
	for (int i = 0; i < contours.size(); i++) {
		Vec2i  pt = approxCurves.at<Vec2i>(i, 0);
		std::cout << pt << std::endl;
		srcPts.push_back(Point2f(pt[0], pt[1]));
		circle(image, Point(pt[0], pt[1]), 12, Scalar(0, 0, 255), 2, 8, 0);
	}
	vector<Point2f> dstPts;
	dstPts.push_back(Point2f(0, 0));
	dstPts.push_back(Point2f(0, 800));
	dstPts.push_back(Point2f(600, 800));	
	dstPts.push_back(Point2f(600, 0));
	imshow("轮廓", image);
	imwrite("D:/result_cc.png", image);

	Mat h = findHomography(srcPts, dstPts, RANSAC);
	Mat dst;
	warpPerspective(image, dst, h, Size(600, 800));
	imwrite("D:/dst.png", dst);
	waitKey(0);
	return 0;
}