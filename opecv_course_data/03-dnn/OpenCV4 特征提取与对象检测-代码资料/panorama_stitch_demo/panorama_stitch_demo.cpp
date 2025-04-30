#include <opencv2/opencv.hpp>
#include <iostream>
#define RATIO    0.8
using namespace std;
using namespace cv;

void linspace(Mat& image, float begin, float finish, int number, Mat &mask);
void generate_mask(Mat &img, Mat &mask);
int main(int argc, char** argv) {
	Mat left = imread("D:/images/q11.jpg");
	Mat right = imread("D:/images/q22.jpg");
	if (left.empty() || right.empty()) {
		printf("could not load image...\n");
		return -1;
	}

	// 提取特征点与描述子
	vector<KeyPoint> keypoints_right, keypoints_left;
	Mat descriptors_right, descriptors_left;
	auto detector = AKAZE::create();
	detector->detectAndCompute(left, Mat(), keypoints_left, descriptors_left);
	detector->detectAndCompute(right, Mat(), keypoints_right, descriptors_right);

	// 暴力匹配
	vector<DMatch> matches;
	auto matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);

	// 发现匹配
	std::vector< std::vector<DMatch> > knn_matches;
	matcher->knnMatch(descriptors_left, descriptors_right, knn_matches, 2);
	const float ratio_thresh = 0.7f;
	std::vector<DMatch> good_matches;
	for (size_t i = 0; i < knn_matches.size(); i++)
	{
		if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
		{
			good_matches.push_back(knn_matches[i][0]);
		}
	}
	printf("total good match points : %d\n", good_matches.size());
	std::cout << std::endl;

	Mat dst;
	drawMatches(left, keypoints_left, right, keypoints_right, good_matches, dst);
	imshow("output", dst);
	imwrite("D:/good_matches.png", dst);

	//-- Localize the object
	std::vector<Point2f> left_pts;
	std::vector<Point2f> right_pts;
	for (size_t i = 0; i < good_matches.size(); i++)
	{
		// 收集所有好的匹配点
		left_pts.push_back(keypoints_left[good_matches[i].queryIdx].pt);
		right_pts.push_back(keypoints_right[good_matches[i].trainIdx].pt);
	}

	// 配准与对齐，对齐到第一张
	Mat H = findHomography(right_pts, left_pts, RANSAC);

	// 获取全景图大小
	int h = max(left.rows, right.rows);
	int w = left.cols + right.cols;
	Mat panorama_01 = Mat::zeros(Size(w, h), CV_8UC3);
	Rect roi;
	roi.x = 0;
	roi.y = 0;
	roi.width = left.cols;
	roi.height = left.rows;

	// 获取左侧与右侧对齐图像
	left.copyTo(panorama_01(roi));
	imwrite("D:/panorama_01.png", panorama_01);
	Mat panorama_02;
	warpPerspective(right, panorama_02, H, Size(w, h));
	imwrite("D:/panorama_02.png", panorama_02);

	// 计算融合重叠区域mask
	Mat mask = Mat::zeros(Size(w, h), CV_8UC1);
	generate_mask(panorama_02, mask);

	// 创建遮罩层并根据mask完成权重初始化
	Mat mask1 = Mat::ones(Size(w, h), CV_32FC1);
	Mat mask2 = Mat::ones(Size(w, h), CV_32FC1);

	// left mask
	linspace(mask1, 1, 0, left.cols, mask);

	// right mask
	linspace(mask2, 0, 1, left.cols, mask);
	imshow("mask1", mask1);
	imshow("mask2", mask2);

	// 左侧融合
	Mat m1;
	vector<Mat> mv;
	mv.push_back(mask1);
	mv.push_back(mask1);
	mv.push_back(mask1);
	merge(mv, m1);
	panorama_01.convertTo(panorama_01, CV_32F);
	multiply(panorama_01, m1, panorama_01);

	// 右侧融合
	mv.clear();
	mv.push_back(mask2);
	mv.push_back(mask2);
	mv.push_back(mask2);
	Mat m2;
	merge(mv, m2);
	panorama_02.convertTo(panorama_02, CV_32F);
	multiply(panorama_02, m2, panorama_02);

	// 合并全景图
	Mat panorama;
	add(panorama_01, panorama_02, panorama);
	panorama.convertTo(panorama, CV_8U);
	imwrite("D:/panorama.png", panorama);
	waitKey(0);
	return 0;
}

void generate_mask(Mat &img, Mat &mask) {
	int w = img.cols;
	int h = img.rows;
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			Vec3b p = img.at<Vec3b>(row, col);
			int b = p[0];
			int g = p[1];
			int r = p[2];
			if (b == g && g == r && r == 0) {
				mask.at<uchar>(row, col) = 255;
			}
		}
	}
	imwrite("D:/mask.png", mask);
}

void linspace(Mat& image, float begin, float finish, int w1, Mat &mask) {
	int offsetx = 0;
	float interval = 0;
	float delta = 0;
	for (int i = 0; i < image.rows; i++) {
		offsetx = 0;
		interval = 0;
		delta = 0;
		for (int j = 0; j < image.cols; j++) {
			int pv = mask.at<uchar>(i, j);
			if (pv == 0 && offsetx == 0) {
				offsetx = j;
				delta = w1 - offsetx;
				interval = (finish - begin) / (delta - 1);
				image.at<float>(i, j) = begin + (j - offsetx)*interval;
			}
			else if (pv == 0 && offsetx > 0 && (j - offsetx) < delta) {
				image.at<float>(i, j) = begin + (j - offsetx)*interval;
			}
		}
	}
}