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
		bitwise_and(frame, frame, result, mask);
		imshow("mask", mask);
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
