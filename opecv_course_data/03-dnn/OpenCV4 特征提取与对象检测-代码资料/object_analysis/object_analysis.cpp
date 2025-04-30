#include "ORBDetector.h"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat refImg = imread("D:/facedb/tiaoma/tpl2.png");
	ORBDetector orb_detector;
	orb_detector.initORB(refImg);
	vector<std::string> files;
	glob("D:/facedb/orb_barcode", files);
	cv::Mat temp;
	for (auto file : files) {
		std::cout << file << std::endl;
		cv::Mat image = imread(file);
		int64 start = getTickCount();
		bool OK = orb_detector.detect_and_analysis(image, temp);
		double ct = (getTickCount() - start) / getTickFrequency();
		printf("decode time: %.5f ms\n", ct * 1000);
		std::cout <<"±êÇ©: "<< (OK == true) << std::endl;
		imshow("temp", temp);
		waitKey(0);
	}
}