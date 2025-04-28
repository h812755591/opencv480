#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "case.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
//
using cv::Mat;
using cv::Size;
using cv::Point;
using cv::Scalar;
string base_path("J:/vs2017ws/data/");

namespace 
{
	bool compareRectY(cv::Rect a, cv::Rect b) {
		return a.y < b.y;  // 左上角 x 坐标小的排在前面
	}
	void sort_rect(vector<cv::Rect> &rects )
	{
		
		std::sort(rects.begin(), rects.end(), compareRectY);
	}
	void dect_defect(Mat &tpl ,vector<cv::Rect> &rects, vector<cv::Rect> &defects)
	{

		
	}
}

void case1::demo01(void)
{
	string image_path = base_path + "ce_01.jpg";
	Mat image=cv::imread(image_path);
	if (image.empty())
	{
		cout << "load error" << endl;
		return;
	}
	string src_win_name = "src_win_name";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;

	cv::namedWindow(src_win_name, windows_style);
	cv::imshow(src_win_name,image);
	// 灰度图
	Mat gray;
	cv::cvtColor(image,gray,cv::COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, cv::Size(3, 3), 0);
	//cv::imshow("gray", gray);
	//二值化
	Mat binary;
	cv::threshold(gray,binary,0,255,
		cv::THRESH_BINARY_INV|cv::THRESH_OTSU);
	//cv::imshow("binary", binary);
	//缺少角 或者有划痕 视为次品 有些轻微划痕 不关心
	//去掉轻微划痕
	Mat binary1;
	Mat kernal=cv::getStructuringElement(cv::MORPH_RECT,Size(3,3));
	cv::morphologyEx(binary, binary1,cv::MORPH_OPEN,kernal);
	cv::imshow("binary1", binary1);
	//
	vector<vector<Point>> contours;
	/*cv::findContours(binary1, contours, cv::RETR_LIST,
		cv::CHAIN_APPROX_SIMPLE, Point(0, 0));*/
	cv::findContours(binary1, contours, cv::RETR_LIST,
		cv::CHAIN_APPROX_NONE, Point(0, 0));
	//for (size_t i = 0; i < contours.size(); i++)
	//{
	//	cv::drawContours(image, contours, static_cast<int>(i),
	//		Scalar(0, 0, 255), 1, 8);
	//	cv::imshow("cc"+i, image);
	//	cv::waitKey(5000);
	//	//cv::Point pt = contours[i][0]; // 取轮廓首个点坐标
	//	//cv::putText(image, std::to_string(i), pt,
	//		//cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255));
	//}
	
	int height = image.rows;
	vector<cv::Rect> rects;
	for (size_t i=0U;i<contours.size();i++)
	{
		//计算输入点集或二值图像中轮廓的最小垂直外接矩形。该矩形的边与图像边界平行
		//如果是二值图像 若输入为图像，需确保是二值图（非零像素为前景）
		vector<Point> c = contours[i];
		cv::Rect  rect = cv::boundingRect(c);
		
		if (rect.height > height / 2)
		{
			continue;
		}
		//
		double area=cv::contourArea(c);
		if (area<150)
		{
			continue;
		}
		rects.push_back(rect);
		//cv::rectangle(image, rect, cv::Scalar(0, 255, 0), 1);  // 绘制绿色矩形，线宽2像素
		cv::drawContours(image, contours, static_cast<int>(i), Scalar(0, 255, 0));
	}
	// 要对外接矩形进行排序
	sort_rect(rects);
	// 现在需要找一个好的 作为模板，这里可以是另一张图的好的模板
	// 为了简单，我就选择一个好的
	//提取ROI 区域作为模板? but why?todowhat
	Mat tpl=binary1(rects[1]);
	//cv::imshow("roi", tpl);
	for(size_t i=0;i<rects.size();i++)
	{
		cv::putText(image, std::to_string(i), rects[i].tl(),
		cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0));
	}
	//


	cout << endl;
	cv::imshow("cc", image);
	//
	cv::waitKey(0);
	cv::destroyAllWindows();




}
