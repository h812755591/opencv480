#include <opencv2/opencv.hpp>
#include "corner_dect.h"


int main(int argc,char * argv[])
{
	yolov5pro::CornerDect cd;
	//cd.demo01_tomasi();
	//cd.demo02_ORB();
	//cd.demo03_SIFT();
	//cd.demo05_findHomography();
	cd.demo06_findHomography();
	return 0;
}