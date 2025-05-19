#include <string>
#include <iostream>
#include "opencv_head.h"
#include "core_operation.h"
using std::string;
using std::cout;
using std::endl;

namespace {
	string base_path("J:/vs2017ws/data/");

}
void basic_operation::demo01_access_modify(void)
{
	Mat img = Mat::zeros(cv::Size(640, 320), CV_8UC3);
	string win_name = "black";
	int windows_style = cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO;
	namedWindow(win_name, windows_style);
	//  CV_8UC3 每个通道对应的是3个uchar
	cv::Vec3b pixel=img.at<cv::Vec3b>(100, 200);
	cout << pixel <<" " << (unsigned )pixel[0]<<endl;
	img.at<cv::Vec3b>(100, 200) = cv::Vec3b(255, 0, 0);
	// 设置一个整个区域
	// img.setTo(cv::Scalar(0, 255, 0));
	cv::Rect roi=cv::Rect(50, 50, 100, 50);
	cv::Mat roiImage = img(roi);
	roiImage.setTo(cv::Scalar(0, 255, 0));
	imshow(win_name, img);
	cv::waitKey(0);
	cv::destroyAllWindows();

}

void basic_operation::demo02_split_merge(void)
{
	Mat img=imread(base_path+"doc_data/"+"home.jpg",cv::IMREAD_COLOR);
	if (img.empty())
	{
		cout << " load error";
		return;
	}
	std::vector<cv::Mat> channels; // B G R
	
	cv::split(img, channels);
	cv::Mat b = channels[0];  // 蓝色通道
	cv::Mat g = channels[1];  // 绿色通道
	cv::Mat r = channels[2];  // 红色通道
	cv::Mat merged_img;
	cv::merge(channels, merged_img);
	imshow("asasd", merged_img);
	cv::waitKey(0);
	cv::destroyAllWindows();

}

void basic_operation::demo03_boarder(void)
{
	Mat img = imread(base_path + "doc_data/" + "opencv-logo.png");
	if (img.empty())
	{
		cout << " load error";
		return;
	}
	Mat replicate;
	// aaaaaa|abcdefgh|hhhhhhh 复制最后一个像素
	imshow("replicate", img);
	cv::copyMakeBorder(img, replicate, 10, 10, 10, 10, cv::BORDER_REPLICATE);
	imshow("replicate", replicate);
	
	// fedcba | abcdefgh | hgfedcb
	Mat reflect;
	cv::copyMakeBorder(img, reflect, 10, 10, 10, 10, cv::BORDER_REFLECT);
	imshow("reflect", reflect);
	Mat reflect101;
	// gfedcb|abcdefgh|gfedcba
	cv::copyMakeBorder(img, reflect101, 10, 10, 10, 10, cv::BORDER_REFLECT101);
	//  cdefgh|abcdefgh|abcdefg
	Mat wrap;
	cv::copyMakeBorder(img, wrap, 10, 10, 10, 10, cv::BORDER_WRAP);
	Mat constant;
	const Scalar BLUE(255, 0, 0);
	cv::copyMakeBorder(img, constant, 10, 10, 10, 10, cv::BORDER_CONSTANT, BLUE);
	imshow("constant", constant);
	imshow("asasd", img);
	cv::waitKey(0);
	cv::destroyAllWindows();
	// res = cv.warpAffine(img, M, (cols, rows), borderMode=cv.BORDER_ISOLATED)
	// 

}

