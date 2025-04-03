#include "quickopencv.h"
#include <string>
#include <windows.h>  // 必须包含此头文件

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
	std::string  path= "J:/vs2017ws/data/flower1.png";
	cv::Mat  img= read_img(path);
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

cv::Mat & QuickDemo::read_img(const std::string path)
{
	// TODO: 在此处插入 return 语句
	cv::Mat img = cv::imread(path);
	if (img.empty())
	{
		throw std::runtime_error("Resource not found: " + path);
	}
	return img;

}
