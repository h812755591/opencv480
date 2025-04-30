#include "dm_defect.h"
#include <math.h>

#define PI 3.14159265

void DMSkewMissBlurDetector::loadConfig(std::string configPath) {
	// 初始化参数文件
	cv::FileStorage fs(configPath, cv::FileStorage::READ);
	fs["line_length"] >> this->line_length;
	fs["support_decode"] >> this->support_decode;
	fs["aspect_rate"] >> this->aspect_rate;
	fs["min_area"] >> this->min_area;
	fs["threshod_angle"] >> this->threshod_angle;
	fs.release();

	// log输出
	std::cout << "current parameters" << std::endl;
	std::cout << "line_length: " << this->line_length << std::endl;
	std::cout << "support_decode: " << this->support_decode << std::endl;
	std::cout << "aspect_rate: " << this->aspect_rate << std::endl;
	std::cout << "min_area: " << this->min_area << std::endl;
	std::cout << "threshod_angle: " << this->threshod_angle << std::endl;
	std::cout << "load config file done!" << std::endl;
}

void DMSkewMissBlurDetector::detect(cv::Mat &himage, DMResult &result) {
	// 轮廓发现, 寻找最大轮廓
	int64 start = cv::getTickCount();
	result.type = DM_OK;
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::Mat gray, binary;
	cv::cvtColor(himage, gray, cv::COLOR_BGR2GRAY);
	cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
	cv::Mat se = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
	cv::morphologyEx(binary, binary, cv::MORPH_CLOSE, se);
	//cv::imshow("binary", binary);
	cv::findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point());
	int max = 0;
	int mIdx = -1;
	for (size_t t = 0; t < contours.size(); t++) {
		double area = cv::contourArea(contours[t]);
		// std::cout << "area : " << area << std::endl;
		if (area < this->min_area) {
			continue;
		}
		cv::Rect box = cv::boundingRect(contours[t]);
		int m = box.width * box.height;
		if (max < m) {
			max = m;
			mIdx = t;
		}
	}
	if (mIdx < 0) {
		result.type = DM_DEFECT_TYPE::DM_MISSING;
		return;
	}
	// 获取ROI区域
	cv::Rect qrbox = cv::boundingRect(contours[mIdx]);

	// 最小外接轮廓
	cv::RotatedRect rrt = cv::minAreaRect(contours[mIdx]);
	float w = rrt.size.width;
	float h = rrt.size.height;
	cv::Point2f pts[4];
	rrt.points(pts);
	std::cout << "angle: " << rrt.angle << std::endl;
	if (abs(rrt.angle) > 15 && abs(rrt.angle) < 75) {
		result.type = DM_DEFECT_TYPE::DM_SKEW;
		return;
	}
	cv::Point2f cpt = rrt.center;

	// 计算横纵比
	float ratio = std::min(w, h) / std::max(w, h);
	//std::cout << ratio << std::endl;
	if (ratio < this->aspect_rate) {
		result.type = DM_DEFECT_TYPE::DM_MISSING;
		return;
	}

	// 选择两条线段
	std::vector<std::vector<cv::Point>> lines;
	int shift_step = 5;
	// 像素点数阈值，小于85的，判读为缺失！高于85的保存
	// 根据保存的两条边点数拟合计算倾斜角度！一切正常的
	// 判定通过！
	for (int i = 0; i < 4; i++) {
		int dx = std::abs(pts[i % 4].x - pts[(i + 1) % 4].x);
		int dy = std::abs(pts[i % 4].y - pts[(i + 1) % 4].y);
		//std::cout << "dx: " << dx << " dy:" << dy << std::endl;
		std::vector<cv::Point> line_pts;
		// 上下寻找线段
		if (dx > dy) {
			int start_x = pts[i % 4].x;
			int end_x = pts[(i + 1) % 4].x;
			if (pts[i % 4].x > pts[(i + 1) % 4].x) {
				start_x = pts[(i + 1) % 4].x;
				end_x = pts[i % 4].x;
			}
			int loc_y = (pts[i % 4].y + pts[(i + 1) % 4].y) / 2;
			if (loc_y > cpt.y) { // 下部， 从下向上
				bool found = false;
				for (int col = start_x; col < end_x; col++) {
					int max_row = 0;
					found = false;
					for (int row = loc_y + shift_step; row > (loc_y - shift_step); row--) {
						int pv = binary.at<uchar>(row, col);
						if (pv > 0) {
							found = true;
							max_row = row;
							break;
						}
					}
					if (found) {
						line_pts.push_back(cv::Point(col, max_row));
					}
				}
			}
			if (loc_y < cpt.y) { // 上部, 从上向下
				bool found = false;
				for (int col = start_x; col < end_x; col++) {
					int max_row = 0;
					found = false;
					for (int row = loc_y - shift_step; row < (loc_y + shift_step); row++) {
						int pv = binary.at<uchar>(row, col);
						if (pv > 0) {
							found = true;
							max_row = row;
							break;
						}
					}
					if (found) {
						line_pts.push_back(cv::Point(col, max_row));
					}
				}
			}
		}

		// 左右寻找线段
		if (dy > dx) {
			int start_y = pts[i % 4].y;
			int end_y = pts[(i + 1) % 4].y;
			if (pts[i % 4].y > pts[(i + 1) % 4].y) {
				start_y = pts[(i + 1) % 4].y;
				end_y = pts[i % 4].y;
			}
			int loc_x = (pts[i % 4].x + pts[(i + 1) % 4].x) / 2;
			if (loc_x > cpt.x) { // 右边， 从右向左
				bool found = false;
				for (int row = start_y; row < end_y; row++) {
					int max_col = 0;
					found = false;
					for (int col = loc_x + shift_step; col > (loc_x - shift_step); col--) {
						int pv = binary.at<uchar>(row, col);
						if (pv > 0) {
							found = true;
							max_col = col;
							break;
						}
					}
					if (found) {
						line_pts.push_back(cv::Point(max_col, row));
					}
				}
			}
			if (loc_x < cpt.x) { // 上部, 从上向下
				bool found = false;
				for (int row = start_y; row < end_y; row++) {
					int max_col = 0;
					found = false;
					for (int col = loc_x - shift_step; col < (loc_x + shift_step); col++) {
						int pv = binary.at<uchar>(row, col);
						if (pv > 0) {
							found = true;
							max_col = row;
							break;
						}
					}
					if (found) {
						line_pts.push_back(cv::Point(max_col, row));
					}
				}
			}
		}

		// 总的边缘像素点
		std::cout << "number of pixels: " << line_pts.size() << std::endl;
		if (line_pts.size() > this->line_length) {
			lines.push_back(line_pts);
		}
	}

	// missing
	if (lines.size() < 2) {
		result.type = DM_DEFECT_TYPE::DM_MISSING;
		double ct = (cv::getTickCount() - start) / cv::getTickFrequency();
		std::cout << "execute time: " << ct * 1000 << std::endl;
		return; 
	}

	// 计算角度
	std::vector<cv::Point> one_line = lines[0];
	cv::Point pt1 = one_line[shift_step];
	cv::Point pt2 = one_line[this->line_length - shift_step];

	// 反三角计算
	double dx = pt1.x - pt2.x;
	double dy = pt1.y - pt2.y;
	if (dx == 0 || dy == 0) {
		result.type = DM_DEFECT_TYPE::DM_OK;
		return;
	}
	if (dx < 0) {
		dx = pt2.x - pt1.x;
		dy = pt2.y - pt1.y;
	}
	double skew_angle = atan(dy / dx) * 180 / PI;
	// std::cout << "angle: " << skew_angle <<std::endl;
	if (skew_angle < (90.0 - this->threshod_angle) &&
		skew_angle > this->threshod_angle) {
		result.type = DM_DEFECT_TYPE::DM_SKEW;
		return;
	}
	double ct = (cv::getTickCount() - start) / cv::getTickFrequency();
	std::cout << "execute time: " << ct*1000 << std::endl;
}