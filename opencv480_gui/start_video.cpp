#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include "start_video.h"

using std::string;
using cv::Mat;
using cv::imread;
using cv::waitKey;
using cv::namedWindow;
using std::endl;
using std::cout;

namespace
{

}
void start_video::demo01(void)
{
	/*int deviceID = 0;//0是摄像头设备的默认索引号  对应操作系统识别的第一个可用摄像头 还可以用1 2 3
	int apiID = cv::CAP_ANY;  // 自动选择后端API
	cv::VideoCapture capture;
	capture.open(deviceID,apiID);
	​跨平台差异​
​Windows​：优先使用 cv::CAP_DSHOW 后端提高稳定性
。
​Linux​：使用 cv::CAP_V4L2 并检查摄像头权限（如 /dev/video0）。
	
	*/
	cv::VideoCapture capture=cv::VideoCapture(0, cv::CAP_ANY);

	if (!capture.isOpened()) {
		printf("Cannot open camera\n");
		exit(1);
	}
	capture.set(cv::CAP_PROP_FRAME_WIDTH,1920);
	capture.set(cv::CAP_PROP_FRAME_HEIGHT, 1200);
	double actual_w = capture.get(cv::CAP_PROP_FRAME_WIDTH);
	double actual_h = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
	std::cout << "实际分辨率: " << actual_w << "x" << actual_h << std::endl;
	//cout << capture.getBackendName() << endl;
	Mat frame;
	// 
	int windows_style = cv::WINDOW_NORMAL | cv::WINDOW_FREERATIO;
	string video_win_name = "framewin";
	namedWindow(video_win_name, windows_style);
	for (;;)
	{
		bool result = capture.read(frame);
		if (!result)
		{
			break;
		}
		cv::resize(frame,frame,cv::Size(1920,1200));
		cv::imshow(video_win_name, frame);
		/*
		cv::waitKey() 是 ​唯一负责更新图像窗口内容​ 的函数。
		即使调用了 cv::imshow() 显示帧，若后续未调用 cv::waitKey()，
		窗口将无法刷新，导致视频画面卡死
		实际帧率由 delay 和 ​帧处理耗时​（读取、解码、显示）共同决定。
		若 capture.read() 或图像处理耗时超过 delay，
		会导致视频卡顿或丢帧
		实时视频的理想 delay 值需通过实验校准，通常介于 1ms（低延迟）到 33ms（30 FPS）之间
		double fps = capture.get(cv::CAP_PROP_FPS);  // 部分摄像头可能返回0或错误值[7](@ref)
		int delay = (fps > 0) ? static_cast<int>(1000 / fps) : 30;  // 默认30ms
		*/
		double fps = capture.get(cv::CAP_PROP_FPS);
		int delay = (fps > 0) ? static_cast<int>(1000 / fps) : 25;  // 默认30ms
		//cout << "delay="<<delay << endl;
		//int key = cv::waitKey(1);  // 快速响应按键和刷新

		int key = cv::waitKey(delay);//cv::waitKey 是必须调用的可以刷新视频 // 快速响应按键和刷新
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
/*
动态延迟补偿
auto start = std::chrono::high_resolution_clock::now();

// 复杂处理（如目标检测）
process_frame(frame);

auto end = std::chrono::high_resolution_clock::now();
int processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

int adjusted_delay = std::max(1, delay - processing_time);
cv::waitKey(adjusted_delay);

*/
/*
std::thread capture_thread([&]() {
	while (running) {
		capture.read(frame);  // 独立线程读取帧
	}
});

std::thread process_thread([&]() {
	while (running) {
		if (!frame.empty()) {
			cv::imshow("视频", frame);
			cv::waitKey(30);  // 主线程控制显示
		}
	}
});


*/
/*
cap.set(propId, value).
cap.get(propId) 可以设置窗口大小等属性

*/