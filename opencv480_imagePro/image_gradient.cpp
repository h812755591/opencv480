#include <opencv2/opencv.hpp>
#include <iostream>
#include "image_gradient.h"

using std::cout;
using std::endl;
using std::string;
//
using cv::Mat;
string base_path("J:/vs2017ws/data/gradient/");
void image_gradient::demo01_sobel(void)
{
	string image_path = base_path+"pie.png";
	Mat image = cv::imread(image_path);
	if (image.empty())
	{
		cout << " image could not be read" << endl;
	}
	//1,gray
	Mat gray;
	cv::cvtColor(image,gray,cv::COLOR_BGR2GRAY);
	//
	Mat dst_x;
	Mat dst_y;
	cv::Sobel(gray, dst_x,CV_16S,1,0,3);
	cv::Sobel(gray, dst_y,CV_16S, 0, 1, 3);

	//2，要展示转化成8u
	Mat abs_dst_x;
	Mat abs_dst_y;
	//
	cv::convertScaleAbs(dst_x, abs_dst_x);
	cv::convertScaleAbs(dst_y, abs_dst_y);
	cv::imshow("sobelx", abs_dst_x);
	cv::imshow("sobely", abs_dst_y);
	//
	Mat gradient;
	//dst=saturate(src1×α+src2×β+γ)
	cv::addWeighted(abs_dst_x,0.5,abs_dst_y,0.5,0, gradient);
	cv::imshow("gradient", gradient);
	//释放资源
	cv::waitKey();
	cv::destroyAllWindows();
}

void image_gradient::demo02_scharr(void)
{
	string image_path = base_path + "pie.png";
	Mat image = cv::imread(image_path);
	if (image.empty())
	{
		cout << " image could not be read" << endl;
	}
	//1,gray
	Mat gray;
	cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	//
	Mat dst_x;
	Mat dst_y; 
	
	cv::Scharr(gray, dst_x, CV_16S, 1, 0, 3);
	cv::Scharr(gray, dst_y, CV_16S, 0, 1, 3);
	
	//2，要展示转化成8u
	Mat abs_dst_x;
	Mat abs_dst_y;
	//
	cv::convertScaleAbs(dst_x, abs_dst_x);
	cv::convertScaleAbs(dst_y, abs_dst_y);
	cv::imshow("sobelx", abs_dst_x);
	cv::imshow("sobely", abs_dst_y);
	//
	Mat gradient;
	//dst=saturate(src1×α+src2×β+γ)
	cv::addWeighted(abs_dst_x, 0.5, abs_dst_y, 0.5, 0, gradient);
	cv::imshow("gradient", gradient);
	//释放资源
	cv::waitKey();
	cv::destroyAllWindows();
}

void image_gradient::demo03_laplacian(void)
{
	string image_path = base_path + "pie.png";
	Mat image = cv::imread(image_path);
	if (image.empty())
	{
		cout << " image could not be read" << endl;
	}
	//1,gray
	Mat gray;
	cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	//
	cv::GaussianBlur(gray, gray, cv::Size(3, 3), 0);
	//
	cv::Mat laplacian, abs_laplacian;
	cv::Laplacian(gray, laplacian, CV_16S, 3);  // ksize=3
	cv::convertScaleAbs(laplacian, abs_laplacian);  // 转为8位无符号

	//
	Mat gradient;
	cv::imshow("gradient", abs_laplacian);
	//释放资源
	cv::waitKey();
	cv::destroyAllWindows();
}

void image_gradient::demo04_canny(void)
{
}
