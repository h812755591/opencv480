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
	void demo01_erosion(void);
}
#endif // !IMAGE_PROCESSING_H_
