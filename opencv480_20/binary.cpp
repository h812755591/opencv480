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
using cv::Scalar;
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
	//
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

void Binary::binary_demo02_all(void)
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
	Mat binary;
	cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY);
	const string binary_window_name = "二值图窗口";
	imshow(binary_window_name, binary);
	//
	Mat binary_inv;
	cv::threshold(gray, binary_inv, 127, 255, cv::THRESH_BINARY_INV);
	const string binary_window_name_inv = "inv二值图窗口";
	imshow(binary_window_name_inv, binary_inv);
	//
	Mat binary_trunc;
	cv::threshold(gray, binary_trunc, 127, 255, cv::THRESH_TRUNC);
	const string binary_window_name_trunc = "trunc二值图窗口";
	imshow(binary_window_name_trunc, binary_trunc);
	//THRESH_TOZERO
	//THRESH_TOZERO_INV

}

void Binary::binary_demo03_otsu(void)
{
	const string path = "J:/vs2017ws/data/test.png";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//转灰度图
	Mat gray;
	cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	//THRESH_BINARY
	Mat binary;
	cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY);
	const string binary_window_name = "二值图窗口";
	imshow(binary_window_name, binary);
	//如何寻找一个合适的阈值呢？
	//1，平均阈值
	Mat binary_mean;
	Scalar mean = cv::mean(gray);
	cout << mean[0] << endl;//120.84
	cv::threshold(gray, binary_mean, mean[0], 255, cv::THRESH_BINARY);
	const string binary_window_name_mean = "mean二值图窗口";
	imshow(binary_window_name_mean, binary_mean);
	//2,OTSU 阈值
	Mat binary_otsu;
	//0没有用仅仅是占位
	double thres2 = cv::threshold(gray, binary_otsu, 0, 255, cv::THRESH_OTSU|cv::THRESH_BINARY);
	const string binary_window_name_otsu = "otsu二值图窗口";
	imshow(binary_window_name_otsu, binary_otsu);
	//3，三角阈值
	Mat binary_trangle;
	double thres1=cv::threshold(gray, binary_trangle, 0, 255, cv::THRESH_TRIANGLE | cv::THRESH_BINARY);
	const string binary_window_name_trangle = "trangle二值图窗口";
	imshow(binary_window_name_trangle, binary_trangle);
}

void Binary::binary_demo04_local(void)
{
	//text1.png
	const string path = "J:/vs2017ws/data/text1.png";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//灰度图
	Mat gray;
	cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	//
	Mat binary;
	cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY);
	const string binary_window_name = "二值图窗口";
	imshow(binary_window_name, binary);
	//自适应阈值
	Mat binary_adtive1;
	cv::adaptiveThreshold(gray, binary_adtive1, 255,
		cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 25, 7);
	const string binary_adtive_window_name = "adtive二值图窗口";
	imshow(binary_adtive_window_name, binary_adtive1);
	//自适应阈值2
	Mat binary_adtive2;
	cv::adaptiveThreshold(gray, binary_adtive2, 255,
		cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 25, 7);
	const string binary_adtive_window_name1 = "adtive1二值图窗口";
	imshow(binary_adtive_window_name1, binary_adtive2);
}
