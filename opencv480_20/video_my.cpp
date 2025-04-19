#include <iostream>
#include <opencv2/opencv.hpp>
#include "util.h"
#include "video_my.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using cv::Mat;
using cv::imread;
using cv::Scalar;
using cv::Size;
using cv::Point;
using std::vector;
using cv::VideoCapture;
using cv::namedWindow;
void MyVideo::video_demo01_rw(void)
{
	VideoCapture capture;
	int deviceID = 0;             // 0 = open default camera
	int apiID = cv::CAP_ANY;      // 0 = autodetect default API
	capture.open(deviceID,apiID);
	if (!capture.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
		return;
	}
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	string video_win_name = "framewin";
	namedWindow(video_win_name, windows_style);
	Mat frame;
	cout<< capture.getBackendName() << endl;
	while (true)
	{
		bool result=capture.read(frame);
		if (!result)
		{
			break;
		}
		cv::imshow(video_win_name,frame);
		int key = cv::waitKey(1);
		if (key!=-1)
		{
			if ((key & 0xFF) == 'q')
			{
				break;
			}
		}
	}
	cv::waitKey(0);
	cv::destroyAllWindows();
	capture.release();
}

void MyVideo::video_demo02_rw_file(void)
{
	VideoCapture capture;
	string file_name = "J:/vs2017ws/data/vtest.avi";             // 0 = open default camera
	int apiID = cv::CAP_ANY;      // 0 = autodetect default API
	capture.open(file_name, apiID);
	if (!capture.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
		return;
	}
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	string video_win_name = "framewin";
	namedWindow(video_win_name, windows_style);
	//
	double fps = capture.get(cv::CAP_PROP_FPS);
	double width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
	double height = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
	double num_of_frames = capture.get(cv::CAP_PROP_FRAME_COUNT);
	double type = capture.get(cv::CAP_PROP_FOURCC);
	cv::VideoWriter writer("J:/vs2017ws/data/vtest_copy.avi", 
		static_cast<int>(capture.get(cv::CAP_PROP_FOURCC)),
		fps, cv::Size(static_cast<int>(width), static_cast<int>(height)), true);
	//
	Mat frame;
	cout << capture.getBackendName() << endl;//FFMPEG
	while (true)
	{
		bool result = capture.read(frame);
		if (!result)
		{
			break;
		}
		cv::imshow(video_win_name, frame);
		writer.write(frame);
		int delay = static_cast<int>(1000 / fps);
		int key = cv::waitKey(delay);
		if (key != -1)
		{
			if ((key & 0xFF) == 'q')
			{
				break;
			}
		}
	}
	cv::destroyAllWindows();
	writer.release();
	capture.release();
}

void MyVideo::video_demo03_rw_url(void)
{
	VideoCapture capture;
	string file_name = "http://vjs.zencdn.net/v/oceans.mp4";
	int apiID = cv::CAP_ANY;      // 0 = autodetect default API
	capture.open(file_name, apiID);
	if (!capture.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
		return;
	}
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	string video_win_name = "framewin";
	namedWindow(video_win_name, windows_style);
	//
	double fps = capture.get(cv::CAP_PROP_FPS);
	double width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
	double height = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
	double num_of_frames = capture.get(cv::CAP_PROP_FRAME_COUNT);
	double type = capture.get(cv::CAP_PROP_FOURCC);
	/*cv::VideoWriter writer("J:/vs2017ws/data/tv.avi",
		static_cast<int>(capture.get(cv::CAP_PROP_FOURCC)),
		fps, cv::Size(static_cast<int>(width), static_cast<int>(height)), true);*/
	//
	Mat frame;
	cout << capture.getBackendName() << endl;//FFMPEG
	while (true)
	{
		bool result = capture.read(frame);
		if (!result)
		{
			break;
		}
		cv::imshow(video_win_name, frame);
		//writer.write(frame);
		int key = cv::waitKey(1);
		if (key != -1)
		{
			if ((key & 0xFF) == 'q')
			{
				break;
			}
		}
	}
	cv::destroyAllWindows();
	//writer.release();
	capture.release();
}

void MyVideo::video_demo03_color_space(void)
{
	VideoCapture capture;
	string file_name = "J:/vs2017ws/data/vtest.avi";             // 0 = open default camera
	int apiID = cv::CAP_ANY;      // 0 = autodetect default API
	capture.open(file_name, apiID);
	if (!capture.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
		return;
	}
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	string video_win_name = "framewin";
	namedWindow(video_win_name, windows_style);
	//
	double fps = capture.get(cv::CAP_PROP_FPS);
	double width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
	double height = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
	double num_of_frames = capture.get(cv::CAP_PROP_FRAME_COUNT);
	double type = capture.get(cv::CAP_PROP_FOURCC);
	
	//
	Mat frame;
	Mat hsv;
	Mat lab;
	cout << capture.getBackendName() << endl;//FFMPEG
	while (true)
	{
		bool result = capture.read(frame);
		if (!result)
		{
			break;
		}
		cv::imshow(video_win_name, frame);
		cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
		imshow("hsv", hsv);
		/*cvtColor(frame, lab, cv::COLOR_BGR2Lab);
		imshow("lab", lab);*/
		int delay = static_cast<int>(1000 / fps);
		int key = cv::waitKey(delay);
		if (key != -1)
		{
			if ((key & 0xFF) == 'q')
			{
				break;
			}
		}
	}
	cv::destroyAllWindows();
	capture.release();
}

void MyVideo::video_demo04_hsv(void)
{
	VideoCapture capture;
	string file_name = "J:/vs2017ws/data/01.mp4";             // 0 = open default camera
	int apiID = cv::CAP_ANY;      // 0 = autodetect default API
	capture.open(file_name, apiID);
	if (!capture.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
		return;
	}
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	string video_win_name = "framewin";
	namedWindow(video_win_name, windows_style);
	//
	double fps = capture.get(cv::CAP_PROP_FPS);
	double width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
	double height = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
	double num_of_frames = capture.get(cv::CAP_PROP_FRAME_COUNT);
	double type = capture.get(cv::CAP_PROP_FOURCC);

	//
	Mat frame;
	Mat hsv;
	Mat mask;
	Mat result;
	cout << capture.getBackendName() << endl;//FFMPEG
	while (true)
	{
		bool res = capture.read(frame);
		if (!res)
		{
			break;
		}
		cv::imshow(video_win_name, frame);
		cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
		imshow("hsv", hsv);
		inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);
		bitwise_not(mask, mask);
		//frame & frame=frame 
		//mask 非零区域显示原图像素，其余区域为黑色
		bitwise_and(frame, frame, result, mask);
		//imshow("mask", mask);
		imshow("result", result);
		int delay = static_cast<int>(1000 / fps);
		int key = cv::waitKey(delay);
		if (key != -1)
		{
			if ((key & 0xFF) == 'q')
			{
				break;
			}
		}
	}
	cv::destroyAllWindows();
	capture.release();
}

void MyVideo::video_demo04_hand(void)
{
	Mat model = imread("J:/vs2017ws/data/sample.png");
	Mat target = imread("J:/vs2017ws/data/target.png");

	namedWindow("input", cv::WINDOW_AUTOSIZE); 
	namedWindow("sample", cv::WINDOW_AUTOSIZE);
	imshow("input", target);
	imshow("sample", model);

	Mat model_hsv;
	cvtColor(model, model_hsv, cv::COLOR_BGR2HSV);
	Mat  target_hsv;
	cvtColor(target, target_hsv, cv::COLOR_BGR2HSV);

	int h_bins = 32, s_bins = 32;
	int histSize[] = { h_bins, s_bins };
	int channels[] = { 0, 1 };
	Mat roiHist;
	float h_range[] = { 0, 180 };
	float s_range[] = { 0, 255 };
	const float* ranges[] = { h_range, s_range };
	calcHist(&model_hsv, 1, channels, Mat(), roiHist, 2, histSize, ranges, true, false);
	normalize(roiHist, roiHist, 0, 255, cv::NORM_MINMAX, -1, Mat());
	cv::MatND backproj;
	calcBackProject(&target_hsv, 1, channels, roiHist, backproj, ranges, 1.0);
	imshow("back projection demo", backproj);

	cv::waitKey(0);
	cv::destroyAllWindows();
}

void MyVideo::video_demo05_hand1(void)
{
	
	Mat model = imread("J:/vs2017ws/data/sample.png");
	Mat src = imread("J:/vs2017ws/data/hand.jpg");

	namedWindow("input", cv::WINDOW_AUTOSIZE);
	imshow("input", src);
	imshow("sample", model);

	Mat model_hsv, image_hsv;
	cvtColor(model, model_hsv, cv::COLOR_BGR2HSV);
	cvtColor(src, image_hsv, cv::COLOR_BGR2HSV);

	int h_bins = 32, s_bins = 32;
	int histSize[] = { h_bins, s_bins };
	int channels[] = { 0, 1 };
	Mat roiHist;
	float h_range[] = { 0, 180 };
	float s_range[] = { 0, 255 };
	const float* ranges[] = { h_range, s_range };
	calcHist(&model_hsv, 1, channels, Mat(), roiHist, 2, histSize, ranges, true, false);
	normalize(roiHist, roiHist, 0, 255, cv::NORM_MINMAX, -1, Mat());
	cv::MatND backproj;
	calcBackProject(&image_hsv, 1, channels, roiHist, backproj, ranges, 1.0);
	imshow("back projection demo", backproj);

	cv::waitKey(0);
	cv::destroyAllWindows();

}
namespace
{
	void process_frame(Mat &image) {
		Mat hsv, mask;
		cvtColor(image, hsv, cv::COLOR_BGR2HSV);
		inRange(hsv, Scalar(0, 43, 46), Scalar(10, 255, 255), mask);
		Mat se = getStructuringElement(cv::MORPH_RECT, Size(15, 15));
		morphologyEx(mask, mask, cv::MORPH_OPEN, se);

		vector<vector<Point>> contours;
		vector<cv::Vec4i> hirearchy;
		findContours(mask, contours, hirearchy, cv::RETR_EXTERNAL, 
			cv::CHAIN_APPROX_SIMPLE, Point());
		int index = -1;
		double max_area = 0;
		for (size_t t = 0; t < contours.size(); t++) {
			double area = contourArea(contours[t]);
			if (area > max_area) {
				max_area = area;
				index = static_cast<int>(t);
			}
		}

		// 进行轮廓离合于输出
		if (index >= 0) {
			cv::RotatedRect rrt = minAreaRect(contours[index]);
			ellipse(image, rrt, Scalar(255, 0, 0), 2, 8);
			circle(image, rrt.center, 4, Scalar(0, 255, 0), 2, 8, 0);
		}
		
	}

}
void MyVideo::video_demo06_obj_tracer_based_color(void)
{
	VideoCapture capture;
	string file_name = "J:/vs2017ws/data/color_object.mp4";             // 0 = open default camera
	int apiID = cv::CAP_ANY;      // 0 = autodetect default API
	capture.open(file_name, apiID);
	if (!capture.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
		return;
	}
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	string video_win_name = "framewin";
	namedWindow(video_win_name, windows_style);
	//
	double fps = capture.get(cv::CAP_PROP_FPS);
	Mat frame;
	string color_win_name = "colorwin";
	namedWindow(color_win_name, windows_style);
	while (true)
	{
		bool result = capture.read(frame);
		if (!result) break;
		cv::imshow(video_win_name, frame);
		process_frame(frame);
		imshow(color_win_name, frame);;
		
		int delay = static_cast<int>(1000 / fps);
		int key = cv::waitKey(delay);
		if (key != -1)
		{
			if ((key & 0xFF) == 'q') break;
		}
	}
	cv::waitKey(0);
	cv::destroyAllWindows();
	capture.release();
}
