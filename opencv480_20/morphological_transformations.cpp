#include <iostream>
#include <opencv2/opencv.hpp>
#include "util.h"
#include "morphological_transformations.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using cv::Mat;
using cv::imread;
using cv::Scalar;
using cv::Size;
using cv::Point;
using std::vector;
void MorphologicalOperation::morphological_demo01_erode(void)
{

	//读取图像
	const string path = "J:/vs2017ws/data/morph3.png";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);


	//
	Mat gray, binary;
	cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
	const string binary_threshold_window_name = "threshold二值图窗口";
	imshow(binary_threshold_window_name, binary);
	//创建一个滤波核
	/*
	Mat kernel = getStructuringElement(cv::MORPH_RECT, Size(3, 3),
		Point(-1, -1));*/
	Mat kernel = getStructuringElement(cv::MORPH_ELLIPSE, Size(3, 3),
		Point(-1, -1));
	Mat dst;
	erode(binary, dst, kernel);
	const string erode_window_name1 = "erode二值图窗口";
	imshow(erode_window_name1, dst);
}

void MorphologicalOperation::morphological_demo02_dilate(void)
{
	//读取图像
	const string path = "J:/vs2017ws/data/yuan_test.png";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//创建一个滤波核
	/*
	Mat kernel = getStructuringElement(cv::MORPH_RECT, Size(3, 3),
		Point(-1, -1));*/
	Mat kernel = getStructuringElement(cv::MORPH_ELLIPSE, Size(3, 3),
		Point(-1, -1));
	Mat dst;
	dilate(image, dst, kernel);
	const string erode_window_name1 = "dilate二值图窗口";
	imshow(erode_window_name1, dst);
}

void MorphologicalOperation::morphological_demo03_erode(void)
{
	//读取图像
	const string path = "J:/vs2017ws/data/yuan_test.png";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//创建一个滤波核
	/*
	Mat kernel = getStructuringElement(cv::MORPH_RECT, Size(3, 3),
		Point(-1, -1));*/
	Mat kernel = getStructuringElement(cv::MORPH_ELLIPSE, Size(3, 3),
		Point(-1, -1));
	Mat dst;
	erode(image, dst, kernel);
	const string erode_window_name1 = "erode二值图窗口";
	imshow(erode_window_name1, dst);
}

void MorphologicalOperation::morphological_demo04_dilate(void)
{
	//读取图像
	const string path = "J:/vs2017ws/data/morph3.png";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);


	//
	Mat gray, binary;
	cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
	const string binary_threshold_window_name = "threshold二值图窗口";
	imshow(binary_threshold_window_name, binary);
	//创建一个滤波核
	/*
	Mat kernel = getStructuringElement(cv::MORPH_RECT, Size(3, 3),
		Point(-1, -1));*/
	Mat kernel = getStructuringElement(cv::MORPH_ELLIPSE, Size(3, 3),
		Point(-1, -1));
	Mat dst;
	dilate(binary, dst, kernel);
	const string dilate_window_name1 = "dilate二值图窗口";
	imshow(dilate_window_name1, dst);
}

void MorphologicalOperation::morphological_demo05_open(void)
{
	const string path = "J:/vs2017ws/data/morph.jpg";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//
	Mat gray, binary;
	cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
	const string binary_threshold_window_name = "threshold二值图窗口";
	imshow(binary_threshold_window_name, binary);
	//
	Mat dst;
	Size kernal_size(3, 3);
	Mat kernel = getStructuringElement(cv::MORPH_RECT, 
		kernal_size, Point(-1, -1));
	morphologyEx(binary, dst, cv::MORPH_OPEN, kernel, Point(-1, -1), 5);
	const string open_window_name = "open二值图窗口";
	imshow(open_window_name, dst);
	Mat dst1;
}

void MorphologicalOperation::morphological_demo06_closed(void)
{
	const string path = "J:/vs2017ws/data/morph02.png";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	/*Mat gauss_dist;
	cv::GaussianBlur(image, gauss_dist,Size(3,3),0);*/
	//
	Mat gray, binary;
	cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
	const string binary_threshold_window_name = "threshold二值图窗口";
	imshow(binary_threshold_window_name, binary);
	//
	Mat dst;
	Size kernal_size(3, 3);
	Mat kernel = getStructuringElement(cv::MORPH_ELLIPSE,
		kernal_size, Point(-1, -1));
	morphologyEx(binary, dst, cv::MORPH_OPEN, kernel, Point(-1, -1), 1);
	const string morph_window_name = "open二值图窗口";
	imshow(morph_window_name, dst);
}

void MorphologicalOperation::morphological_demo07_lines(void)
{
	const string path = "J:/vs2017ws/data/morph01.png";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	
	Mat gray, binary;
	cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
	const string binary_threshold_window_name = "threshold二值图窗口";
	imshow(binary_threshold_window_name, binary);
	//
	Mat dst;
	Size kernal_size(15, 1);
	Mat kernel = getStructuringElement(cv::MORPH_RECT,
		kernal_size, Point(-1, -1));
	morphologyEx(binary, dst, cv::MORPH_OPEN, kernel, Point(-1, -1));
	const string morph_window_name = "open二值图窗口";
	imshow(morph_window_name, dst);
}

void MorphologicalOperation::morphological_demo08_gradient(void)
{
	const string path = "J:/vs2017ws/data/home.jpg";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//
	Mat gray, binary;
	cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	string gray_win_name = "gray输入窗口";
	imshow(gray_win_name, gray);
	cv::namedWindow(gray_win_name, windows_style);
	//
	Mat basic_grad, inter_grad, exter_grad;
	Mat kernel = getStructuringElement(cv::MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(gray, basic_grad, cv::MORPH_GRADIENT, kernel, Point(-1, -1), 1);
	imshow("basic gradient", basic_grad);
	//
	threshold(basic_grad, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
	imshow("binary", binary);
}

void MorphologicalOperation::morphological_demo09_tophat(void)
{
	const string path = "J:/vs2017ws/data/morph.jpg";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//
	Mat gray;
	cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	string gray_win_name = "gray输入窗口";
	cv::namedWindow(gray_win_name, windows_style);
	imshow(gray_win_name, gray);
	
	//
	Mat binary;
	threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
	string binary_win_name = "binary输入窗口";
	cv::namedWindow(binary_win_name, windows_style);
	imshow(binary_win_name, binary);
	//
	Mat kernel = getStructuringElement(cv::MORPH_RECT, Size(13, 13), Point(-1, -1));
	Mat tophat_dist;
	morphologyEx(gray, tophat_dist, cv::MORPH_TOPHAT, kernel, Point(-1, -1), 1);
	string morph_win_name = "morph输入窗口";
	imshow(morph_win_name, tophat_dist);
	//
	
}

void MorphologicalOperation::morphological_demo10_hitmiss(void)
{
	const string path = "J:/vs2017ws/data/cross.png";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//
	Mat gray;
	cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	string gray_win_name = "gray输入窗口";
	cv::namedWindow(gray_win_name, windows_style);
	imshow(gray_win_name, gray);

	//
	Mat binary;
	threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
	string binary_win_name = "binary输入窗口";
	cv::namedWindow(binary_win_name, windows_style);
	imshow(binary_win_name, binary);
	//
	Mat hitmiss;
	Mat k = getStructuringElement(cv::MORPH_CROSS, Size(15, 15), Point(-1, -1));
	morphologyEx(binary, hitmiss, cv::MORPH_HITMISS, k);
	string morph_win_name = "morph输入窗口";
	imshow(morph_win_name, hitmiss);
	
}

void MorphologicalOperation::morphological_demo11_case01(void)
{
	const string path = "J:/vs2017ws/data/case6.jpg";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//高斯滤波
	// 二值化
	GaussianBlur(image, image, Size(3, 3), 0);
	Mat gray, binary;
	cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

	// 闭操作
	Mat se = getStructuringElement(cv::MORPH_RECT, Size(15, 15), Point(-1, -1));
	morphologyEx(binary, binary, cv::MORPH_CLOSE, se);
	imshow("binary", binary);

	// 轮廓发现
	int height = binary.rows;
	int width = binary.cols;
	vector<vector<Point>> contours;
	vector<cv::Vec4i> hirearchy;
	findContours(binary, contours, hirearchy, cv::RETR_EXTERNAL, 
		cv::CHAIN_APPROX_SIMPLE, Point());
	double max_area = -1;
	int cindex = -1;
	for (size_t t = 0; t < contours.size(); t++) {
		cv::Rect rect = boundingRect(contours[t]);
		if (rect.height >= height || rect.width >= width) {
			continue;
		}
		double area = contourArea(contours[t]);
		double len = arcLength(contours[t], true);
		if (area > max_area) {
			max_area = area;
			cindex = t;
		}
	}
	drawContours(image, contours, cindex, Scalar(0, 0, 255), 2, 8);
	Mat pts;
	approxPolyDP(contours[cindex], pts, 4, true);
	Mat result = Mat::zeros(image.size(), image.type());
	drawContours(result, contours, cindex, Scalar(0, 0, 255), 2, 8);
	for (int i = 0; i < pts.rows; i++) {
		cv::Vec2i pt = pts.at<cv::Vec2i>(i, 0);
		circle(image, Point(pt[0], pt[1]), 2, Scalar(0, 255, 0), 2, 8, 0);
		circle(result, Point(pt[0], pt[1]), 2, Scalar(0, 255, 0), 2, 8, 0);
	}
	imshow("find max contours", image);
	imshow("result contours analysis", result);
	printf("area : %.2f \n", max_area);
}

void MorphologicalOperation::morphological_demo11_case02(void)
{
	const string path = "J:/vs2017ws/data/case6.jpg";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//
	Mat gray;
	cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	//高斯模糊
	GaussianBlur(gray, gray, Size(9, 9), 0);
	string gray_win_name = "gray窗口";
	cv::namedWindow(gray_win_name, windows_style);
	imshow(gray_win_name, gray);
	
	//结构元素
	Mat remove_noise_kernerl = getStructuringElement(cv::MORPH_RECT, Size(3, 3), 
		Point(-1, -1));
	//腐蚀
	Mat erode_image;
	erode(gray, erode_image, remove_noise_kernerl, Point(-1, -1), 10);
	//膨胀
	dilate(erode_image, gray, remove_noise_kernerl, Point(-1, -1), 10);
	string noise_win_name = "noise窗口";
	cv::namedWindow(noise_win_name, windows_style);
	imshow(noise_win_name, gray);
	
}
