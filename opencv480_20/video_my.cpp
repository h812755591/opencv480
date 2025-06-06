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
	void process_frame_back_ground(Mat &image,
		cv::Ptr<cv::BackgroundSubtractorMOG2> &ptr)
	{
		Mat mask;
		ptr->apply(image, mask);

		Mat se = getStructuringElement(cv::MORPH_RECT, Size(1, 5), 
			Point(-1, -1));
		morphologyEx(mask, mask, cv::MORPH_OPEN, se);
		imshow("mask", mask);
		// 形态学操作
		vector<vector<Point>> contours;
		vector<cv::Vec4i> hirearchy;
		findContours(mask, contours, hirearchy, cv::RETR_EXTERNAL, 
			cv::CHAIN_APPROX_SIMPLE, Point());
		for (size_t t = 0; t < contours.size(); t++) {
			double area = contourArea(contours[t]);
			if (area < 100) {
				continue;
			}
			cv::Rect box = boundingRect(contours[t]);
			cv::RotatedRect rrt = minAreaRect(contours[t]);
			// rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
			circle(image, rrt.center, 2, Scalar(255, 0, 0), 2, 8, 0);
			ellipse(image, rrt, Scalar(0, 0, 255), 2, 8);
		}
	}
	void test(void)
	{
		cv::Ptr<cv::BackgroundSubtractorMOG2> pMOG2 =
			cv::createBackgroundSubtractorMOG2(500, 16, false);
		cout<<"VarInit="<<pMOG2->getVarInit() <<endl;//VarInit=15
		
	}
	void draw_lines(Mat &frame, vector<cv::Point2f> pts1, 
		vector<cv::Point2f> pts2, cv::RNG &rng)
	{
		vector<Scalar> lut;
		for (size_t t = 0; t < pts1.size(); t++) {
			int b = rng.uniform(0, 255);
			int g = rng.uniform(0, 255);
			int r = rng.uniform(0, 255);
			lut.push_back(Scalar(b, g, r));
		}
		for (size_t t = 0; t < pts1.size(); t++) {
			line(frame, pts1[t], pts2[t], lut[t], 2, 8, 0);
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

void MyVideo::video_demo07_background(void)
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
	Mat frame;
	string do_frame_winow = "do_frame_winow";
	namedWindow(do_frame_winow, windows_style);
	cv::Ptr<cv::BackgroundSubtractorMOG2> pMOG2 = 
		cv::createBackgroundSubtractorMOG2(500, 100, false);
	while (true)
	{
		bool result = capture.read(frame);
		if (!result) break;
		cv::imshow(video_win_name, frame);
		process_frame_back_ground(frame, pMOG2);
		imshow(do_frame_winow, frame);

		int delay = static_cast<int>(1000 / fps);
		int key = cv::waitKey(delay/2);
		if (key != -1)
		{
			if ((key & 0xFF) == 'q') break;
		}
	}
	cv::waitKey(0);
	cv::destroyAllWindows();
	capture.release();
}

void MyVideo::video_demo08_objecttrack_KLT(void)
{
	VideoCapture capture;
	string file_name = "J:/vs2017ws/data/bike.avi";             // 0 = open default camera
	int apiID = cv::CAP_ANY;      // 0 = autodetect default API
	capture.open(file_name, apiID);
	if (!capture.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
		return;
	}
	//
	double fps = capture.get(cv::CAP_PROP_FPS);
	//
	cv::RNG rng(12345);
	namedWindow("frame", cv::WINDOW_AUTOSIZE);
	Mat old_frame, old_gray;
	capture.read(old_frame);
	cvtColor(old_frame, old_gray, cv::COLOR_BGR2GRAY);
	vector<cv::Point2f> feature_pts;
	vector<cv::Point2f> initPoints;
	double quality_level = 0.01;
	int minDistance = 20;
	goodFeaturesToTrack(old_gray, feature_pts, 5000, quality_level, minDistance, 
		Mat(), 3, false);
	Mat frame, gray;
	vector<cv::Point2f> pts[2];
	pts[0].insert(pts[0].end(), feature_pts.begin(), feature_pts.end());
	initPoints.insert(initPoints.end(), feature_pts.begin(), feature_pts.end());
	vector<uchar> status;
	vector<float> err;
	cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::COUNT + 
		cv::TermCriteria::EPS, 30, 0.01);

	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		imshow("frame", frame);
		cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

		// calculate optical flow
		calcOpticalFlowPyrLK(old_gray, gray, pts[0], pts[1], status, err, Size(31, 31), 3, criteria, 0);
		size_t i = 0, k = 0;
		for (i = 0; i < pts[1].size(); i++) {
			double dist = abs(pts[0][i].x - pts[1][i].x) + abs(pts[0][i].y - pts[1][i].y);
			if (status[i] && dist > 2) {
				pts[0][k] = pts[0][i];
				initPoints[k] = initPoints[i];
				pts[1][k++] = pts[1][i];
				int b = rng.uniform(0, 255);
				int g = rng.uniform(0, 255);
				int r = rng.uniform(0, 255);
				circle(frame, pts[1][i], 2, Scalar(b, g, r), 2, 8, 0);
			}
		}

		// update key points
		pts[0].resize(k);
		pts[1].resize(k);
		initPoints.resize(k);

		
		draw_lines(frame, initPoints, pts[1], rng);

	
		imshow("KLT-demo", frame);
		int delay = static_cast<int>(1000 / fps);
		int key = cv::waitKey(delay);
		if (key != -1)
		{
			if ((key & 0xFF) == 'q') break;
		}

		// update to old
		std::swap(pts[1], pts[0]);
		cv::swap(old_gray, gray);

		// re-init
		if (pts[0].size() < 40) {
			goodFeaturesToTrack(old_gray, feature_pts, 5000, quality_level, minDistance, Mat(), 3, false);
			pts[0].insert(pts[0].end(), feature_pts.begin(), feature_pts.end());
			initPoints.insert(initPoints.end(), feature_pts.begin(), feature_pts.end());
		}
	}
	cv::waitKey(0);
	cv::destroyAllWindows();
	capture.release();
}
