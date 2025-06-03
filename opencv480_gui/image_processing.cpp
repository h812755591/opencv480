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
	string doc_path("J:/vs2017ws/data/doc_data/");
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
/*

*/
void image_thresholding::demo01_threshold(void)
{
	
	Mat img = imread(doc_path + "gradient.png", cv::IMREAD_COLOR);
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
	imshow(src_name, img);

	//全局阈值
	Mat img_gray;
	cv::cvtColor(img,img_gray,cv::COLOR_BGR2GRAY);
	//
	Mat m1;
	Mat m2;

	Mat m3;
	Mat m4;
	cv::threshold(img_gray, m1, 127, 255, cv::THRESH_BINARY);
	cv::threshold(img_gray, m2, 127, 255, cv::THRESH_BINARY_INV);
	//​当像素值 > 阈值时​：将像素值截断为阈值（127）
	//当像素值 ≤ 阈值时​：保持原值不变  这个不属于二值化
	//减少图像中高光区域的亮度过曝
	cv::threshold(img_gray, m3, 127, 255, cv::THRESH_TRUNC);
	//如果像素值 src(x,y) ​大于​ 阈值 thresh，则保持原值：dst(x,y) = src(x,y)。
	//如果像素值 src(x,y) ​小于等于​ 阈值 thresh，则将该像素值设为0​：dst(x,y) = 0。
	//也不属于二值化
	cv::threshold(img_gray, m4, 127, 255, cv::THRESH_TOZERO);
	//cv::threshold(img_gray, m2, 127, 255, cv::THRESH_TOZERO_INV);
	
	//分离前景和背景 去掉不必要的信息 如纹理和渐变等等 方便后续操作
	Mat m5;
	//0没有用 只是占位 
	//使用Otsu算法自动计算最佳阈值，并使用标准二值化方法
	//通过分析图像直方图自动确定最佳阈值
	//基于类间方差最大化原理
	//特别适用于双峰直方图图像（前景 / 背景分明）
	//不需要我们手动计算
	double thres2 = cv::threshold(img_gray, m5, 0, 255, 
		cv::THRESH_OTSU | cv::THRESH_BINARY);

	Mat binary_trangle;
	double thres1 = cv::threshold(img_gray, binary_trangle, 0, 255, 
		cv::THRESH_TRIANGLE | cv::THRESH_BINARY);
	/*
	​计算灰度直方图​：
	统计图像中各灰度级的像素数量
	对直方图进行平滑处理(防止噪声影响)
	​三角法计算阈值​
	最佳场景​：目标占比很小的单峰直方图图像
	​计算特点​：几何算法比统计分析更简单高效
	​典型应用​：文档、医疗、显微图像等前背景比例悬殊的情况
	对于文档类图像处理（白纸黑字），三角法通常比OTSU更优。在扫描照片或打印文本时，它能更好地区分纸张底色和文字墨迹。实际应用中建议：

	先尝试三角法
	效果不佳时切换到OTSU
	复杂图像使用分块处理
	*/



	cv::waitKey(0);
	cv::destroyAllWindows();
}

void image_thresholding::demo02_adaptive_threshold(void)
{
	Mat img = imread(doc_path + "sudoku.png", cv::IMREAD_COLOR);
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
	imshow(src_name, img);
	//
	Mat img_gray;
	cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
	Mat binary_adtive1;
	/*
	计算步骤
	​确定邻域范围​：
	对于图像中的每个像素点 (x, y)，以其为中心确定一个大小为 blockSize × blockSize 的邻域。
	注意：blockSize 必须是奇数（如 3, 5, 7 等），以确保中心点存在。
	​计算邻域均值​：
	计算该邻域内所有像素的灰度值的算术平均值（mean）。
	计算公式：
	mean= 
	blockSize×blockSize
	1
	​
  
	i∈邻域
	∑
	​
	 I(i)
	其中 I(i) 表示邻域内第 i 个像素的灰度值。
	​计算阈值​：
	将计算得到的均值减去常数 C（即参数中的 C 值）得到该像素的阈值 T(x, y)：
	T(x,y)=mean−C
	​应用阈值​：
	根据阈值类型（THRESH_BINARY 或 THRESH_BINARY_INV）进行二值化：
	*/
	cv::adaptiveThreshold(img_gray, binary_adtive1, 255,
		cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 25, 7);
	//
	Mat binary_adtive2;
	//只是进行了加权求和
	//w(i, j) = exp(-((i-x)^2 + (j-y)^2) / (2 * sigma^2)) 
	//sigma = 0.3 * ((blockSize-1)*0.5 - 1) + 0.8

	cv::adaptiveThreshold(img_gray, binary_adtive2, 255,
		cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 25, 7);
	cv::waitKey(0);
	cv::destroyAllWindows();
}
