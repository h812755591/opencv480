#include <vector>
#include "corner_dect.h"
#include "util.h"
using std::string;
using cv::Mat;
using std::vector;
using cv::Point2f;
using cv::Scalar;
void yolov5pro::CornerDect::demo01_tomasi(void)
{
	//步骤1 读取彩色图BGR
	const string path = "J:/vs2017ws/data/left12.jpg";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//步骤2 获取灰度图
	Mat gray;
	cv::cvtColor(image,gray,cv::COLOR_BGR2GRAY);//dscn由code自动推导
	string gray_win_name = "gray窗口";
	cv::namedWindow(gray_win_name, windows_style);
	imshow(gray_win_name, gray);
	//步骤3 获取角点
	vector<Point2f> corners;
	int max_corners = 200;
	double mindistance = 10;
	cv::goodFeaturesToTrack(gray,corners, max_corners,0.6, mindistance
		);//输入必须是单通道 可以是8u 也可以是32F
	//可选的亚像素优化
	cv::TermCriteria criteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.01);
	cv::cornerSubPix(gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	unsigned int   nums=(unsigned int)corners.size();
	for (unsigned int i=0;i< nums;i++)
	{
		Point2f corner=corners[i];
		//这个函数输入是Point 需要转
		//cv::Point corner_int = static_cast<cv::Point>(corners[i]);//截断
		cv::Point corner_int(cvRound(corner.x), cvRound(corner.y));
		cv::circle(image, corner, 3, Scalar(0, 0, 255), 1);
	}
	string corner_win_name = "corner窗口";
	cv::namedWindow(corner_win_name, windows_style);
	imshow(corner_win_name, image);
	cv::waitKey(0);
	cv::destroyAllWindows();


}
