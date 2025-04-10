#include <iostream>
#include <opencv2/opencv.hpp>
#include "binary.h"
#include "util.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using cv::Mat;
using cv::imread;
void Binary::binary_demo01(void)
{
	const string path = "J:/vs2017ws/data/master.jpg";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//转灰度图
	Mat gray;
	cv::cvtColor(image, gray,cv::COLOR_BGR2GRAY);
	const string gray_window_name = "灰度图窗口";
	imshow(gray_window_name, gray);
	//二值化 127 是阈值
	Mat binary;
	cv::threshold(gray,binary,127,255,cv::THRESH_BINARY);
	const string binary_window_name = "二值图窗口";
	imshow(binary_window_name, binary);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void Binary::binary_demo02_THRESH_BINARY_INV(void)
{
	const string path = "J:/vs2017ws/data/master.jpg";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//转灰度图
	Mat gray;
	cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	//THRESH_BINARY
	//127 因为127是0-255中间的数 假定图像像素值空间是平均的
	Mat binary;
	cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY);
	const string binary_window_name = "二值图窗口";
	imshow(binary_window_name, binary);
	//
	Mat binary1;
	cv::threshold(gray, binary1, 127, 255, cv::THRESH_BINARY_INV);
	const string binary_window_name_inv = "二值图窗口inv";
	imshow(binary_window_name_inv, binary1);
	//
	cv::waitKey(0);
	cv::destroyAllWindows();

}
