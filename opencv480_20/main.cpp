#include <iostream>
#include <opencv2/opencv.hpp>
#include "binary.h"
#include "connected_component.h" 
#include "contour.h"
#include "hough.h"
#include "morphological_transformations.h"
#include "video_my.h"
#include "corner_dect.h"
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
	//ContourMy cy;
	//cy.contour_demo01_find();
	//cy.contour_demo02_area();
	//cy.contour_demo03_match();
	//cy.contour_demo04_approxi01();//多边形逼近
	//cy.contour_demo04_fit_circle01();
	//Hough20::Hough hough;
	//hough.hough_demo01_hough_lines();
	//hough.hough_demo02_hough_lines();
	//hough.hough_demo03_hough_test();
	//hough.hough_demo04_hough_circle();
	//MorphologicalOperation mo;
	//mo.morphological_demo01_erode();
	//mo.morphological_demo03_erode();
	//mo.morphological_demo02_dilate();
	//mo.morphological_demo04_dilate();
	//mo.morphological_demo05_open();
	//mo.morphological_demo06_closed();
	//mo.morphological_demo07_lines();
	//mo.morphological_demo09_tophat();
	//mo.morphological_demo10_hitmiss();
	//mo.morphological_demo11_case01();
	//mo.morphological_demo11_case02();
	MyVideo mv;
	//mv.video_demo01_rw();
	//mv.video_demo02_rw_file();
	//mv.video_demo03_rw_url();
	//mv.video_demo03_color_space();
	//mv.video_demo04_hsv();
	//mv.video_demo04_hand();
	//mv.video_demo06_obj_tracer_based_color();
	mv.video_demo07_background();
	//CornerDect cornerDect;
	//cornerDect.demo01_harris();
	//cornerDect.demo01_thomas();
	return 0;
}

