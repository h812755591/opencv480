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
namespace {  // 匿名命名空间
	void contour_info(Mat &image, 
		std::vector<std::vector<cv::Point>> &contours,bool show_binary=false,int type= cv::THRESH_BINARY | cv::THRESH_OTSU)
	{  
		// 二值化
		cv::Mat gauss_dst;
		GaussianBlur(image, gauss_dst, cv::Size(3, 3), 0);//如果不指定标准差 根据滤波核进行计算
		
		Mat gray, binary;
		cvtColor(gauss_dst, gray, cv::COLOR_BGR2GRAY);
		threshold(gray, binary, 0, 255, type);
		if (show_binary)
		{
			const string binary_win_name = "binary1窗口";
			int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
			cv::namedWindow(binary_win_name, windows_style);
			imshow(binary_win_name, binary);
		}
		// 轮廓发现
		std::vector<cv::Vec4i> hirearchy;
		findContours(binary, contours, hirearchy, 
			cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, cv::Point());
	};
	void draw_contour(const std::vector<std::vector<cv::Point>> &contours, Mat &image)
	{
		for (size_t i = 0; i < contours.size(); i++)
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
}
void ContourMy::contour_demo03_match(void)
{
	//读取图像
	const string src_path = "J:/vs2017ws/data/abc.png";
	const string math_path = "J:/vs2017ws/data/a.png";
	Mat image_src = util::read_img(src_path);
	Mat image_match = util::read_img(math_path);
	const string src_win_name = "src窗口";
	const string match_win_name = "match窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(src_win_name, windows_style);
	cv::namedWindow(match_win_name, windows_style);
	imshow(src_win_name, image_src);
	imshow(match_win_name, image_match);
	//
	std::vector<std::vector<cv::Point>> contours_src;
	cout << contours_src.size() << endl;
	std::vector<std::vector<cv::Point>> contours_match;
	contour_info(image_src, contours_src);
	contour_info(image_match, contours_match);
	cout << contours_src[0].size() << endl;
	cout << contours_match[0].size() << endl;
	//draw_contour(contours_src, image_src);
	cv::Moments mm2 = cv::moments(contours_match[0]);
	Mat hu2;
	cv::HuMoments(mm2, hu2);
	for (size_t t = 0; t < contours_src.size(); t++) {
		cv::Moments mm = cv::moments(contours_src[t]);
		double cx = mm.m10 / mm.m00;//质心x坐标
		double cy = mm.m01 / mm.m00;//质心y坐标
		int x = cvRound(cx);
		int y = cvRound(cy);
		circle(image_src, cv::Point(x, y), 3, Scalar(255, 0, 0), 2, 8, 0);
		Mat hu;
		HuMoments(mm, hu);
		double dist = matchShapes(hu, hu2, cv::CONTOURS_MATCH_I1, 0);
		if (dist < 1.0) {
			printf("matched distance value : %.2f\n", dist);
			drawContours(image_src, contours_src, static_cast<int>(t), Scalar(0, 0, 255), 2, 8);
		}
	}
	imshow("match contours demo", image_src);
}
void ContourMy::contour_demo03_match02(void)
{
	//读取图像
	const string src_path = "J:/vs2017ws/data/abc.png";
	const string math_path = "J:/vs2017ws/data/a.png";
	Mat image_src = util::read_img(src_path);
	Mat image_match = util::read_img(math_path);
	const string src_win_name = "src窗口";
	const string match_win_name = "match窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(src_win_name, windows_style);
	cv::namedWindow(match_win_name, windows_style);
	imshow(src_win_name, image_src);
	imshow(match_win_name, image_match);
	//
	std::vector<std::vector<cv::Point>> contours_src;
	cout << contours_src.size() << endl;
	std::vector<std::vector<cv::Point>> contours_match;
	contour_info(image_src, contours_src);
	contour_info(image_match, contours_match);
	cout << contours_src[0].size() << endl;
	cout << contours_match[0].size() << endl;
	//draw_contour(contours_src, image_src);
	/*cv::Moments mm2 = cv::moments(contours_match[0]);
	Mat hu2;
	cv::HuMoments(mm2, hu2);*/
	for (size_t t = 0; t < contours_src.size(); t++) {
		cv::Moments mm = cv::moments(contours_src[t]);
		double cx = mm.m10 / mm.m00;//质心x坐标
		double cy = mm.m01 / mm.m00;//质心y坐标
		int x = cvRound(cx);
		int y = cvRound(cy);
		circle(image_src, cv::Point(x, y), 3, Scalar(255, 0, 0), 2, 8, 0);
		
		double dist = matchShapes(contours_src[t], contours_match[0], cv::CONTOURS_MATCH_I1, 0);
		if (dist < 0.5) {
			printf("matched distance value : %.2f\n", dist);
			drawContours(image_src, contours_src, static_cast<int>(t), Scalar(0, 0, 255), 2, 8);
		}
	}
	imshow("match contours demo", image_src);
}

void ContourMy::contour_demo04_approxi01(void)
{
	const string src_path = "J:/vs2017ws/data/contours.png";
	Mat image_src = util::read_img(src_path);
	const string src_win_name = "src窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(src_win_name, windows_style);
	imshow(src_win_name, image_src);
	//获取轮廓
	std::vector<std::vector<cv::Point>> contours_src;
	contour_info(image_src, contours_src);
	printf("提取轮廓数量：%zu\n", contours_src.size());//提取轮廓数量 4
	
	//多边形逼近
	for (size_t i = 0; i < contours_src.size(); i++)
	{
		std::vector<cv::Point> contour_my = contours_src[i];
		cv::Moments mm = cv::moments(contour_my);
		//double cx = mm.m10 / mm.m00;
		//double cy = mm.m01 / mm.m00;
		int x = cvRound(mm.m10 / mm.m00);
		int y = cvRound(mm.m01 / mm.m00);
		double area = cv::contourArea(contour_my);
		double clen = cv::arcLength(contour_my, true);
		circle(image_src, cv::Point(x, y), 3, Scalar(255, 0, 0), 2, 8, 0);
		std::vector<cv::Point> result;
		double epsilon = clen * 0.02;  // 2%的周长‌
		cout << "epsilon=" << epsilon << endl;
		//cv::approxPolyDP(contour_my, result, 4, true);
		cv::approxPolyDP(contour_my, result, epsilon, true);
		printf("corners : %zu , contour area : %.2f, contour length : %.2f \n", 
			result.size(), area, clen);
		if (result.size() == 6) 
		{
			putText(image_src, "poly", cv::Point(x, y - 10), 
				cv::FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 0, 255), 1, 8);
			
		}
		if (result.size() == 4) 
		{
			putText(image_src, "rectangle", cv::Point(x, y - 10),
				cv::FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 255, 255), 1, 8);
		}
		if (result.size() == 3) 
		{
			putText(image_src, "triangle", cv::Point(x, y - 10),
				cv::FONT_HERSHEY_PLAIN, 1.0, Scalar(255, 0, 255), 1, 8);
		}
		if (result.size() > 10) 
		{//圆的角点很多
			putText(image_src, "circle", cv::Point(x, y - 10),
				cv::FONT_HERSHEY_PLAIN, 1.0, Scalar(255, 255, 0), 1, 8);
		}
		polylines(image_src, result, true, Scalar(0, 255, 0), 2);
	}
	imshow("find contours demo", image_src);
}

void ContourMy::contour_demo04_fit_circle01(void)
{
	const string src_path = "J:/vs2017ws/data/stuff.jpg";
	Mat image_src = util::read_img(src_path);
	const string src_win_name = "src窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(src_win_name, windows_style);
	imshow(src_win_name, image_src);
	//
	cv::Mat gauss_dst;
	GaussianBlur(image_src, gauss_dst, cv::Size(3, 3), 10);
	//获取轮廓
	Mat gray, binary;
	cvtColor(gauss_dst, gray, cv::COLOR_BGR2GRAY);
	/*threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);*/
	cv::adaptiveThreshold(gray, binary, 255,
		cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY_INV, 25, 7);
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::erode(binary, binary, kernel, cv::Point(-1, -1), 1);
	// 轮廓发现
	imshow("binary", binary);
	std::vector<std::vector<cv::Point>> contours_src;
	std::vector<cv::Vec4i> hirearchy;
	findContours(binary, contours_src, hirearchy, cv::RETR_EXTERNAL,
		cv::CHAIN_APPROX_SIMPLE, cv::Point());
	printf("提取轮廓数量：%zu\n", contours_src.size());//提取轮廓数量 0
	// 拟合圆或者椭圆
	for (size_t t = 0; t < contours_src.size(); t++) {
		std::vector<cv::Point> contour_tmp=contours_src[t];
		double area = cv::contourArea(contour_tmp);
		double len = cv::arcLength(contour_tmp, true);
		cout << "area=" << area << " len=" << len << " t=" << t << endl;
		if (area < 2000 || len < 200|| (area / len)<7)
		{
			continue;
		}
		drawContours(image_src, contours_src, t, Scalar(0, 0, 255), 2, 8);
		cv::Point pt = contour_tmp[0];
		cv::putText(image_src, cv::format("num=%d area=%0.0f len=%0.0f", t, area,len),
			pt,
			cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255));
		cv::RotatedRect rrt = cv::fitEllipse(contour_tmp);
		float w = rrt.size.width;
		float h = rrt.size.height;
		cv::Point center = rrt.center;
		cv::circle(image_src, center, 3, Scalar(255, 0, 0), 2, 8, 0);
		ellipse(image_src, rrt, Scalar(0, 255, 0), 2, 8);
	}
	//
	imshow("fit result", image_src);

}
