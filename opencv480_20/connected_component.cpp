#include <iostream>
#include <opencv2/opencv.hpp>
#include "util.h"
#include "connected_component.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using cv::Mat;
using cv::imread;
using cv::Scalar;
void ConnectedComponent::connected_component_demo01(void)
{
	const string path = "J:/vs2017ws/data/rice.png";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	
	//高斯模糊
	cv::Mat gauss_dst;
	GaussianBlur(image, gauss_dst, cv::Size(3, 3),0);
	const string gauss_window_name1 = "gauss图窗口";
	//imshow(gauss_window_name1, gauss_dst);
	//转灰度图
	Mat gray;
	cv::cvtColor(gauss_dst, gray, cv::COLOR_BGR2GRAY);
	//二值化 如果光照强度一致 首选全局阈值
	/*Mat binary_adtive2;
	cv::adaptiveThreshold(gray, binary_adtive2, 255,
		cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 25, 7);
	const string binary_adtive_window_name1 = "adtive二值图窗口";
	imshow(binary_adtive_window_name1, binary_adtive2);*/
	Mat binary;
	double thres2 = cv::threshold(gray, binary,
		0, 255, cv::THRESH_OTSU | cv::THRESH_BINARY);

	const string binary_threshold_window_name1 = "threshold二值图窗口";
	imshow(binary_threshold_window_name1, binary);
	//连通组件扫描
	Mat labels = Mat::zeros(binary.size(),CV_32S);
	//cv::connectedComponentsWithStats(binary,labels,8, cv::CCL_DEFAULT);
	/*这个有两个函数connectedComponents(InputArray image, OutputArray labels,
	int connectivity, int ltype, int ccltype)
	connectedComponents(InputArray image, OutputArray labels,
	int connectivity = 8, int ltype = CV_32S)*/
	//cv::CCL_DEFAULT
	int num_labels=cv::connectedComponents(binary, labels, 8, CV_32S,cv::CCL_DEFAULT);
	cout << "total labels is " << num_labels - 1 << endl;//25
	//cv::Vec3b 表示一个向量，数量有三个 类型是uchar
	
	//背景
	std::vector<cv::Vec3b> color_table(num_labels);
	cv::RNG rng(12345);
	color_table[0] = cv::Vec3b(0,0,0);
	for (int i=1;i<num_labels;i++)
	{
		color_table[i]= cv::Vec3b(rng.uniform(0,256), rng.uniform(0, 256), rng.uniform(0, 256));
	}
	Mat result = Mat::zeros(image.size(),image.type());
	int width = result.cols;
	int height = result.rows;
	for (int row=0;row<height;row++)
	{
		for (int column = 0; column < width; column++)
		{
			int label = labels.at<int>(row, column);
			cv::Vec3b color = color_table[label];
			result.at<cv::Vec3b>(row, column)= color;
		}
	}
	cv::putText(result,cv::format("num is %d", num_labels - 1),
		cv::Point(0,15),1,cv::FONT_HERSHEY_PLAIN,cv::Scalar(0,255,0),1);
	imshow("CCL", result);
}
