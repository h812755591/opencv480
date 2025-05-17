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

