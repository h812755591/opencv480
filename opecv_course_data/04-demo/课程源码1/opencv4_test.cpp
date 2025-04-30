#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/images/test.png");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	VideoCapture capture(0);
	int type = static_cast<int>(capture.get(CAP_PROP_FOURCC));
	int height = static_cast<int>(capture.get(CAP_PROP_FRAME_HEIGHT));
	int width = static_cast<int>(capture.get(CAP_PROP_FRAME_WIDTH));
	VideoWriter out("D:/test.mp4", type, 15, Size(width, height), true);
	Mat frame;
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;

		imshow("frame", frame);
		out.write(frame);
		char c = waitKey(50);
		if (c == 27) {
			break;
		}
	}

	waitKey(0);
	destroyAllWindows();
	return 0;
}
