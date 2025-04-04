#include <opencv2/opencv.hpp>
#include <iostream>
#include "quickopencv.h"
#include "main.h"
using namespace std;
//using namespace cv;

string img_path = "J:/vs2017ws/data/yuan_test.png";
//string output_path = "J:/vs2017ws/data/";


void test_load_img(string & path= img_path)
{
	cv::Mat img = cv::imread(path);

	if (img.empty())
	{
		cout << "img could not load" << endl;
		return;
	}
	//namedWindow("hsv", WINDOW_AUTOSIZE | WINDOW_FREERATIO | WINDOW_GUI_NORMAL);
	//namedWindow("gray", WINDOW_AUTOSIZE | WINDOW_FREERATIO | WINDOW_GUI_NORMAL);
	//namedWindow("test", WINDOW_AUTOSIZE | WINDOW_FREERATIO | WINDOW_GUI_NORMAL);
	QuickDemo qd;
	//qd.color_space_demo1(img);
	//qd.mat_demo1(img);
	//qd.pixel_demo1(img);
	//qd.arithmetic_demo1(img);
	//qd.tracking_bar_demo(img);
	//qd.keyboard_demo(img);
	//qd.color_style_demo(img);
	//qd.bitwise_demo(img);
	//qd.channels_demo(img);
	//qd.inrange_demo();
	//qd.inrange_demo01();
	//qd.trackbar_hsv(img);
	//qd.pixel_statistic_demo();
	//qd.drawing_demo();
	//qd.random_drawing();
	//qd.polyline_drawing_demo();
	//qd.polyline_drawing_hierarchy();
	//qd.mouse_drawing_demo();
	qd.norm_demo();
	//qd.mouse_drawing_demo1(img);

	cv::waitKey(0);
	cv::destroyAllWindows();
}

int main(int argc,char * argv[])
{
	test_load_img();
	return 0;
}
