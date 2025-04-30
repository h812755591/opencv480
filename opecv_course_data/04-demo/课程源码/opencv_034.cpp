#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	VideoCapture capture;
	capture.open("http://ivi.bupt.edu.cn/hls/cctv6hd.m3u8");
	// VideoCapture capture("D:/images/video/vtest.avi");
	if (!capture.isOpened()) {
		printf("could not open the camera...\n");
	}
	namedWindow("frame", WINDOW_AUTOSIZE);
	int fps = capture.get(CAP_PROP_FPS);
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int num_of_frames = capture.get(CAP_PROP_FRAME_COUNT);
	int type = capture.get(CAP_PROP_FOURCC);
	printf("frame size(w=%d, h=%d), FPS:%d, frames: %d \n", width, height, fps, num_of_frames);

	Mat frame;
	VideoWriter writer("D:/test.mp4", type, fps, Size(width, height), true);
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		imshow("frame", frame);
		writer.write(frame);
		char c = waitKey(5);
		if (c == 27) { // ESC
			break;
		}
	}
	capture.release();
	writer.release();

	waitKey(0);
	destroyAllWindows();
}