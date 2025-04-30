#pragma once
#include <opencv2/opencv.hpp>

enum DM_DEFECT_TYPE {
	DM_MISSING,
	DM_SKEW,
	DM_OK// 正常
};

struct DMResult {
	cv::Rect rect; // 二维码位置信息
	DM_DEFECT_TYPE type = DM_DEFECT_TYPE::DM_OK; // 错误类型
};

class DMSkewMissBlurDetector {
public:
	void loadConfig(std::string configPath);
	void detect(cv::Mat &himage, DMResult &result);
private:
	int line_length = 85; // DM码的两条边
	int support_decode = 0; // 是否尝试解码, 0 不解码
	float aspect_rate = 0.75; // 横纵比
	double min_area = 5000; // 最小面积
	float threshod_angle = 5.0;
};