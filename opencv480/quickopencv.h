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
	void bitwise_demo(cv::Mat &image);
	void channels_demo(cv::Mat &image);
	void inrange_demo(void);
	void inrange_demo01(void);
	void pixel_statistic_demo(void);
	void drawing_demo(void);
	void random_drawing(void);
	void polyline_drawing_demo(void);
	void polyline_drawing_hierarchy(void);
	void mouse_drawing_demo(void);
	void mouse_drawing_demo1(cv::Mat &image);
	void norm_demo(void);
public:
	static void on_track(int b, void* userdata);
	//对比度
	static void on_contrast(int b, void* userdata);
	//查看hsv
	static void trackbar_hsv(cv::Mat &image);
	static cv::Mat  read_img(const std::string& path);
	static void on_draw(int event, int x, int y,
		int flags, void *userdata);
	/*static void on_draw1(int event, int x, int y,
		int flags, void *userdata);*/
	//static void on_contrast(int b, void* userdata);
};
void  test(void);


