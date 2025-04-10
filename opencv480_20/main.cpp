#include <iostream>
#include <opencv2/opencv.hpp>
#include "binary.h"


int main(int argc, char * argv[])
{
	Binary binary;
	//binary.binary_demo01();
	//binary.binary_demo02_THRESH_BINARY_INV();
	//binary.binary_demo02_all();
	//binary.binary_demo03_otsu();
	binary.binary_demo04_local();
	//
	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}

