#include <iostream>
#include <opencv2/opencv.hpp>
#include "binary.h"
#include "connected_component.h" 
#include "contour.h"

int main(int argc, char * argv[])
{
	//二值化
	//Binary binary;
	//binary.binary_demo01();
	//binary.binary_demo02_THRESH_BINARY_INV();
	//binary.binary_demo02_all();
	//binary.binary_demo03_otsu();
	//binary.binary_demo04_local();
	//连通组件
	//ConnectedComponent cc;
	//cc.connected_component_demo01();
	//cc.connected_component_demo02_stats();
	//轮廓
	ContourMy cy;
	//cy.contour_demo01_find();
	//cy.contour_demo02_area();
	//cy.contour_demo03_match();
	cy.contour_demo04_approxi01();//多边形逼近
	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}

