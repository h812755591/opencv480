#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "case03.h"
#include "omp.h"
using std::cout;
using std::endl;
using std::string;
using std::vector;
//
using cv::Mat;
using cv::Size;
using cv::Point;
using cv::Scalar;
using cv::RotatedRect;
using cv::Point2f;
namespace
{
	string base_path("J:/vs2017ws/data/");
	Mat transformCorner(Mat &image, RotatedRect &rect);
	bool isYCorner(Mat &image);
	bool isXCorner(Mat &image);
	Mat transformCorner(Mat &image, RotatedRect &rect);
	void scanAndDetectQRCode(Mat & image) {
		//二值化
		Mat gray, binary;
		cvtColor(image, gray, cv::COLOR_BGR2GRAY);
		threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
		imshow("binary", binary);

		// detect rectangle now
		cv::Moments monents;
		vector<vector<Point>> contours;
		findContours(binary.clone(), contours, cv::RETR_LIST,
			cv::CHAIN_APPROX_SIMPLE, Point());
		Mat result = Mat::zeros(image.size(), CV_8UC1);
		for (size_t t = 0; t < contours.size(); t++) {
			double area = contourArea(contours[t]);
			if (area < 100) continue;
			RotatedRect rect = minAreaRect(contours[t]);
			float w = rect.size.width;
			float h = rect.size.height;
			double rate = cv::min(w, h) / cv::max(w, h);
			
			if (rate > 0.85 && w < image.cols / 4 && h < image.rows / 4) {
				Mat qr_roi = transformCorner(image, rect);
				if (isXCorner(qr_roi)) {
					drawContours(image, contours, static_cast<int>(t), Scalar(0, 255, 0),1, 8);
					drawContours(result, contours, static_cast<int>(t), Scalar(255), 1, 8);
				}
			}
			
		}
		//
		vector<Point> pts;
		for (int row = 0; row < result.rows; row++) {
			for (int col = 0; col < result.cols; col++) {
				int pv = result.at<uchar>(row, col);
				if (pv == 255) {
					pts.push_back(Point(col, row));//这里我们可以进行发现轮廓 不需要这一步
				}
			}
		}
		RotatedRect rrt = minAreaRect(pts);
		Point2f vertices[4];
		rrt.points(vertices);
		pts.clear();
		for (int i = 0; i < 4; i++) {
			line(image, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
			pts.push_back(vertices[i]);
		}
		Mat mask = Mat::zeros(result.size(), result.type());
		vector<vector<Point>> cpts;
		cpts.push_back(pts);
		drawContours(mask, cpts, 0, Scalar(255), -1, 8);

		Mat dst;
		bitwise_and(image, image, dst, mask);
		//
		cv::imshow("contour_image",image);
		cv::imshow("result", result);
	}
	bool isXCorner(Mat &image) {
		Mat gray, binary;
		cvtColor(image, gray,cv::COLOR_BGR2GRAY);
		threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
		int xb = 0, yb = 0;
		int w1x = 0, w2x = 0;
		int b1x = 0, b2x = 0;

		int width = binary.cols;
		int height = binary.rows;
		int cy = height / 2;
		int cx = width / 2;
		int pv = binary.at<uchar>(cy, cx);
		if (pv == 255) return false;
		// verfiy finder pattern
		bool findleft = false, findright = false;
		int start = 0, end = 0;
		int offset = 0;
		while (true) {
			offset++;
			if ((cx - offset) <= width / 8 || (cx + offset) >= width - 1) {
				start = -1;
				end = -1;
				break;
			}
			pv = binary.at<uchar>(cy, cx - offset);
			if (pv == 255) {
				start = cx - offset;
				findleft = true;
			}
			pv = binary.at<uchar>(cy, cx + offset);
			if (pv == 255) {
				end = cx + offset;
				findright = true;
			}
			if (findleft && findright) {
				break;
			}
		}

		if (start <= 0 || end <= 0) {
			return false;
		}
		xb = end - start;
		for (int col = start; col > 0; col--) {
			pv = binary.at<uchar>(cy, col);
			if (pv == 0) {
				w1x = start - col;
				break;
			}
		}
		for (int col = end; col < width - 1; col++) {
			pv = binary.at<uchar>(cy, col);
			if (pv == 0) {
				w2x = col - end;
				break;
			}
		}
		for (int col = (end + w2x); col < width; col++) {
			pv = binary.at<uchar>(cy, col);
			if (pv == 255) {
				b2x = col - end - w2x;
				break;
			}
			else {
				b2x++;
			}
		}
		for (int col = (start - w1x); col > 0; col--) {
			pv = binary.at<uchar>(cy, col);
			if (pv == 255) {
				b1x = start - col - w1x;
				break;
			}
			else {
				b1x++;
			}
		}

		float sum = xb + b1x + b2x + w1x + w2x;
		//printf("xb : %d, b1x = %d, b2x = %d, w1x = %d, w2x = %d\n", xb , b1x , b2x , w1x , w2x);
		xb = static_cast<int>((xb / sum)*7.0 + 0.5);
		b1x = static_cast<int>((b1x / sum)*7.0 + 0.5);
		b2x = static_cast<int>((b2x / sum)*7.0 + 0.5);
		w1x = static_cast<int>((w1x / sum)*7.0 + 0.5);
		w2x = static_cast<int>((w2x / sum)*7.0 + 0.5);
		printf("xb : %d, b1x = %d, b2x = %d, w1x = %d, w2x = %d\n", xb, b1x, b2x, w1x, w2x);
		if ((xb == 3 || xb == 4) && b1x == b2x && w1x == w2x && w1x == b1x && b1x == 1) { // 1:1:3:1:1
			return true;
		}
		else {
			return false;
		}
	}
	bool isYCorner(Mat &image) {
		Mat gray, binary;
		cvtColor(image, gray, cv::COLOR_BGR2GRAY);
		threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
		int width = binary.cols;
		int height = binary.rows;
		int cy = height / 2;
		int cx = width / 2;
		int pv = binary.at<uchar>(cy, cx);
		int bc = 0, wc = 0;
		bool found = true;
		for (int row = cy; row > 0; row--) {
			pv = binary.at<uchar>(row, cx);
			if (pv == 0 && found) {
				bc++;
			}
			else if (pv == 255) {
				found = false;
				wc++;
			}
		}
		bc = bc * 2;
		if (bc <= wc) {
			return false;
		}
		return true;
	}
	Mat transformCorner(Mat &image, RotatedRect &rect) {
		int width = static_cast<int>(rect.size.width);
		int height = static_cast<int>(rect.size.height);
		Mat result = Mat::zeros(height, width, image.type());
		//顺时针坐标 四个顶点坐标（左下）→ p[1]（左上）→ p[2]（右上）→ p[3]（右下）
		Point2f vertices[4]; 
		rect.points(vertices);
		vector<Point> src_corners;
		vector<Point> dst_corners;
		dst_corners.push_back(Point(0, 0));// ​左上→右上→右下→左下  有点不对应
		dst_corners.push_back(Point(width, 0));
		dst_corners.push_back(Point(width, height)); // big trick
		dst_corners.push_back(Point(0, height));
		
		src_corners.push_back(vertices[1]);  // 左上
		src_corners.push_back(vertices[2]);  // 右上
		src_corners.push_back(vertices[3]);  // 右下
		src_corners.push_back(vertices[0]);  // 左下
		

		/*for (int i = 0; i < 4; i++) {
			src_corners.push_back(vertices[i]);
		}*/
		
		Mat hm = findHomography(src_corners, dst_corners);
		warpPerspective(image, result, hm, result.size());
		
		return result;
	}

}
void case3::demo01(void)
{
	/*string image_name("qrcode.png");*/
	//string image_name("qrcode_07.png"); 
	//string image_name("qrcode_06.png"); 
	string image_name("qrcode_05.jpg");
	Mat image = cv::imread(base_path+image_name);
	if (image.empty())
	{
		cout << "load error" << endl;
	}
	cv::imshow("input",image);
	//
	scanAndDetectQRCode(image);


	//
	cv::waitKey(0);
	cv::destroyAllWindows();
}
