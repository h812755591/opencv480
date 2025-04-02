#pragma once


#include <opencv2/opencv.hpp>


class QuickDemo
{
public:
	void color_space_demo1(cv::Mat &img);
	void mat_demo1(cv::Mat & img);
	void pixel_demo1(cv::Mat & img);
	void arithmetic_demo1(cv::Mat & img);
	void tracking_bar_demo(cv::Mat &image);
//public:
//	static void on_lightness(int b, void* userdata);
//	static void on_contrast(int b, void* userdata);
//	static std::string UTF8ToLocal(const std::string& utf8Str);
};



