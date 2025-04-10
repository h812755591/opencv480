#include "util.h"  
cv::Mat util::read_img(const std::string& path) {
	// TODO: 在此处插入 return 语句
	cv::Mat img = cv::imread(path);
	if (img.empty())
	{
		throw std::runtime_error("Resource not found: " + path);
		throw cv::Exception(cv::Error::StsError, "Failed to load image",
			__func__, __FILE__, __LINE__);
	}
	return img;
}




