#include <opencv2/opencv.hpp>
#include "omp.h"

using namespace cv;

// ÉýÐò£¬»ùÓÚÃæ»ýÅÅÐò
static bool comparePointByx(cv::Point pt1, cv::Point pt2) {
	return pt1.x <= pt2.x;
}

int main(int argc, char** argv) {
	Mat image = imread("D:/python/intel_advance_opencv/images/arrays.png");
	int64 start = getTickCount();
	Mat gray, binary;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	medianBlur(gray, gray, 3);
	threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(binary, binary, MORPH_OPEN, se);
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(binary, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, cv::Point());
	int max = 0;
	int mIdx = -1;

	for (size_t t = 0; t < contours.size(); t++) {
		double area = cv::contourArea(contours[t]);
		if (area < 500) {
			continue;
		}
		Rect box = boundingRect(contours[t]);
		Point tl_pt = box.tl();
		Point br_pt = box.br();
		int left_h1 = tl_pt.y + 2;
		int left_h2 = br_pt.y - 2;
		int left_cx = tl_pt.x;
		int right_cx = br_pt.x;
		std::vector<cv::Point> left_line_pts;
		std::vector<cv::Point> right_line_pts;
		int left_dx = 0, right_dx = 0;
		omp_set_num_threads(2);
		#pragma omp parallel
		{
#pragma omp  sections
			{
#pragma omp section
				{
					for (int row = left_h1; row < left_h2; row++) {
						for (int col = left_cx - 5; col < (left_cx + 5); col++) {
							int pv = binary.at<uchar>(row, col);
							if (pv > 0) {
								left_line_pts.push_back(Point(col, row));
								break;
							}
						}
					}
					int left_len = left_line_pts.size();
					if (left_len > 0) {
						std::sort(left_line_pts.begin(), left_line_pts.end(), comparePointByx);
						left_dx = std::abs(left_line_pts[left_len - 1].x - left_line_pts[0].x);
					}
				}
#pragma omp section
				{
					for (int row = left_h1; row < left_h2; row++) {
						for (int col = right_cx + 5; col > (right_cx - 5); col--) {
							int pv = binary.at<uchar>(row, col);
							if (pv > 0) {
								right_line_pts.push_back(Point(col, row));
								break;
							}
						}
					}
					int right_len = right_line_pts.size();
					if (right_len > 0) {
						std::sort(right_line_pts.begin(), right_line_pts.end(), comparePointByx);
						right_dx = std::abs(right_line_pts[right_len - 1].x - right_line_pts[0].x);
					}
				}
			}
		}
		/*std::vector<cv::Point> left_line_pts;
		for (int row = left_h1; row < left_h2; row++) {
			for (int col = left_cx - 5; col < (left_cx + 5); col++) {
				int pv = binary.at<uchar>(row, col);
				if (pv > 0) {
					left_line_pts.push_back(Point(col, row));
					break;
				}
			}
		}*/
		//std::vector<cv::Point> right_line_pts;
		//for (int row = left_h1; row < left_h2; row++) {
		//	for (int col = right_cx + 5; col > (right_cx - 5); col--) {
		//		int pv = binary.at<uchar>(row, col);
		//		if (pv > 0) {
		//			right_line_pts.push_back(Point(col, row));
		//			break;
		//		}
		//	}
		//}
		//int left_len = left_line_pts.size();
		//int right_len = right_line_pts.size();
		//int left_dx = 0, right_dx = 0;
		/*if (left_len > 0) {
			std::sort(left_line_pts.begin(), left_line_pts.end(), comparePointByx);
			left_dx = std::abs(left_line_pts[left_len - 1].x - left_line_pts[0].x);
		}
		if (right_len > 0) {
			std::sort(right_line_pts.begin(), right_line_pts.end(), comparePointByx);
			right_dx = std::abs(right_line_pts[right_len - 1].x - right_line_pts[0].x);
		}*/
		// std::cout << "left pixel shift: " << left_dx << " right pixel shift: " << right_dx << std::endl;
		if (left_dx > 2 || right_dx > 2) {
			drawContours(image, contours, t, Scalar(0, 0, 255), 2, 8);
		}
	}
	double ct = (getTickCount() - start) / getTickFrequency();
	putText(image, cv::format("execute time : %.5f ms", ct * 1000), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 2, 8);
	imshow("ÕóÁÐÍ¼ÏñÈ±ÏÝ¼ì²â", image);
	cv::waitKey(0);
	cv::destroyAllWindows();
	imwrite("D:/result.png", image);
}