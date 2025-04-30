#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	VideoCapture capture("D:/images/video/vtest.avi");
	if (!capture.isOpened()) {
		printf("could not open the camera...\n");
	}
	namedWindow("frame", WINDOW_AUTOSIZE);
	Mat frame, preFrame;
	Mat gray, preGray;
	capture.read(preFrame);
	cvtColor(preFrame, preGray, COLOR_BGR2GRAY);
	Mat hsv = Mat::zeros(preFrame.size(), preFrame.type());
	Mat mag = Mat::zeros(hsv.size(), CV_32FC1);
	Mat ang = Mat::zeros(hsv.size(), CV_32FC1);
	Mat xpts = Mat::zeros(hsv.size(), CV_32FC1);
	Mat ypts = Mat::zeros(hsv.size(), CV_32FC1);
	Mat_<Point2f> flow;
	vector<Mat> mv;
	split(hsv, mv);
	Mat bgr;
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		calcOpticalFlowFarneback(preGray, gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
		for (int row = 0; row < flow.rows; row++) {
			for (int col = 0; col < flow.cols; col++) {
				const Point2f &flow_xy = flow.at<Point2f>(row, col);
				xpts.at<float>(row, col) = flow_xy.x;
				ypts.at<float>(row, col) = flow_xy.y;
			}
		}
		cartToPolar(xpts, ypts, mag, ang);
		ang = ang * 180 / CV_PI / 2.0;
		normalize(mag, mag, 0, 255, NORM_MINMAX);
		convertScaleAbs(mag, mag);
		convertScaleAbs(ang, ang);
		mv[0] = ang;
		mv[1] = Scalar(255);
		mv[2] = mag;
		merge(mv, hsv);
		cvtColor(hsv, bgr, COLOR_HSV2BGR);
		imshow("frame", frame);
		imshow("result", bgr);
		char c = waitKey(1);
		if (c == 27) { // ESC
			break;
		}
	}
	capture.release();

	waitKey(0);
	destroyAllWindows();
}
