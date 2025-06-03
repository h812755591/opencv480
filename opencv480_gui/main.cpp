#include <opencv2/opencv.hpp>
#include <string>
#include "start_image.h"
#include "start_video.h"
#include "draw_function.h"
#include "core_operation.h"
#include "image_processing.h"



int main()
{
	/*start_image::show();*/
	//start_video::demo01();
	//draw_func::demo01_circle();
	//basic_operation::demo01_access_modify();
	//basic_operation::demo02_split_merge();
	//basic_operation::demo03_boarder();
	//arithmetic_operation::demo01_add();
	//arithmetic_operation::demo02_add_weight();
	//arithmetic_operation::demo03_add_weight();
	//arithmetic_operation::demo04_Bitwise_Operations();
	//arithmetic_operation::demo05_Bitwise_Operations();
	//changing_colorspaces::demo01_inRange();
	//image_thresholding::demo01_threshold();
	image_thresholding::demo02_adaptive_threshold();
	return 1;
}