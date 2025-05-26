#include <string>
#include <iostream>
#include <time.h>
#include "opencv_head.h"
#include "image_processing.h"
using std::string;
using std::cout;
using std::endl;
int H_min = 0, S_min = 0, V_min = 0;
int H_max = 179, S_max = 255, V_max = 255;
namespace {
	string base_path("J:/vs2017ws/data/");
	void on_trackbar(int, void*) {
		// 空函数，只为了刷新回调
	}
	void tracer_hsv(Mat &img,Mat &hsv)
	{
		// 创建窗口和滑块
		namedWindow("Trackbars", cv::WINDOW_AUTOSIZE);

		// 创建6个滑块，参数指针传 nullptr，推荐方式
		cv::createTrackbar("H min", "Trackbars", nullptr, 179, on_trackbar);
		cv::createTrackbar("H max", "Trackbars", nullptr, 179, on_trackbar);
		cv::createTrackbar("S min", "Trackbars", nullptr, 255, on_trackbar);
		cv::createTrackbar("S max", "Trackbars", nullptr, 255, on_trackbar);
		cv::createTrackbar("V min", "Trackbars", nullptr, 255, on_trackbar);
		cv::createTrackbar("V max", "Trackbars", nullptr, 255, on_trackbar);

		// 设置默认值
		cv::setTrackbarPos("H min", "Trackbars", 35);
		cv::setTrackbarPos("H max", "Trackbars", 85);
		cv::setTrackbarPos("S min", "Trackbars", 50);
		cv::setTrackbarPos("S max", "Trackbars", 255);
		cv::setTrackbarPos("V min", "Trackbars", 50);
		cv::setTrackbarPos("V max", "Trackbars", 255);

		while (true) {
			// 获取当前滑块值
			int H_min = cv::getTrackbarPos("H min", "Trackbars");
			int H_max = cv::getTrackbarPos("H max", "Trackbars");
			int S_min = cv::getTrackbarPos("S min", "Trackbars");
			int S_max = cv::getTrackbarPos("S max", "Trackbars");
			int V_min = cv::getTrackbarPos("V min", "Trackbars");
			int V_max = cv::getTrackbarPos("V max", "Trackbars");

			// 转换到 HSV 空间
			Mat mask, result;
		

			// 创建掩膜并提取颜色
			inRange(hsv, Scalar(H_min, S_min, V_min), Scalar(H_max, S_max, V_max), mask);
			bitwise_and(img, img, result, mask);

			// 显示窗口
			imshow("Original", img);
			imshow("Mask", mask);
			imshow("Extracted", result);

			// 按 ESC 键退出
			if (cv::waitKey(30) == 27) break;
		}
	}


}



void changing_colorspaces::demo01_inRange(void)
{
	Mat img = imread(base_path + "greenback.png", cv::IMREAD_COLOR);
	if (img.empty())
	{
		cout << " load error";
		return;
	}
	//
	int windows_style = cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO;
	//
	string src_name = "img";
	cv::namedWindow(src_name, windows_style);
	imshow(src_name,img);
	//转hsv
	Mat img_hsv;
	cv::cvtColor(img,img_hsv,cv::COLOR_BGR2HSV);
	cv::namedWindow("img_hsv", windows_style);
	imshow("img_hsv", img_hsv);
	//因为是绿色 我们需要找到绿色的范围
	Mat mask;
	Scalar lower=Scalar(35, 43, 46);
	Scalar upper = Scalar(77, 255, 255);
	cv::inRange(img_hsv, lower,upper,mask);
	//
	string mask_pic_name = "mask_pic_name";
	cv::namedWindow(mask_pic_name, windows_style);
	imshow(mask_pic_name, mask);
	//tracer_hsv(img,img_hsv);
	Mat dst;
	Mat mask_inv  ;
	cv::bitwise_not(mask, mask_inv);
	cv::bitwise_and(img,img,dst, mask_inv);//挖洞

	cv::namedWindow("dst", windows_style);
	imshow("dst", dst);
	//
	cv::waitKey(0);
	cv::destroyAllWindows();
	/*
	1,我们要提取一个区域，比如一块绿色区域，就必须找到mask
	2,通过bitwise_and
	*/
}
