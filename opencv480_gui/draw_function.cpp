#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include "draw_function.h"

using std::string;
using std::endl;
using std::cout;
using cv::Mat;
using cv::imread;
using cv::waitKey;
using cv::namedWindow;
namespace {
	string base_path("J:/vs2017ws/data/");

}
void draw_func::demo01_circle(void)
{
	//Mat img = Mat::zeros(320,640,CV_8UC3);//height width
	Mat img = Mat::zeros(cv::Size(640, 320), CV_8UC3);//height width
	cv::line(img,cv::Point(0,0), cv::Point(640, 320),cv::Scalar(255, 0, 0));
	//左上角 右下角 顶点+颜色 矩形
	cv::rectangle(img, cv::Point(384, 0), cv::Point(510, 128), cv::Scalar(0, 255, 0), 2);
	//
	/*cv::Rect rect = cv::Rect(384,0,126,128);
	cv::rectangle(img, rect, cv::Scalar(0, 255, 0), 2);*/
	//cv::Scalar(0, 0, 255) BGR
	cv::circle(img, cv::Point(70, 200),10, cv::Scalar(0, 0, 255),-1);
	//cv.ellipse(img,(256,256),(100,50),0,0,180,255,-1) 椭圆形 
	//cv.polylines(img,[pts],True,(0,255,255)) 画多边形 
	cv::HersheyFonts font = cv::FONT_HERSHEY_SIMPLEX;
	cv::Point p1 = cv::Point(60, 100);
	cv::circle(img, p1, 1, cv::Scalar(0, 0, 255), 1);
	//文本字符串的左下角坐标 
	//bottomLeftOrigin=True 左上角
	cv::putText(img, "opencv", p1, font, 1, cv::Scalar(255, 255, 255), 2, 8, true);
	//cv::Size textSize = cv::getTextSize("opencv", font, 1, 2, nullptr);

	imshow("Display window", img);

	int k = waitKey(0);// 超时返回-1  
	if ((k & 0xFF) == 's')
	{
		exit(1);
	}
	cv::destroyAllWindows();
}
