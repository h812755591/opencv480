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