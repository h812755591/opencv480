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
	std::string win_name = "窗口";
	cv::namedWindow(win_name);
	int init_value = 50;
	int max_value = 100;
	int contrast_value = 100;
	std::string trackbar_name = "调整";
	cv::createTrackbar(trackbar_name, win_name, &init_value, max_value, nullptr);
	cv::imshow(win_name,image);
}



