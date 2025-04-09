#include "quickopencv.h"
#include <string>
#include <windows.h>  // 必须包含此头文件
#include <fstream>
#include <chrono>
#include <opencv2/videoio.hpp>
void QuickDemo::color_space_demo1(cv::Mat & img)
{
	cv::Mat gray;
	cv::Mat hsv;
	std::string output_path = "J:/vs2017ws/data/";
	cvtColor(img, hsv, cv::COLOR_BGR2HSV);
	cvtColor(img, gray, cv::COLOR_BGR2GRAY);
	imshow("gray", gray);
	imshow("hsv", hsv);
	imwrite(output_path + "gray.jpg", gray);
	imwrite(output_path + "hsv.jpg", hsv);

}

void QuickDemo::mat_demo1(cv::Mat & img)
{
	cv::Mat dest1;
	cv::Mat dest2;
	dest1 = img.clone();
	img.copyTo(dest2);
	// 创建空白图像
	cv::Mat m3= cv::Mat::zeros(cv::Size(8, 8),CV_8UC1);
	cv::Mat m4 = cv::Mat::zeros(cv::Size(8, 7), CV_8UC3);
	std::cout << m3 << std::endl;
	std::cout << m4.cols << " 宽度" << m4.rows<<" 高度 "<<" channel"<<m4.channels()<< std::endl;
	std::cout << m4 << std::endl;
	//更改第一个通道所有的值
	cv::Mat m5=m4.clone();
	m5 = 127;//这个是三通道的 每三个一组 分别位第一 第二 第三通道
	std::cout << m5 << std::endl;
    //更改属于第1 2 3个通道所有的值
	cv::Mat m6 = m4.clone();
	m6 = cv::Scalar(100,100);//1通道和2通道 m6 = Scalar(100,100,100);123 通道
	std::cout << m6 << std::endl;
}

void QuickDemo::pixel_demo1(cv::Mat & img)
{
	int width = img.cols;
	int heigh = img.rows;
	int channels=img.channels();
	
	for (int i=0;i< heigh;i++)
	{
		uchar * current_row = img.ptr<uchar>(i);
		for (int j= 0; j < width; j++)
		{
			if (channels==1)
			{
				//首先元素类型是8位无符号类型 uchar
				int pixel_value = *current_row;
				//current_row++先执行 但是返回current_row的值和*进行计算
				*current_row++ = 255-pixel_value;
			}
			else if (channels==3)
			{
				cv::Vec3b pixel_values = img.at<cv::Vec3b>(i, j);
				*current_row++ = 255- *current_row;
				*current_row++ = 255- *current_row;
				*current_row++ = 255- *current_row;
				/**current_row = 255 - *current_row;
				current_row++;
				这样写其实更好
				*/
				
			}
		}
	}
}

void QuickDemo::arithmetic_demo1(cv::Mat & img)
{
	cv::namedWindow("src", cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO | cv::WINDOW_GUI_NORMAL);
	cv::namedWindow("dst", cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO | cv::WINDOW_GUI_NORMAL);

	cv::Mat dst;
	cv::Mat m = cv::Mat::zeros(img.size(), img.type());
	m = cv::Scalar(2, 2, 2);
	multiply(img, m, dst);
	imshow("src",img);
	imshow("dst",dst);
	
}

void QuickDemo::tracking_bar_demo(cv::Mat &image)
{
	std::string in_win_name = "输入窗口";
	
	std::string win_name = "窗口";
	cv::namedWindow(win_name);

	int init_value = 0;
	int init_const = 0;
	int max_value = 100;
	std::string trackbar_name_const = "对比度";
	std::string trackbar_name_light = "亮度";
	cv::createTrackbar(trackbar_name_const, win_name, &init_const, max_value,
		QuickDemo::on_contrast, (void *)&image);
	cv::createTrackbar(trackbar_name_light, win_name, &init_value, max_value,
		QuickDemo::on_track, (void *)&image);
	cv::imshow(win_name, image);
	cv::imshow(in_win_name,image);
}

void QuickDemo::keyboard_demo(cv::Mat & image)
{
	cv::Mat dst = cv::Mat::zeros(image.size(), image.type());
	std::string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name);
	cv::imshow(in_win_name, image);
	std::string out_win_name = "输出窗口";
	while (true)
	{
		char key =(char) cv::waitKey(0);//在图像上按键 返回
		if (key == '\033')
		{
			std::cout << "esc 退出" << std::endl;
			break;
		}
		else if (key == '1')
		{
			std::cout << "按键 "<<key << std::endl;
			cv::cvtColor(image, dst, cv::COLOR_BGR2GRAY);
			cv::imshow(out_win_name, dst);
		}
		else if (key == '2')
		{
			
			std::cout << "按键 " << key << std::endl;
			cv::cvtColor(image, dst, cv::COLOR_BGR2HSV);
			cv::imshow(out_win_name, dst);
		}
		else if (key == '3')
		{
			cv::Mat scalar_mat(image.size(), image.type(), cv::Scalar(30, 30, 30));
			std::cout << "按键 " << key << std::endl;
			dst = image + scalar_mat;
			cv::imshow(out_win_name, dst);
		}
	}
}




void QuickDemo::on_track(int b, void * userdata)
{
	cv::Mat  p = *((cv::Mat *)userdata);
	cv::Mat  add_num = cv::Mat(p.size(), p.type(), cv::Scalar(b, b, b));
	cv::Mat dst;
	cv::add(p, add_num, dst);
	std::string win_name = "窗口";
	cv::imshow(win_name, dst);
}



void QuickDemo::on_contrast(int b, void * userdata)
{
	cv::Mat image = *((cv::Mat*)userdata);
	cv::Mat dst = cv::Mat::zeros(image.size(), image.type());
	cv::Mat m = cv::Mat::zeros(image.size(), image.type());
	double contrast = 1.0;
	if (b > 10)
	{
		contrast = b / 10.0;
	}
	std::cout << b << std::endl;
	addWeighted(image, contrast, m, 0.0, 0, dst);
	imshow("窗口", dst);
	std::cout<<"对比度"<<std::endl;
}

void test(void)
{
	
	std::cout << "hello" << std::endl;
	
}
void QuickDemo::color_style_demo(cv::Mat & image)
{
	std::string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name);
	cv::imshow(in_win_name, image);
	cv::Mat dst = cv::Mat::zeros(image.size(),image.type());
	int max_num = 21;//颜色表颜色map个数
	for (int i = 0; i <= max_num; ++i)
	{
		// 将整数值转为枚举类型
		cv::ColormapTypes colormap = static_cast<cv::ColormapTypes>(i);
		//首先转化为灰度图
		cv::cvtColor(image, dst, cv::COLOR_BGR2GRAY);
		cv::Mat colorized_img;
		cv::applyColorMap(dst, colorized_img, colormap);
		//
		std::string out_win_name = "输出窗口";
		cv::namedWindow(out_win_name);
		cv::imshow(out_win_name, colorized_img);
		int key=cv::waitKey(2000);
		if (27== key)
		{
			break;
		}
		else
		{
			//需要说明的是，无论我们点击哪个图像 都会有相应
			std::cout << "key is " <<key<< std::endl;
		}

	}
	


}

void QuickDemo::bitwise_demo(cv::Mat & image)
{
	int width = 256;
	int height = 256;
	cv::Mat m1 = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);
	cv::Mat m2 = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);
	cv::rectangle(m1, cv::Rect(100, 100, 80, 80), cv::Scalar(255, 255, 0), -1, cv::LINE_8, 0);
	cv::rectangle(m2, cv::Rect(150, 150, 80, 80), cv::Scalar(0, 255, 255), -1, cv::LINE_8, 0);
	cv::imshow("m1", m1);
	cv::imshow("m2", m2);
	cv::Mat dst;
	//cv::bitwise_xor(m1, m2, dst);
	cv::bitwise_or(m1,m2,dst);
	cv::imshow("像素位操作", dst);
}

void QuickDemo::channels_demo(cv::Mat & image)
{
	std::string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name);
	cv::imshow(in_win_name, image);
	
	int channel_num=image.channels();
	//也可以自动传std::vector<cv::Mat> mv 让cv::split自动变size和源一样
	std::vector<cv::Mat> mv(channel_num);
	cv::split(image, mv);//BGR
	//imshow("蓝色", mv[0]);
	//imshow("绿色", mv[1]);
	//imshow("红色", mv[2]);//都是灰度图
	std::cout << mv[0].channels() << std::endl;
	//只彰显蓝色通道的值 那么就需要把其它通道的值变为0
	/*mv[0] = 0;
	
	cv::Mat dst;
	cv::merge(mv,dst);
	imshow("去掉蓝色", dst);*/
	cv::Mat dst1(image.size(), CV_8UC3);
	int from_to[] = { 0,2,1,1,2,0 };
	cv::mixChannels(&image,1,&dst1,1, from_to,3);
	cv::imshow("通道混合", dst1);
}

void QuickDemo::inrange_demo()
{
	std::string img_path = "J:/vs2017ws/data/flower.png";
	cv::Mat image = cv::imread(img_path);
	if (image.empty())
	{
		std::cout << "img could not load" << std::endl;
		return;
	}
	std::string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name);
	cv::imshow(in_win_name, image);
	cv::Mat hsv;
	cvtColor(image, hsv, cv::COLOR_BGR2HSV);
	cv::Mat mask;//mask是对应的二值图
	cv::inRange(hsv, cv::Scalar(35, 43, 46), cv::Scalar(77, 255, 255), mask);
	//cv::inRange(hsv, cv::Scalar(75, 100, 50), cv::Scalar(95, 255, 255), mask);
	std::string mask_win = "二值化图像";
	cv::namedWindow(mask_win);
	cv::imshow(mask_win, mask);
	//
	cv::Mat redback = cv::Mat::zeros(image.size(), image.type());
	//redback = cv::Scalar(40, 40, 200); //这种写法不是很合适
	redback.setTo(cv::Scalar(40, 40, 200));

	cv::Mat dst_mask;
	cv::bitwise_not(mask, dst_mask);
	cv::imshow("not mask", dst_mask);
	cv::copyTo(image,redback, dst_mask);
	cv::imshow("roi区域提取", redback);
}
void QuickDemo::inrange_demo01(void)
{
	std::string path = "J:/vs2017ws/data/greenback50.png";
	cv::Mat img = cv::imread(path);
	if (img.empty())
	{
		std::cout << "img could not load" << std::endl;
		return;
	}
	std::string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name);
	cv::imshow(in_win_name, img);
	cv::Mat hsv;
	cvtColor(img, hsv, cv::COLOR_BGR2HSV);
	cv::Mat mask;//mask是对应的二值图 根据图像背景是绿色 查表 
	cv::inRange(hsv, cv::Scalar(35, 43, 46), cv::Scalar(77, 255, 255), mask);
	std::string mask_win = "二值化图像";
	cv::namedWindow(mask_win);
	cv::imshow(mask_win, mask);
	//
	cv::Mat redback = cv::Mat::zeros(img.size(), img.type());
	//redback = cv::Scalar(40, 40, 200); //这种写法不是很合适
	redback.setTo(cv::Scalar(0, 0, 255));//这个是纯红色背景 BGR

	cv::Mat dst_mask;
	cv::bitwise_not(mask, dst_mask);
	cv::imshow("not mask", dst_mask);
	cv::copyTo(img, redback, dst_mask);
	cv::imshow("roi区域提取", redback);
}
void QuickDemo::pixel_statistic_demo(void)
{
	std::string  path= "J:/vs2017ws/data/coins.jpg";
	cv::Mat  img= read_img(path);
	std::string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name);
	cv::imshow(in_win_name, img);
	double minv, maxv;
	//Point_<int>
	cv::Point minLoc, maxLoc;
	std::vector<cv::Mat> mv;
	cv::split(img, mv);//切分成三个Mat 每个Mat 是单通道的
	for (int i = 0; i < mv.size(); i++) {
		//(宽度, 高度)
		minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc, cv::Mat());
		std::cout << "No. channels:" << i << " min value:" << minv << " max value:" << maxv << std::endl;
		std::cout << "No. channels:" << i << " minLoc:" << minLoc << " maxLoc:" << maxLoc << std::endl;
	}
	cv::Mat mean, stddev;
	cv::Mat redback = cv::Mat::zeros(img.size(), img.type());
	redback = cv::Scalar(40, 40, 200);
	////输入矩阵的数据类型自动转换为 CV_64F 进行计算，确保精度
	cv::meanStdDev(redback, mean, stddev);
	imshow("redback", redback);
	//#define CV_64F  6 返回的是double
	std::cout << "means:" << mean << std::endl;
	std::cout << " stddev:" << stddev << std::endl;//这个是三通道的Mat
	std::cout << " stddev:" << stddev.channels() << std::endl;//存储的是有
	std::cout << " stddev:" << stddev.size() << std::endl;//存储的是有
}
void QuickDemo::drawing_demo(void)
{
	std::string  path = "J:/vs2017ws/data/yuan_test.png";
	cv::Mat  img = read_img(path);
	std::string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name);
	cv::imshow(in_win_name, img);
	int x = 130;
	int y = 30;
	int width = 230;
	int height = 260;
	cv::Rect rect(x,y,width,height);
	//原图绘制
	/*rectangle(img, rect, cv::Scalar(0, 0, 255), 1, cv::LINE_8, 0);
	rectangle(img, rect, cv::Scalar(0, 0, 255), 1, cv::LINE_8, 0);
	cv::circle(img,cv::Point(247,157),120,1, cv::LINE_8, 0);
	imshow("绘制演示", img);*/
	//
	/*cv::Mat bg = cv::Mat::zeros(img.size(), img.type());
	rectangle(bg, rect, cv::Scalar(0, 0, 255), -1, cv::LINE_8, 0);
	cv::line(bg, cv::Point(130, 30), cv::Point(360, 290), 
		cv::Scalar(0, 255, 0), 2, cv::LINE_8, 0);
	cv::Mat dst;
	cv::addWeighted(img, 0.7, bg, 0.3, 0, dst);
	imshow("绘制演示", dst);*/
	//
	cv::Mat bg = cv::Mat::zeros(img.size(), img.type());
	rectangle(bg, rect, cv::Scalar(0, 0, 255), -1, cv::LINE_8, 0);
	cv::line(bg, cv::Point(130, 30), cv::Point(360, 290),
		cv::Scalar(0, 255, 0), 2, cv::LINE_8, 0);
	cv::Mat dst;
	cv::RotatedRect rrt;
	rrt.center = cv::Point(200, 200);
	rrt.size = cv::Size(100, 200);
	rrt.angle = 90.0;
	ellipse(bg, rrt, cv::Scalar(0, 255, 255), 2, 8);
	cv::addWeighted(img, 0.7, bg, 0.3, 0, dst);
	imshow("绘制演示", dst);
	/*circle(bg, cv::Point(350, 400), 15, cv::Scalar(255, 0, 0), -1, 8, 0);
	line(bg, cv::Point(100, 100), cv::Point(350, 400), cv::Scalar(0, 255, 0), 4, cv::LINE_AA, 0);
	cv::RotatedRect rrt;
	rrt.center = cv::Point(200, 200);
	rrt.size = cv::Size(100, 200);
	rrt.angle = 90.0;
	ellipse(bg, rrt, cv::Scalar(0, 255, 255), 2, 8);*/
	/*cv::Mat dst;
	addWeighted(img, 0.7, bg, 0.3, 0, dst);
	imshow("绘制演示", bg);*/
	
}
void QuickDemo::random_drawing(void)
{
	cv::Mat canvas = cv::Mat::zeros(cv::Size(512, 512), CV_8UC3);
	int w = canvas.cols;
	int h = canvas.rows;
	//cv::RNG 是 OpenCV 中用于生成伪随机数的工具类，
	//支持均匀分布、高斯分布等多种随机数生成方式，
	//适用于图像处理、数据增强、算法测试等场景‌
	//其实cv::RNG rng() 也是固定的，默认是 2**32-1
	//需要注意的是 这里的随机生成，不是每次都是一样的
	//而是每次生成的和前一次一样
	// 第一次调用 1 2 3 
	//第二次调用还是1 2 3 
	cv::RNG rng(12345);
	while (true) {
		int c = cv::waitKey(500);
		if (c == 27) { // 退出
			break;
		}
		//
		int x1 = rng.uniform(0, w);
		int y1 = rng.uniform(0, h);
		int x2 = rng.uniform(0, w);
		int y2 = rng.uniform(0, h);
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);
		// canvas = Scalar(0, 0, 0);
		line(canvas, cv::Point(x1, y1), cv::Point(x2, y2), 
			cv::Scalar(b, g, r), 1, cv::LINE_AA, 0);
		imshow("随机绘制演示", canvas);
	}


}
void QuickDemo::polyline_drawing_demo(void) 
{
	cv::Mat canvas = cv::Mat::zeros(cv::Size(512, 512),
		CV_8UC3);
	int w = canvas.cols;
	int h = canvas.rows;
	cv::Point p1(100, 100);
	cv::Point p2(300, 150);
	cv::Point p3(300, 350);
	cv::Point p4(250, 450);
	cv::Point p5(50, 450);
	std::vector<cv::Point> pts;
	pts.push_back(p1);
	pts.push_back(p2);
	pts.push_back(p3);
	pts.push_back(p3);
	pts.push_back(p4);
	pts.push_back(p5);
	pts.push_back(p1);

	//说明可以有多个多边形
	cv::Point p6(450, 100);
	cv::Point p7(480, 200);
	cv::Point p8(500, 300);
	std::vector<cv::Point> pts1;
	pts1.push_back(p6);
	pts1.push_back(p7);
	pts1.push_back(p8);
	pts1.push_back(p6); // 闭合多边形
	std::vector<std::vector<cv::Point>> contours;
	contours.push_back(pts);
	contours.push_back(pts1);
	drawContours(canvas, contours, -1, cv::Scalar(0, 0, 255), -1, cv::LINE_8);
	
	imshow("绘制多边形", canvas);
}

void QuickDemo::polyline_drawing_hierarchy(void)
{
	cv::Mat canvas = cv::Mat::zeros(400, 400, CV_8UC3);

	// 定义两个轮廓（外层矩形和内层矩形）
	std::vector<std::vector<cv::Point>> contours;

	// 外层矩形（索引0）
	std::vector<cv::Point> outer_rect = {
		cv::Point(100, 100), cv::Point(300, 100),
		cv::Point(300, 300), cv::Point(100, 300)
	};
	contours.push_back(outer_rect);

	// 内层矩形（索引1）
	std::vector<cv::Point> inner_rect = {
		cv::Point(150, 150), cv::Point(250, 150),
		cv::Point(250, 250), cv::Point(150, 250)
	};
	contours.push_back(inner_rect);

	// 定义层次结构
	std::vector<cv::Vec4i> hierarchy;
	hierarchy.push_back(cv::Vec4i(-1, -1, 1, -1)); // 外层矩形（父）
	hierarchy.push_back(cv::Vec4i(-1, -1, -1, 0)); // 内层矩形（子）

	// 绘制轮廓
	cv::drawContours(
		canvas, contours, -1, cv::Scalar(0, 255, 0),
		2, cv::LINE_8, hierarchy, INT_MAX
	);

	cv::imshow("Manual RETR_TREE", canvas);

}


struct MouseData {
	cv::Mat image;       // 直接存储图像副本，避免悬垂指针
	cv::Mat temp;
	cv::Point sp;
	cv::Point ep;
};

void QuickDemo::mouse_drawing_demo() {
	std::string path = "J:/vs2017ws/data/yuan_test.png";
	cv::Mat image = read_img(path);  
	cv::namedWindow("鼠标绘制", cv::WINDOW_AUTOSIZE);

	// 动态分配 MouseData，确保回调函数生命周期内有效
	MouseData* userdata = new MouseData;
	userdata->image = image.clone();  // 存储副本
	userdata->temp = image.clone();
	userdata->sp = cv::Point(-1, -1);
	userdata->ep = cv::Point(-1, -1);

	// 设置回调函数
	cv::setMouseCallback("鼠标绘制", on_draw, (void*)userdata);

	// 显示初始图像
	cv::imshow("鼠标绘制", userdata->image);

	// 保持窗口打开，等待事件
	while (true) {
		int key = cv::waitKey(10);
		if (key == 27) {  // ESC 键退出
			break;
		}
	}

	// 释放内存（确保在退出事件循环后）
	delete userdata;
}

void QuickDemo::trackbar_hsv(cv::Mat & image)
{
	cv::Mat hsv;
	cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);
	cv::namedWindow("Threshold");
	int h_min = 0, h_max = 20, s_min = 50, v_min = 50;
	cv::createTrackbar("H Min", "Threshold", &h_min, 180);
	cv::createTrackbar("H Max", "Threshold", &h_max, 180);
	cv::createTrackbar("S Min", "Threshold", &s_min, 255);
	cv::createTrackbar("V Min", "Threshold", &v_min, 255);

	while (true) {
		cv::Scalar lower(h_min, s_min, v_min);
		cv::Scalar upper(h_max, 255, 255);
		cv::Mat mask;
		cv::inRange(hsv, lower, upper, mask);
		cv::imshow("Threshold", mask);
		if (cv::waitKey(30) == 27) break;  // 按 ESC 退出
	}
}

cv::Mat  QuickDemo::read_img(const std::string & path)
{
	// TODO: 在此处插入 return 语句
	cv::Mat img = cv::imread(path);
	if (img.empty())
	{
		throw std::runtime_error("Resource not found: " + path);
		throw cv::Exception(cv::Error::StsError, "Failed to load image",
			__func__, __FILE__, __LINE__);
	}
	return img;

}

void QuickDemo::on_draw(int event, int x, int y, int flags, void* userdata) {
	MouseData* data = (MouseData*)userdata;
	cv::Mat& image = data->image;  // 直接操作存储的副本
	cv::Mat& temp = data->temp;
	cv::Point& sp = data->sp;
	cv::Point& ep = data->ep;

	if (event == cv::EVENT_LBUTTONDOWN) {
		sp.x = x;
		sp.y = y;
		std::cout << "start point:" << sp << std::endl;
	}
	else if (event == cv::EVENT_LBUTTONUP) 
	{
		ep.x = x;
		ep.y = y;
		int dx = ep.x - sp.x;
		int dy = ep.y - sp.y;
		if (dx > 0 && dy > 0) {
			cv::Rect box(sp.x, sp.y, dx, dy);
			temp.copyTo(image);
			imshow("ROI区域", image(box));
			rectangle(image, box, cv::Scalar(0, 0, 255), 2, 8, 0);
			imshow("鼠标绘制", image);
			// ready for next drawing
			sp.x = -1;
			sp.y = -1;
		}
	}
	else if (event == cv::EVENT_MOUSEMOVE) 
	{
		if (sp.x > 0 && sp.y > 0) {
			ep.x = x;
			ep.y = y;
			int dx = ep.x - sp.x;
			int dy = ep.y - sp.y;
			if (dx > 0 && dy > 0) {
				cv::Rect box(sp.x, sp.y, dx, dy);
				temp.copyTo(image);
				rectangle(image, box, cv::Scalar(0, 0, 255), 2, 8, 0);
				imshow("鼠标绘制", image);
			}
		}
	}
	else if (event == cv::EVENT_RBUTTONDOWN)
	{
		if (sp.x > 0 || sp.y > 0|| ep.x>0||ep.y>0) {
			ep.x = -1;
			ep.y = -1;
			sp.x = -1;
			sp.y = -1;
			temp.copyTo(image);
			imshow("鼠标绘制", image);
		}
	}
}
cv::Point sp(-1, -1);
cv::Point ep(-1, -1);
cv::Mat temp;
static void on_draw1(int event, int x, int y, int flags, void *userdata) {
	cv::Mat image = *((cv::Mat*)userdata);
	if (event == cv::EVENT_LBUTTONDOWN) {
		sp.x = x;
		sp.y = y;
		std::cout << "start point:" << sp << std::endl;
	}
	else if (event == cv::EVENT_LBUTTONUP) {
		ep.x = x;
		ep.y = y;
		int dx = ep.x - sp.x;
		int dy = ep.y - sp.y;
		if (dx > 0 && dy > 0) {
			cv::Rect box(sp.x, sp.y, dx, dy);
			temp.copyTo(image);//这个代码的 目的是回复到原始图像
			imshow("ROI区域", image(box));
			rectangle(image, box, cv::Scalar(0, 0, 255), 2, 8, 0);
			imshow("鼠标绘制", image);
			// ready for next drawing
			sp.x = -1;
			sp.y = -1;
		}
	}
	else if (event == cv::EVENT_MOUSEMOVE) {
		if (sp.x > 0 && sp.y > 0) {
			ep.x = x;
			ep.y = y;
			int dx = ep.x - sp.x;
			int dy = ep.y - sp.y;
			if (dx > 0 && dy > 0) {
				cv::Rect box(sp.x, sp.y, dx, dy);
				temp.copyTo(image);
				rectangle(image, box, cv::Scalar(0, 0, 255), 2, 8, 0);
				imshow("鼠标绘制", image);
			}
		}
	}
}

void QuickDemo::mouse_drawing_demo1(cv::Mat &image) {
	//std::string path = "J:/vs2017ws/data/yuan_test.png";
	//cv::Mat image = read_img(path);
	cv::namedWindow("鼠标绘制", cv::WINDOW_AUTOSIZE);
	cv::setMouseCallback("鼠标绘制", on_draw1, (void*)(&image));
	imshow("鼠标绘制", image);
	temp = image.clone();
}

void QuickDemo::norm_demo()
{
	
	std::string path = "J:/vs2017ws/data/yuan_test.png";
	
	cv::Mat image = read_img(path);
	cv::imshow("输入图像", image);
	cv::Mat dst;
	std::cout << image.type() << std::endl;//16
	image.convertTo(dst, CV_32FC3);
	cv::imshow("转换图像", dst);
	std::cout << dst.type() << std::endl;//21
	cv::Mat dst1;
	cv::normalize(dst, dst1, 0.0, 1.0, cv::NORM_MINMAX);
	std::cout << dst1.type() << std::endl;//21
	cv::imshow("图像数据归一化1", dst1);
	
}

void QuickDemo::resize_demo(void)
{
	std::string  path = "J:/vs2017ws/data/panchong.jpg";
	cv::Mat  image = read_img(path);
	std::string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name,cv::WINDOW_NORMAL| cv::WINDOW_KEEPRATIO );
	cv::imshow(in_win_name, image);
	//
	cv::Mat zoo_min;
	cv::Mat zoom_out;
	int width = image.cols;
	int height= image.rows;
	cv::resize(image, zoo_min, cv::Size(width / 2, height / 2), 0, 0, cv::INTER_AREA);
	cv::namedWindow("zoomin", cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO);
	cv::imshow("zoomin", zoo_min);
	//C++ 会进行 ‌隐式截断转换‌（直接舍弃小数部分，不四舍五入）
	//cv::resize(image, zoom_out, cv::Size(width*1.5, height*1.5), 0, 0, cv::INTER_LINEAR);
	//cv::imshow("zoom_out", zoom_out);
}

void QuickDemo::flip_demo(void)
{
	std::string  path = "J:/vs2017ws/data/flower.png";
	cv::Mat  image = read_img(path);
	std::string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
	cv::imshow(in_win_name, image);
	cv::Mat dst;
	//上下翻转
	cv::flip(image, dst, 0);
	cv::imshow("上下翻转", dst);
	flip(image, dst, 1); // 左右翻转
	cv::imshow("左右翻转", dst);
	cv::flip(image, dst, -1);
	cv::imshow("双向翻转", dst);
}

void QuickDemo::rotate_demo(void)
{
	std::string  path = "J:/vs2017ws/data/panchong.jpg";
	cv::Mat  image = read_img(path);
	std::string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name, cv::WINDOW_AUTOSIZE | cv::WINDOW_KEEPRATIO);
	cv::imshow(in_win_name, image);
	//
	cv::Mat dst;
	int w = image.cols;
	int h = image.rows;
	cv::Mat res = cv::getRotationMatrix2D(cv::Point2f(w / 2, h / 2), 45, 1.0);
	std::cout << res.size() << std::endl;
	double cos = abs(res.at<double>(0, 0));//cos(θ)
	double sin = abs(res.at<double>(0, 1));//sins(θ)
	int nw = static_cast<int>(cos * w + sin * h);//计算图像旋转后的新高度‌
	int nh = static_cast<int>(sin * w + cos * h);//计算图像旋转后的新宽度‌
	res.at<double>(0, 2) += (nw / 2 - w / 2);//使原图与新图坐标点对齐
	res.at<double>(1, 2) += (nh / 2 - h / 2);//
	//cv::warpAffine(image, dst, res, cv::Size(nw, nh), cv::INTER_LINEAR, 0, cv::Scalar(255, 255, 0));
	cv::warpAffine(image, dst, res, cv::Size(0.4*nw, 0.4*nh), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(255, 0, 0));
	cv::namedWindow("旋转演示", cv::WINDOW_AUTOSIZE | cv::WINDOW_KEEPRATIO);
	cv::imshow("旋转演示", dst);
}
static void fps_count(cv::VideoCapture & cap)
{
	int frame_count = 0;
	auto start_time = std::chrono::steady_clock::now(); // 记录起始时间
	while (true) {
		cv::Mat frame;
		cap >> frame; // 读取一帧
		if (frame.empty()) break;

		frame_count++; // 累计帧数

		// 计算经过的时间（秒）
		auto current_time = std::chrono::steady_clock::now();
		double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
			current_time - start_time).count() / 1000.0;

		// 实时计算 FPS（每秒更新一次）
		if (elapsed >= 1.0) {
			double fps = frame_count / elapsed;
			std::cout << "FPS: " << fps << std::endl;
			frame_count = 0; // 重置计数
			start_time = current_time; // 重置时间
		}

		// 显示帧（可选）
		cv::imshow("Video", frame);
		if (cv::waitKey(1) == 'q') break;
	}
}

void QuickDemo::video_demo(void)
{
	//
	cv::VideoCapture cap("J:/vs2017ws/data/example_dsh.mp4");
	std::cout << cv::getBuildInformation() << std::endl;//FFMPEG:   YES (prebuilt binaries)
	if (!cap.isOpened())
	{
		return;
	}
	else
	{
		std::cout << "load is succ" << std::endl;
		std::cout << "backend is " << cap.getBackendName() << std::endl;
	}
	//std::cout << "FFmpeg 后端支持: " << cv::getBackendName(cv::CAP_FFMPEG) << std::endl;  // 预期输出 `FFMPEG`‌:ml-citation{ref="2,7" data="citationList"}

	//
	int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));//640
	int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));//480
	//如果是摄像头 ，返回-1 如果是文件  用于获取视频文件的 ‌总帧数
	int count = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));
	// 方法1：直接获取元数据中的帧率（可能不准确）
	//每秒多少帧 
	double fps = cap.get(cv::CAP_PROP_FPS);
	std::cout << "fps=" <<fps<< std::endl;//fps=23.976
	//
	int fourcc_code = cv::VideoWriter::fourcc('a', 'v', 'c', '1'); 
	//int fourcc_code = static_cast<int>(cap.get(cv::CAP_PROP_FOURCC));//
	char fourcc_str[] = {
		(char)(fourcc_code & 0xFF),
		(char)((fourcc_code >> 8) & 0xFF),
		(char)((fourcc_code >> 16) & 0xFF),
		(char)((fourcc_code >> 24) & 0xFF),
		0
	};
	std::cout << "视频编码格式: " << fourcc_str << std::endl;  // 视频编码格式: FMP4
	std::cout << fourcc_code << std::endl;//输出877677894


	cv::VideoWriter writer("J:/vs2017ws/data/test.mp4", fourcc_code,
		fps, cv::Size(frame_width, frame_height), true);
	cv::Mat frame;
	while (true)
	{
		cap.read(frame);
		if (frame.empty())
		{
			std::cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		int key = cv::waitKey(50);
		if (key != -1) {  // 有按键被按下  //没有按键是-1
			unsigned char c = static_cast<unsigned char>(key);
			//在 C++ 中，当比较两个不同类型的操作数时，编译器会进行 ‌整型提升
			//unsigned char c 会被提升为 int（例如 113 变为 int 类型的 113）
			//无论 'q'是有符号还是无符号，不影响 但是如果超过127 有影响 
			if (c == 'q') {
				std::cerr << "退出" << std::endl;
				break;
			}
		}
		cv::flip(frame, frame, 1);
		cv::imshow("live", frame);
		writer.write(frame);
	}
	//符合“从内到外”的资源释放顺序
	writer.release();
	cap.release();
	cv::destroyWindow("live"); // 再关闭窗口
	
}

void QuickDemo::video_demo01(void)
{
	//cv::VideoCapture cap(0);
	cv::VideoCapture cap("J:/vs2017ws/data/example_dsh.mp4");
	if (!cap.isOpened())
	{
		return;
	}
	else
	{
		std::cout << "load is succ" << std::endl;
		//说明默认用的是cv::CAP_DSHOW  windows  backend is DSHOW
		std::cout << "backend is "<<cap.getBackendName() << std::endl;
	}
	cv::Mat frame;
	while (true)
	{
		cap.read(frame);
		if (frame.empty())
		{
			std::cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		int key = cv::waitKey(50);
		if (key != -1) {  // 有按键被按下  //没有按键是-1
			unsigned char c = static_cast<unsigned char>(key);
			//在 C++ 中，当比较两个不同类型的操作数时，编译器会进行 ‌整型提升
			//unsigned char c 会被提升为 int（例如 113 变为 int 类型的 113）
			//无论 'q'是有符号还是无符号，不影响 但是如果超过127 有影响 
			// TODO: do something....
			if (c == 'q') {
				std::cerr << "退出"<<std::endl;
				break;
			}
		}
		cv::flip(frame, frame, 1);
		cv::imshow("live", frame);
		
	}
	//符合“从内到外”的资源释放顺序
	cap.release();
	cv::destroyWindow("live"); // 再关闭窗口
}

void QuickDemo::histogram_demo(void)
{
	std::string  path = "J:/vs2017ws/data/flower.png";
	cv::Mat  image = read_img(path);
	std::string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
	cv::imshow(in_win_name, image);
	//将通道分离
	std::vector < cv::Mat > bgr_plane;//BGR
	cv::split(image, bgr_plane);
	//
	const int bins[1] = { 256 };
	float hranges[2] = { 0,255 };
	const float* ranges[1] = { hranges };
	cv::Mat b_hist;
	cv::Mat g_hist;
	cv::Mat r_hist;
	// 计算Blue, Green, Red通道的直方图
	cv::calcHist(&bgr_plane[0], 1, 0, cv::Mat(), b_hist, 1, bins, ranges);
	cv::calcHist(&bgr_plane[1], 1, 0, cv::Mat(), g_hist, 1, bins, ranges);
	cv::calcHist(&bgr_plane[2], 1, 0, cv::Mat(), r_hist, 1, bins, ranges);
	//
	// 显示直方图
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);
	cv::Mat histImage = cv::Mat::zeros(hist_h, hist_w, CV_8UC3);
	normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	// 绘制直方图曲线
	for (int i = 1; i < bins[0]; i++) {
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			cv::Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))), cv::Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))), cv::Scalar(0, 0, 255), 2, 8, 0);
	}
	// 显示直方图
	cv::namedWindow("Histogram Demo", cv::WINDOW_AUTOSIZE);
	imshow("Histogram Demo", histImage);
}
void QuickDemo::histogram_demo_han(void)
{
	//读取图片
	std::string  path = "J:/vs2017ws/data/flower.png";
	cv::Mat  image = read_img(path);
	std::string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
	cv::imshow(in_win_name, image);
	//统计B通道直方图
	//1，讲B通道分离出来
	std::vector<cv::Mat> mv;
	cv::split(image, mv);
	//
	const int bins[1] = { 256 };
	float ranges[] = { 0, 256 };// 像素值范围（左闭右开）像素值范围 [0, 256)，包含 0~255
	const float* histRanges[] = { ranges };//划分的bin也是左闭右开() 255-0+1=256/bins=1
	//统计channels 统计哪些通道的
	int channels[] = { 0 };
	cv::Mat b_hist;
	//bins参数表示有多少个bin 
	//histRanges 表示bin表示的数据范围
	//histRanges 和 bins 表示0-255 范围 分成256个bin
	//mv.data()  返回第一个元素的地址
	cv::calcHist(&mv[0], 1, channels, cv::Mat(), b_hist, 1, bins, histRanges);  // B通道（数组索引0）
	//
	cv::Mat g_hist;
	cv::calcHist(&mv[1], 1, channels, cv::Mat(), g_hist, 1, bins, histRanges);
	//
	cv::Mat r_hist;
	cv::calcHist(&mv[2], 1, channels, cv::Mat(), r_hist, 1, bins, histRanges);
	//
	// 显示直方图
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);
	cv::Mat histImage = cv::Mat::zeros(hist_h, hist_w, CV_8UC3);
	// 归一化直方图数据
	normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	//
	for (int i = 1; i < bins[0]; i++) {
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))), cv::Scalar(255, 0, 0), 2, 8, 0);
		/*line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))), cv::Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))), cv::Scalar(0, 0, 255), 2, 8, 0);*/
	}
	// 显示直方图
	cv::namedWindow("Histogram Demo", cv::WINDOW_AUTOSIZE);
	cv::imshow("Histogram Demo", histImage);
}
void QuickDemo::histogram_2d_demo(void)
{
	std::string  path = "J:/vs2017ws/data/flower.png";
	cv::Mat  image = read_img(path);
	std::string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
	cv::imshow(in_win_name, image);
	//
	cv::Mat hsv, hs_hist;
	cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);
	int hbins = 30, sbins = 32;
	int hist_bins[] = { hbins, sbins };
	float h_range[] = { 0, 180 };
	float s_range[] = { 0, 256 };
	const float* hs_ranges[] = { h_range, s_range };
	int hs_channels[] = { 0, 1 };
	calcHist(&hsv, 1, hs_channels, cv::Mat(), hs_hist, 2, hist_bins, hs_ranges, true, false);
	double maxVal = 0;
	minMaxLoc(hs_hist, 0, &maxVal, 0, 0);
	int scale = 10;
	cv::Mat hist2d_image = cv::Mat::zeros(sbins*scale, hbins * scale, CV_8UC3);
	for (int h = 0; h < hbins; h++) {
		for (int s = 0; s < sbins; s++)
		{
			float binVal = hs_hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);
			rectangle(hist2d_image, cv::Point(h*scale, s*scale),
				cv::Point((h + 1)*scale - 1, (s + 1)*scale - 1),
				cv::Scalar::all(intensity),
				-1);
		}
	}
	//applyColorMap(hist2d_image, hist2d_image, cv::COLORMAP_JET);
	imshow("H-S Histogram", hist2d_image);
	imwrite("J:/vs2017ws/data/hist_2d.png", hist2d_image);
}

void QuickDemo::histogram_eq_demo(void)
{
	std::string  path = "J:/vs2017ws/data/flower.png";
	cv::Mat  image = read_img(path);
	std::string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
	cv::imshow(in_win_name, image);
	//
	// 转换为 HSV 颜色空间
	cv::Mat hsv;
	cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);
	//
	// 分离通道：H（色调）、S（饱和度）、V（亮度）
	std::vector<cv::Mat> channels;
	cv::split(hsv, channels);
	//
	// 3. 仅对 V 通道（索引2）做直方图均衡化
	cv::equalizeHist(channels[2], channels[2]);  // 输入和输出均为 V 通道

	cv::merge(channels, hsv);
	cv::Mat result;
	cv::cvtColor(hsv, result, cv::COLOR_HSV2BGR);
	cv::imshow("直方图均衡化演示", result);
}

void QuickDemo::blur_demo(void)
{
	std::string  path = "J:/vs2017ws/data/example.png";
	cv::Mat  image = read_img(path);
	std::string in_win_name = "输入窗口";
	/*cv::namedWindow(in_win_name, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);*/
	cv::imshow(in_win_name, image);
	//
	cv::Mat dst;
	//卷积核越大，模糊效果越大
	//blur(image, dst, cv::Size(15, 15), cv::Point(-1, -1));
	//blur(image, dst, cv::Size(3, 3), cv::Point(-1, -1));
	//水平方向卷积 这种设置表示只在水平方向进行模糊（7像素宽），垂直方向几乎不模糊
	blur(image, dst, cv::Size(7, 1), cv::Point(-1, -1));
	//垂直方向卷积
	//blur(image, dst, cv::Size(1, 7), cv::Point(-1, -1));
	imshow("图像模糊", dst);
}

void QuickDemo::gaussian_blur_demo(void)
{
	std::string  path = "J:/vs2017ws/data/hist_02.jpg";
	cv::Mat  image = read_img(path);
	std::string in_win_name = "输入窗口";
	/*cv::namedWindow(in_win_name, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);*/
	cv::imshow(in_win_name, image);
	//
	cv::Mat dst;
	GaussianBlur(image, dst, cv::Size(0, 0), 2.0);
	imshow("高斯模糊", dst);
}

void QuickDemo::bifilter_demo(void)
{
	std::string  path = "J:/vs2017ws/data/example.png";
	cv::Mat  image = read_img(path);
	std::string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
	cv::namedWindow("高斯模糊", cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
	cv::namedWindow("双边模糊", cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
	cv::imshow(in_win_name, image);
	//
	cv::Mat dst;
	cv::bilateralFilter(image, dst, 0, 100, 10);
	cv::Mat dst1;
	GaussianBlur(image, dst1, cv::Size(0, 0), 2.0);
	imshow("高斯模糊", dst1);
	cv::imshow("双边模糊", dst);

}

void QuickDemo::face_detection_demo(void)
{
	std::string root_dir = "D:/opencv-4.4.0/opencv/sources/samples/dnn/face_detector/";
	cv::dnn::Net net = cv::dnn::readNetFromTensorflow(root_dir + "opencv_face_detector_uint8.pb", root_dir + "opencv_face_detector.pbtxt");
	cv::VideoCapture capture("D:/images/video/example_dsh.mp4");
}






















