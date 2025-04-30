#include "dm_defect.h"

int main(int argc, char** argv) {

	std::shared_ptr<DMSkewMissBlurDetector> detector(new DMSkewMissBlurDetector());
	detector->loadConfig("dm_defect_config.yml");
	std::vector<std::string> dm_images;
	cv::glob("D:/facedb/dm_defect", dm_images);
	DMResult result;
	for (int i = 0; i < dm_images.size(); i++) {
		std::string himage_path = dm_images[i];
		std::cout << "data matrix image path: " << himage_path << std::endl;
		cv::Mat image = cv::imread(himage_path);
		detector->detect(image, result);
		if (result.type == DM_DEFECT_TYPE::DM_MISSING) {
			std::cout << "Data Matrix code missing~~~~" << std::endl;
			cv::putText(image, "Miss NG", cv::Point(10, 30), cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(0, 0, 255), 2, 8);
		}
		if (result.type == DM_DEFECT_TYPE::DM_SKEW) {
			std::cout << "Data Matrix code skew" << std::endl;
			cv::putText(image, "Skew NG", cv::Point(10, 30), cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(0, 0, 255), 2, 8);
		}
		if (result.type == DM_DEFECT_TYPE::DM_OK) {
			std::cout << "good qrcode!!!" << std::endl;
			cv::putText(image, "OK", cv::Point(10, 30), cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(0, 255, 0), 2, 8);
		}
		cv::imshow("DMÈ±ÏÝ¼ì²â", image);
		cv::waitKey(0);
	}
}