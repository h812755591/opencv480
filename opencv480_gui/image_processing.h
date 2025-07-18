#pragma once
#ifndef IMAGE_PROCESSING_H_
#define IMAGE_PROCESSING_H_
namespace changing_colorspaces
{
	/*
	H = round(H);         // 0~179
	S = round(S * 255);   // 0~255
	V = round(V * 255);   // 0~255 V=Cmax 

​

	*/
	void demo01_inRange(void);
	void demo02_inRange(void);

}
namespace geometric_transformations
{
	//图像的几何变化
	void demo01_warpAffine(void);
	void demo02_warpAffine_rotation(void);//旋转变换
	void demo03_warpAffine_Shear(void);//剪切变换
	void demo04_rotation90(void);//顺时针旋转90度
	void demo05_Perspective(void);//透视变换
}
namespace image_thresholding
{
	void demo01_threshold(void);
	void demo02_adaptive_threshold(void);
}
namespace smoothing_images
{
	void demo01_filter2D(void);
	void demo01_blur(void);
}
namespace morphological_transformation
{
	/*
	腐蚀和膨胀不仅适用于二值图像，也适用于灰度图像
	Morphological Gradient 还有梯度  这个是先膨胀 -后腐蚀
	top hat 原图-open
	black hat close -src
	*/
	void demo01_erosion(void);//
	void demo02_dilation(void);//
	void demo03_open(void);//腐蚀+膨胀
	void demo04_closed(void);//膨胀+腐蚀
}

namespace countours
{
	void demo01_find(void);
	void demo02_analize(void);
	void demo03_match(void);//轮廓匹配
	void demo04_proxy(void);//轮廓逼近
}
namespace hough_trans
{
	void demo_line(void);//霍夫直线检测
	void demo_circle(void);//霍夫直线检测
}
#endif // !IMAGE_PROCESSING_H_
