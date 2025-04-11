#include <iostream>
#include <opencv2/opencv.hpp>
#include "util.h"
#include "contour.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using cv::Mat;
using cv::imread;
using cv::Scalar;
using namespace cv::dnn;
void ContourMy::contour_demo01_find(void)
{
	//读取图像
	const string path = "J:/vs2017ws/data/rice.png";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//高斯模糊
	cv::Mat gauss_dst;
	GaussianBlur(image, gauss_dst, cv::Size(3, 3),5);
	const string gauss_window_name1 = "gauss图窗口";
	imshow(gauss_window_name1, gauss_dst);
	//转灰度图
	Mat gray;
	cv::cvtColor(gauss_dst, gray, cv::COLOR_BGR2GRAY);
	//全局二值化
	Mat binary;
	double thres2 = cv::threshold(gray, binary,
		0, 255, cv::THRESH_OTSU | cv::THRESH_BINARY);
	const string binary_threshold_window_name1 = "threshold二值图窗口";
	
	//进行腐蚀 消除由于高斯模糊带来的目标物体面积增加的问题
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::erode(binary, binary, kernel, cv::Point(-1, -1), 1);
	imshow(binary_threshold_window_name1, binary);
	//获取轮廓 Vec<int, 4> 4个int 向量
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hirearchy;
	/*cv::findContours(binary,contours, hirearchy,cv::RETR_TREE,
		cv::CHAIN_APPROX_SIMPLE,cv::Point(0,0));*/
	cv::findContours(binary, contours, hirearchy, cv::RETR_TREE,
		cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	/*cv::findContours(binary, contours, hirearchy, cv::RETR_TREE,
		cv::CHAIN_APPROX_NONE, cv::Point(0, 0));*/
	//size_t 无符号整数类型unsigned long long
	for (size_t  i=0;i< contours.size();i++)
	{
		cv::drawContours(image, contours, static_cast<int>(i), Scalar(0, 0, 255), 1, 8);
		cv::Point pt = contours[i][0]; // 取轮廓首个点坐标
		cv::putText(image, std::to_string(i), pt, 
			cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255));
	}
	//cv::drawContours(image,contours,-1,Scalar(0,0,255),1,8);
	const string contour_window_name1 = "contour图窗口";
	imshow(contour_window_name1, image);
}

void ContourMy::contour_demo02_area(void)
{
	//读取图像
	const string path = "J:/vs2017ws/data/zhifang_ball.png";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//高斯模糊
	cv::Mat gauss_dst;
	GaussianBlur(image, gauss_dst, cv::Size(3, 3),0);
	const string gauss_window_name1 = "gauss图窗口";
	imshow(gauss_window_name1, gauss_dst);
	//转灰度图
	Mat gray;
	cv::cvtColor(gauss_dst, gray, cv::COLOR_BGR2GRAY);
	//全局二值化
	Mat binary;
	double thres2 = cv::threshold(gray, binary,
		0, 255, cv::THRESH_OTSU | cv::THRESH_BINARY_INV);
	/*double thres2 = cv::threshold(gray, binary,
		0, 255, cv::THRESH_TRIANGLE | cv::THRESH_BINARY_INV);*/
	/*cv::adaptiveThreshold(gray, binary, 255,
		cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY_INV, 25, 7);*/
	const string binary_threshold_window_name1 = "threshold二值图窗口";

	//进行腐蚀 消除由于高斯模糊带来的目标物体面积增加的问题
	/*cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::erode(binary, binary, kernel, cv::Point(-1, -1), 1);*/
	imshow(binary_threshold_window_name1, binary);
	//
	//获取轮廓 Vec<int, 4> 4个int 向量
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hirearchy;
	cv::findContours(binary, contours, hirearchy, cv::RETR_EXTERNAL,
		cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	for (size_t i = 0; i < contours.size(); i++)
	{
		std::vector<cv::Point> contour_tmp = contours[i];
		double area=cv::contourArea(contour_tmp);
		double len = cv::arcLength(contour_tmp,true);
		
		if (area<100||len<10)
		{
			continue;
		}
		//cv::drawContours(image, contours, static_cast<int>(i), Scalar(0, 0, 255), 1, 8);
		/*cv::Rect box=cv::boundingRect(contours[i]);
		cv::rectangle(image, box, cv::Scalar(0, 0, 255), 1, 8, 0);*/
		cv::RotatedRect box=cv::minAreaRect(contour_tmp);
		//
		cv::Point2f vertices[4];
		box.points(vertices);

		std::vector<cv::Point> int_vertices;
		for (int i = 0; i < 4; i++) {
			int_vertices.push_back(cv::Point(
				static_cast<int>(vertices[i].x),
				static_cast<int>(vertices[i].y)));
		}
		//最小外接矩形
		cv::polylines(image, int_vertices, true, cv::Scalar(0, 255, 0), 1, 8);
		cout << "area=" << area << " len=" << len <<" angle=" <<box.angle <<endl;
	}
	const string contour_window_name1 = "contour图窗口";
	imshow(contour_window_name1, image);
}
