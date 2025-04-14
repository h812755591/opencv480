#include <iostream>
#include <opencv2/opencv.hpp>
#include "util.h"
#include "hough.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using cv::Mat;
using cv::imread;
using cv::Scalar;
using cv::Vec3f;
using cv::Point;
using cv::Vec4i;
void Hough20::Hough::hough_demo01_hough_lines()
{
	//读取图像
	const string path = "J:/vs2017ws/data/two_lines.jpg";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//高斯滤波
	Mat gauss_dst;
	cv::GaussianBlur(image, gauss_dst, cv::Size(3, 3), 0);
	imshow("gauss blur", gauss_dst);
	
	//
	Mat gray;
	cv::cvtColor(gauss_dst,gray,cv::COLOR_BGR2GRAY);
	//
	Mat binary;
	cv::threshold(gray,binary,0,255,
		cv::THRESH_BINARY|cv::THRESH_OTSU);
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::erode(binary, binary, kernel, cv::Point(-1, -1), 1);
	string binary_win_name = "binary窗口";
	cv::namedWindow(binary_win_name, windows_style);
	imshow(binary_win_name, binary);
	//
	vector<Vec3f> lines;
	HoughLines(binary, lines, 1, CV_PI / 180.0, 100, 0, 0);
	Point pt1, pt2;
	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0]; // 距离
		float theta = lines[i][1]; // 角度
		float acc = lines[i][2];// 累加值
		printf("rho: %.2f, theta : %.2f, acc: %.2f \n", rho, theta, acc);
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		int angle = round((theta / CV_PI) * 180);
		printf("angle : %d \n", angle);
		if (rho > 0) { // 右倾
			line(image, pt1, pt2, Scalar(0, 0, 255), 1, 8, 0);
			if (angle == 90) { // 水平线
				line(image, pt1, pt2, Scalar(0, 255, 255), 2, 8, 0);
			}
			if (angle <= 1) {// 垂直线
				line(image, pt1, pt2, Scalar(255, 255, 0), 4, 8, 0);
			}
		}
		else { // 左倾
			line(image, pt1, pt2, Scalar(255, 0, 0), 2, 8, 0);
		}
	}
	string hough_win_name = "hough窗口";
	cv::namedWindow(hough_win_name, windows_style);
	imshow(hough_win_name, image);
}

void Hough20::Hough::hough_demo02_hough_lines(void)
{
	Mat src = imread("J:/vs2017ws/data/morph01.png");
	imshow("src", src);
	Mat binary;
	Canny(src, binary, 80, 160, 3, false);
	imshow("binary", binary);

	vector<Vec4i> lines;
	HoughLinesP(binary, lines, 1, CV_PI / 180, 80, 200, 10);
	Mat result = Mat::zeros(src.size(), src.type());
	for (int i = 0; i < lines.size(); i++) {
		line(result, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 1, 8);
	}
	imshow("hough linesp demo", result);
}
