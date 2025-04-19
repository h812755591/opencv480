#include <iostream>
#include <opencv2/opencv.hpp>
#include "util.h"
#include "corner_dect.h"
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
namespace {

	void harris_do(Mat &image)
	{
		Mat gray;
		cvtColor(image, gray, cv::COLOR_BGR2GRAY);
		Mat dst;
		double k = 0.04;
		int blocksize = 2;//2-7
		int ksize = 3;
		cornerHarris(gray, dst, blocksize, ksize, k);
		Mat dst_norm = Mat::zeros(dst.size(), dst.type());
		normalize(dst, dst_norm, 0, 255, cv::NORM_MINMAX, -1, Mat());
		//dst_norm 元素类型和dst 一样都是CV_32FC1 
		//
		convertScaleAbs(dst_norm, dst_norm);

		// draw corners
		cv::RNG rng(12345);
		for (int row = 0; row < image.rows; row++) {
			for (int col = 0; col < image.cols; col++) {
				int rsp = dst_norm.at<uchar>(row, col);
				if (rsp > 150) {
					int b = rng.uniform(0, 255);
					int g = rng.uniform(0, 255);
					int r = rng.uniform(0, 255);
					circle(image, Point(col, row), 5, Scalar(b, g, r), 2, 8, 0);
				}
			}
		}
	}
	void thomas_do(Mat &image)
	{
		Mat gray;
		cvtColor(image, gray, cv::COLOR_BGR2GRAY);
		vector<cv::Point2f> corners;
		double quality_level = 0.01;
		cv::RNG rng(12345);
		goodFeaturesToTrack(gray, corners, 200, quality_level, 3, Mat(), 3, false);
		for (int i = 0; i < corners.size(); i++) {
			int b = rng.uniform(0, 255);
			int g = rng.uniform(0, 255);
			int r = rng.uniform(0, 255);
			circle(image, corners[i], 5, Scalar(b, g, r), 2, 8, 0);
		}
	}
}
void CornerDect::demo01_harris(void)
{
	VideoCapture capture;
	string file_name = "J:/vs2017ws/data/bike.avi";             // 0 = open default camera
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
	string corner_win_name = "cornerwin";
	namedWindow(corner_win_name, windows_style);
	while (true)
	{
		bool result = capture.read(frame);
		if (!result) break;
		cv::imshow(video_win_name, frame);
		harris_do(frame);
		imshow(corner_win_name, frame);
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

void CornerDect::demo01_thomas(void)
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
	string corner_win_name = "cornerwin";
	namedWindow(corner_win_name, windows_style);
	while (true)
	{
		bool result = capture.read(frame);
		if (!result) break;
		cv::imshow(video_win_name, frame);
		thomas_do(frame);
		imshow(corner_win_name, frame);
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
