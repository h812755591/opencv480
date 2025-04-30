#pragma once
#include <opencv2/opencv.hpp>

enum DM_DEFECT_TYPE {
	DM_MISSING,
	DM_SKEW,
	DM_OK// ����
};

struct DMResult {
	cv::Rect rect; // ��ά��λ����Ϣ
	DM_DEFECT_TYPE type = DM_DEFECT_TYPE::DM_OK; // ��������
};

class DMSkewMissBlurDetector {
public:
	void loadConfig(std::string configPath);
	void detect(cv::Mat &himage, DMResult &result);
private:
	int line_length = 85; // DM���������
	int support_decode = 0; // �Ƿ��Խ���, 0 ������
	float aspect_rate = 0.75; // ���ݱ�
	double min_area = 5000; // ��С���
	float threshod_angle = 5.0;
};