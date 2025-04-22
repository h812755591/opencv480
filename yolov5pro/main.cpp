#include <opencv2/opencv.hpp>
#include "corner_dect.h"


int main(int argc,char * argv[])
{
	yolov5pro::CornerDect cd;
	cd.demo01_tomasi();
	return 0;
}