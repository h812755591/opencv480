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
	void keyboard_demo(cv::Mat &image);
	void color_style_demo(cv::Mat &image);
public:
	static void on_track(int b, void* userdata);
	//对比度
	static void on_contrast(int b, void* userdata);
//	static std::string UTF8ToLocal(const std::string& utf8Str);
};
void  test(void);


