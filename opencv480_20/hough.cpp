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
using cv::Vec2f;
using cv::Point;
using cv::Vec4i;
void Hough20::Hough::hough_demo01_hough_lines()
{
	//读取图像
	const string path = "J:/vs2017ws/data/tline.jpg";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//高斯滤波
	/*Mat gauss_dst;
	cv::GaussianBlur(image, gauss_dst, cv::Size(3, 3), 0);
	imshow("gauss blur", gauss_dst);*/
	
	//
	Mat gray;
	cv::cvtColor(image,gray,cv::COLOR_BGR2GRAY);
	//
	Mat binary;
	cv::threshold(gray,binary,0,255,
		cv::THRESH_BINARY_INV|cv::THRESH_OTSU);
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::erode(binary, binary, kernel, cv::Point(-1, -1), 1);
	string binary_win_name = "binary窗口";
	cv::namedWindow(binary_win_name, windows_style);
	imshow(binary_win_name, binary);
	//
	vector<Vec3f> lines;
	HoughLines(binary, lines, 1, CV_PI / 180.0, 100, 0.5, 0.5);
	Point pt1, pt2;
	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0]; // 距离
		float theta = lines[i][1]; // 弧度
		float acc = lines[i][2];// 累加值
		printf("rho: %.2f, theta : %.2f, acc: %.2f  size=%zu\n", rho, theta, acc, lines.size());
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho, y0 = b * rho;//(a,b)法线单位向量
		pt1.x = cvRound(x0 + 1000 * (-b)); //(-b,a) 直线一个主方向
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));//(b,-a) 直线另一个主方向
		pt2.y = cvRound(y0 - 1000 * (a));
		int angle = static_cast<int>(round((theta / CV_PI) * 180));
		printf("angle : %d \n", angle);
		if (rho > 0) { // 右倾
			
			if (angle == 90) { // 水平线
				line(image, pt1, pt2, Scalar(0, 255, 255), 2, 8, 0);
			}
			if (angle <= 1) {// 垂直线
				line(image, pt1, pt2, Scalar(255, 255, 0), 4, 8, 0);
			}
			else
			{
				line(image, pt1, pt2, Scalar(0, 0, 255), 1, 8, 0);
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

void Hough20::Hough::hough_demo03_hough_test(void)
{
	//读取图像
	const string path = "J:/vs2017ws/data/han.png";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//
	Mat gray;
	cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	//
	Mat binary;
	cv::threshold(gray, binary, 0, 255,
		cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
	/*cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::erode(binary, binary, kernel, cv::Point(-1, -1), 1);*/
	string binary_win_name = "binary窗口";
	cv::namedWindow(binary_win_name, windows_style);
	imshow(binary_win_name, binary);
	//
	vector<Vec3f> lines;
	HoughLines(binary, lines, 1, CV_PI / 180.0, 100, 0.5, 0.5);
	size_t size = lines.size();
	cout << "size=" << size << endl;
	for (size_t i=0;i< size;i++)
	{
		float rho = lines[i][0]; // 距离
		float theta = lines[i][1]; // 弧度
		float acc = lines[i][2];// 累加值
		cout << "size=" << size <<" rh0="<<rho<< endl;
	}
}

void Hough20::Hough::hough_demo04_hough_circle(void)
{
	Mat src = imread("J:/vs2017ws/data/coins.jpg");
	Mat gray;
	cvtColor(src, gray, cv::COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, cv::Size(9, 9), 2, 2);
	imshow("gray", gray);
	vector<Vec3f> circles;
	double minDist = 20;
	double min_radius = 20;
	double max_radius = 43;
	HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 3, minDist, 100, 100, 
		min_radius, max_radius);
	for (size_t t = 0; t < circles.size(); t++) {
		Point center(circles[t][0], circles[t][1]);
		int radius = round(circles[t][2]);
		//
		circle(src, center, radius, Scalar(0, 0, 255), 2, 8, 0);
		circle(src, center, 3, Scalar(255, 0, 0), 2, 8, 0);
	}
	imshow("hough circle demo", src);
}
