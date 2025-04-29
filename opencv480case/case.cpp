#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "case.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
//
using cv::Mat;
using cv::Size;
using cv::Point;
using cv::Scalar;
string base_path("J:/vs2017ws/data/");
string positive_dir("J:/vs2017ws/data/elec_watch/positive");
string negative_dir("J:/vs2017ws/data/elec_watch/negative");
namespace 
{
	bool compareRectY(cv::Rect a, cv::Rect b) {
		return a.y < b.y;  // 左上角 x 坐标小的排在前面
	}
	void sort_rect(vector<cv::Rect> &rects )
	{
		
		std::sort(rects.begin(), rects.end(), compareRectY);
	}
	void dect_defect(Mat &tpl ,vector<cv::Rect> &rects,Mat &binary1, vector<cv::Rect> &defects)
	{
		int height = tpl.rows;
		int width = tpl.cols;
		size_t size = rects.size();
		for(size_t ihhh=0; ihhh <size; ihhh++)
		{
			Mat roi=binary1(rects[ihhh]);
			
			cv::resize(roi,roi,tpl.size());//因为模板的长宽和模板有一些轻微差距
			Mat mask;
			cv::subtract(tpl,roi,mask);
			Mat kernal = cv::getStructuringElement(cv::MORPH_RECT,
				cv::Size(3,3));
			cv::morphologyEx(mask,mask,cv::MORPH_OPEN,kernal);
			//转化为二值图
			cv::threshold(mask,mask,0,255,cv::THRESH_BINARY);
			//
			int count = cv::countNonZero(mask);
			//轮廓分析
			int mh = mask.rows + 2;
			int mw = mask.cols + 2;
			Mat mask1 = Mat::zeros(Size(mw,mh),mask.type());
			cv::Rect mroi;
			mroi.x = 1;
			mroi.y = 1;
			mroi.height = mask.rows;
			mroi.width = mask.cols;
			mask.copyTo(mask1(mroi));
			//
			vector<vector<Point>> contours11;
			cv::findContours(mask1, contours11, cv::RETR_LIST,
				cv::CHAIN_APPROX_SIMPLE);
			bool find_flag = false;
			for (size_t m=0;m< contours11.size();m++)
			{

				vector<Point> cc= contours11[m];
				cv::Rect rt = cv::boundingRect(cc);
				//长宽比
				double ratio = ((double)rt.width) / ((double)rt.height);
				
				double area1 = cv::contourArea(cc);
				
				/*mask = 0 ratio = 0.8 edget = 44 edgeb = 2
					mask = 0 area1 = 56*/
				if ((ratio > 4.0)&&(rt.y < 5 ||((mask1.rows - (rt.y + rt.height)) < 10)))
				{
					continue;
				}
				
				//再根据面积过滤一下
				
				if (area1>10)
				{
					cout << "mask=" << ihhh << " ratio=" << ratio << " rt.y=" << rt.y << " hh="
						<< mask1.rows - rt.y - rt.height << endl;
					cout << "mask=" << ihhh << " area1=" << area1 << endl;
					find_flag = true;
				}
			}

			if (count > 50&&find_flag)
			{
				cout << "count:: " << count << endl;
				defects.push_back(rects[ihhh]);
			}
			cv::imshow("mask", mask);
			cv::waitKey(0);
			
		}
	}
}

void case1::demo01(void)
{
	//string image_path = base_path + "ce_02.jpg";
	string image_path = base_path + "ce_01.jpg";

	Mat image=cv::imread(image_path);
	if (image.empty())
	{
		cout << "load error" << endl;
		return;
	}
	string src_win_name = "src_win_name";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;

	cv::namedWindow(src_win_name, windows_style);
	cv::imshow(src_win_name,image);
	// 灰度图
	Mat gray;
	cv::cvtColor(image,gray,cv::COLOR_BGR2GRAY);
	//GaussianBlur(gray, gray, cv::Size(3, 3), 0);
	//cv::imshow("gray", gray);
	//二值化
	Mat binary;
	cv::threshold(gray,binary,0,255,
		cv::THRESH_BINARY_INV|cv::THRESH_OTSU);
	cv::imshow("binary", binary);
	//缺少角 或者有划痕 视为次品 有些轻微划痕 不关心
	//去掉轻微划痕
	Mat binary1;
	Mat kernal=cv::getStructuringElement(cv::MORPH_RECT,Size(3,3));
	cv::morphologyEx(binary, binary1,cv::MORPH_OPEN,kernal);
	cv::imshow("binary1", binary1);
	//
	vector<vector<Point>> contours;
	/*cv::findContours(binary1, contours, cv::RETR_LIST,
		cv::CHAIN_APPROX_SIMPLE, Point(0, 0));*/
	cv::findContours(binary1, contours, cv::RETR_LIST,
		cv::CHAIN_APPROX_SIMPLE, Point(0, 0));
	//for (size_t i = 0; i < contours.size(); i++)
	//{
	//	cv::drawContours(image, contours, static_cast<int>(i),
	//		Scalar(0, 0, 255), 1, 8);
	//	cv::imshow("cc"+i, image);
	//	cv::waitKey(5000);
	//	//cv::Point pt = contours[i][0]; // 取轮廓首个点坐标
	//	//cv::putText(image, std::to_string(i), pt,
	//		//cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255));
	//}
	
	int height = image.rows;
	vector<cv::Rect> rects;
	for (size_t i=0U;i<contours.size();i++)
	{
		//计算输入点集或二值图像中轮廓的最小垂直外接矩形。该矩形的边与图像边界平行
		//如果是二值图像 若输入为图像，需确保是二值图（非零像素为前景）
		vector<Point> c = contours[i];
		cv::Rect  rect = cv::boundingRect(c);
		
		if (rect.height > height / 2)
		{
			continue;
		}
		//
		double area=cv::contourArea(c);
		if (area<150)
		{
			continue;
		}
		rects.push_back(rect);
		//cv::rectangle(image, rect, cv::Scalar(0, 255, 0), 1);  // 绘制绿色矩形，线宽2像素
		//cv::drawContours(image, contours, static_cast<int>(i), Scalar(0, 255, 0));
	}
	// 要对外接矩形进行排序
	sort_rect(rects);
	// 现在需要找一个好的 作为模板，这里可以是另一张图的好的模板
	// 为了简单，我就选择一个好的
	//提取ROI 区域作为模板? but why?todowhat
	Mat tpl=binary1(rects[1]);
	//cv::imshow("roi", tpl);
	/*for(size_t i=0;i<rects.size();i++)
	{
		cv::putText(image, std::to_string(i), rects[i].tl(),
		cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0));
	}*/
	//
	vector<cv::Rect> defects;
	dect_defect(tpl,rects,binary1, defects);
	for (size_t i=0;i<defects.size();i++)
	{
		cv::rectangle(image,defects[i],Scalar(0,0,255));
		cv::putText(image, cv::format("bad"), defects[i].tl(),
		cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255, 0));
	}
	//
	cv::imshow("result", image);
	cv::waitKey(0);
	cv::destroyAllWindows();




}
namespace fordemo02
{
	void get_hog_descriptor(Mat &image,vector<float> &desc)
	{
		cv::HOGDescriptor hogdesc;
		int h = image.rows;
		int w = image.cols;
		//转64*128 图像 宽64 长128
		Mat img;
		double ration = 64.0 / w;
		cv::resize(image,img,Size(64,static_cast<int>(ration*h)));
		Mat gray;
		cv::cvtColor(img,gray,cv::COLOR_BGR2GRAY);
		Mat result = Mat::zeros(Size(64,128),CV_8UC1);
		result.setTo(Scalar(127));//
		//
		cv::Rect roi;
		roi.x = 0;
		roi.width = 64;
		roi.y = (128 -gray.rows)/2 ;
		roi.height = gray.rows;

		gray.copyTo(result(roi));
		//
		hogdesc.compute(result,desc,Size(8,8),Size(0,0));

		//hog 宽高必须能被2整除
		printf("desc len=%u\n", static_cast<unsigned int>(desc.size()));
	}
	void generate_dataset(Mat &train_data, Mat &labels)
	{
		vector<string> p_images;
		cv::glob(positive_dir, p_images);
		int nums = static_cast<int>(p_images.size());
		for (int i = 0;i<nums;i++) 
		{
			Mat image = cv::imread(p_images[i]);
			vector<float> fv;
			get_hog_descriptor(image,fv);
			for (int j = 0; j < static_cast<int>(fv.size()); j++)
			{
				train_data.at<float>(i, j) = fv[j];
				//cout << fv[j] << endl;
			}
			labels.at<int>(i,0)= 1;
		}
		vector<string> n_images;
		cv::glob(negative_dir, n_images);
		int n_nums = static_cast<int>(n_images.size());
		for (int i = 0; i < n_nums; i++)
		{
			Mat n_image = cv::imread(n_images[i]);
			vector<float> fv;
			get_hog_descriptor(n_image, fv);
			for (int j = 0; j < static_cast<int>(fv.size()); j++)
			{
				train_data.at<float>(i+ nums, j) = fv[j];
			}
			labels.at<int>(i+ nums, 0) = -1;
		}

	}
	void svm_train(Mat &train_data, Mat &labels)
	{
		
		cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
		svm->setC(2.67);
		svm->setType(cv::ml::SVM::C_SVC);
		svm->setKernel(cv::ml::SVM::LINEAR);
		svm->setGamma(5.383);
		svm->train(train_data, cv::ml::ROW_SAMPLE, labels);
		//
		svm->save(base_path+"hog_elec.xml");
	}
	void test(void)
	{
		Mat result = Mat::zeros(Size(640, 1280), CV_8UC1);
		cv::imshow("result",result);
		//result = Scalar(127);//
		result.setTo(Scalar(127));//
		cv::imshow("test",result);
		cv::waitKey(0);
		cv::destroyAllWindows();
	}
}
void case2::demo02(void)
{
	//
	//Mat train_data = Mat::zeros(Size(3780,26),CV_32FC1);
	//Mat labels= Mat::zeros(Size(1, 26), CV_32SC1);
	//fordemo02::generate_dataset(train_data, labels);
	
	//fordemo02::svm_train(train_data,labels);
	//
	cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::load(base_path+ "hog_elec.xml");
	//
	Mat test = cv::imread("J:/vs2017ws/data/elec_watch/test/scene_01.jpg");
	cv::resize(test,test,Size(0,0),0.2,0.2);
	//
	cv::Rect rect;
	rect.width = 64;
	rect.height = 128;
	int sum_x = 0;
	int sum_y = 0;
	int count = 0;
	//
	for (int row=64;row<test.rows-64;row+=4) 
	{
		for (int col=32;col<test.cols-32;col+=4)
		{
			rect.x = col - 32;
			rect.y = row - 64;
			vector<float> fv;
			Mat roi=test(rect);
			fordemo02::get_hog_descriptor(roi,fv);
			Mat one_row = Mat::zeros(Size(fv.size(),1),CV_32FC1);
			for (int i=0;i<static_cast<int>(fv.size());i++)
			{
				one_row.at<float>(0, i) = fv[i];
			}
			float fflag = svm->predict(one_row);
			if (fflag>0)
			{
				//cv::rectangle(test,rect,Scalar(0,0,255),1);
				count++;
				sum_x += rect.x;
				sum_y += rect.y;
			}
		}
	}










	//
	rect.x = sum_x / count;
	rect.y = sum_y / count;
	cv::rectangle(test, rect, Scalar(0, 255, 0), 1);
	cv::imshow("src",test);
	cv::waitKey(0);
	cv::destroyAllWindows();
}
