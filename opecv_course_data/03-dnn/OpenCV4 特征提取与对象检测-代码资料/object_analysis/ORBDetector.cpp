#include "ORBDetector.h"

ORBDetector::ORBDetector() {
	std::cout << "create orb detector..." << std::endl;
}

ORBDetector::~ORBDetector() {
	this->tpl_descriptors.release();
	this->tpl_kps.clear();
	this->orb.release();
	this->tpl.release();
	std::cout << "destory instance..." << std::endl;
}

void ORBDetector::initORB(cv::Mat &refImg) {
	if (!refImg.empty()) {
		cv::Mat tplGray;
		cv::cvtColor(refImg, tplGray, cv::COLOR_BGR2GRAY);
		orb->detectAndCompute(tplGray, cv::Mat(), this->tpl_kps, this->tpl_descriptors);
		tplGray.copyTo(this->tpl);
	}
}

bool ORBDetector::detect_and_analysis(cv::Mat &image, cv::Mat &aligned) {
	// keypoints and match threshold
	float GOOD_MATCH_PERCENT = 0.15f;
	bool found = true;
	// 处理数据集中每一张数据
	cv::Mat img2Gray;
	cv::cvtColor(image, img2Gray, cv::COLOR_BGR2GRAY);
	std::vector<cv::KeyPoint> img_kps;
	cv::Mat img_descriptors;
	orb->detectAndCompute(img2Gray, cv::Mat(), img_kps, img_descriptors);

	std::vector<cv::DMatch> matches;
	cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");
	// auto flann_matcher = cv::FlannBasedMatcher(new cv::flann::LshIndexParams(6, 12, 2));
	matcher->match(img_descriptors, this->tpl_descriptors, matches, cv::Mat());

	// Sort matches by score
	std::sort(matches.begin(), matches.end());

	// Remove not so good matches
	const int numGoodMatches = matches.size() * GOOD_MATCH_PERCENT;
	matches.erase(matches.begin() + numGoodMatches, matches.end());
	// std::cout << numGoodMatches <<"distance:"<<matches [0].distance<< std::endl;
	if (matches[0].distance > 30) {
		found = false;
	}
	// Extract location of good matches
	std::vector<cv::Point2f> points1, points2;
	for (size_t i = 0; i < matches.size(); i++)
	{
		points1.push_back(img_kps[matches[i].queryIdx].pt);
		points2.push_back(tpl_kps[matches[i].trainIdx].pt);
	}

	cv::Mat H = findHomography(points1, points2, cv::RANSAC);
	cv::Mat im2Reg;
	warpPerspective(image, im2Reg, H, tpl.size());

	// 逆时针旋转90度
	cv::Mat result;
	cv::rotate(im2Reg, result, cv::ROTATE_90_COUNTERCLOCKWISE);
	result.copyTo(aligned);
	return found;
}