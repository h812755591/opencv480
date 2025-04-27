#include <vector>

#include "corner_dect.h"
#include "util.h"
using std::string;
using cv::Mat;
using std::vector;
using cv::Point2f;
using cv::Point;
using cv::Scalar;
//
using std::cout;
using std::endl;
void yolov5pro::CornerDect::demo01_tomasi(void)
{
	//步骤1 读取彩色图BGR
	const string path = "J:/vs2017ws/data/morph3.png";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//步骤2 获取灰度图
	Mat gray;
	cv::cvtColor(image,gray,cv::COLOR_BGR2GRAY);//dscn由code自动推导
	string gray_win_name = "gray窗口";
	cv::namedWindow(gray_win_name, windows_style);
	imshow(gray_win_name, gray);
	//步骤3 获取角点
	vector<Point2f> corners;
	int max_corners = 200;
	double mindistance = 10;
	cv::goodFeaturesToTrack(gray,corners, max_corners,0.999999, mindistance
		);//输入必须是单通道 可以是8u 也可以是32F 没有角点 corners.size()为0
	//可选的亚像素优化
	unsigned int   nums = (unsigned int)corners.size();
	cout << "个数为=" << nums << endl;
	if (0!=nums)
	{
		cv::TermCriteria criteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.01);
		cv::cornerSubPix(gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);
	}
	

	
	for (unsigned int i=0;i< nums;i++)
	{
		Point2f corner=corners[i];
		//这个函数输入是Point 需要转
		//cv::Point corner_int = static_cast<cv::Point>(corners[i]);//截断
		cv::Point corner_int(cvRound(corner.x), cvRound(corner.y));
		cv::circle(image, corner, 3, Scalar(0, 0, 255), 1);
	}
	string corner_win_name = "corner窗口";
	cv::namedWindow(corner_win_name, windows_style);
	imshow(corner_win_name, image);
	cv::waitKey(0);
	cv::destroyAllWindows();


}

void yolov5pro::CornerDect::demo02_ORB(void)
{
	//步骤1 读取彩色图BGR
	const string path = "J:/vs2017ws/data/blox.jpg";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//步骤2 关键点检测
	cv::Ptr<cv::ORB>  ptr = cv::ORB::create(500);
	vector<cv::KeyPoint> kypts;
	ptr->detect(image,kypts);
	Mat result;
	cv::drawKeypoints(image,kypts,result,Scalar::all(-1),cv::DrawMatchesFlags::
		DEFAULT);
	//步骤三 显示
	string kp_win_name = "kp窗口";
	cv::namedWindow(kp_win_name, windows_style);
	imshow(kp_win_name, result);
	//
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void yolov5pro::CornerDect::demo03_SIFT(void)
{
	//步骤1 读取彩色图BGR
	const string path = "J:/vs2017ws/data/blox.jpg";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//
	cv::Mat gray_image;
	cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
	//
	cv::Ptr<cv::SIFT> sift = cv::SIFT::create(0, 3, 0.04, 10, 1.6);
	std::vector<cv::KeyPoint> keypoints;
	std::vector<cv::KeyPoint> kp_gray;
	sift->detect(image, keypoints);
	sift->detect(gray_image, kp_gray);    // 传入灰度图
	// 在图像上绘制关键点
	cv::Mat img_with_keypoints;
	cv::Mat img_with_keypoints1;
	Mat image_clone = image.clone();
	cv::drawKeypoints(image, keypoints, img_with_keypoints, 
		cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
	cv::drawKeypoints(image_clone, kp_gray, img_with_keypoints1,
		cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
	//步骤三 显示
	string kp_win_name = "kp窗口";
	cv::namedWindow(kp_win_name, windows_style);
	imshow(kp_win_name, img_with_keypoints);
	//
	string kp1_win_name = "kp1窗口";
	cv::namedWindow(kp1_win_name, windows_style);
	imshow(kp1_win_name, img_with_keypoints1);
	//
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void yolov5pro::CornerDect::demo04_ORB_desc(void)
{

}

void yolov5pro::CornerDect::demo05_findHomography(void)
{
	//1.读取彩色图
	const string path = "J:/vs2017ws/data/mytest.jpg";
	Mat image = util::read_img(path);
	string in_win_name = "输入窗口";
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);
	imshow(in_win_name, image);
	//2，转灰度图
	Mat gray;
	cv::cvtColor(image,gray,cv::COLOR_BGR2GRAY);
	string gray_win_name = "gray窗口";
	cv::namedWindow(gray_win_name, windows_style);
	imshow(gray_win_name, gray);
	//3，灰度图转化为二值图
	Mat binary;
	cv::threshold(gray, binary,0,255,
		cv::THRESH_BINARY|cv::THRESH_OTSU);
	string binary_win_name = "binary窗口";
	cv::namedWindow(binary_win_name, windows_style);
	imshow(binary_win_name, binary);
	//4，可以执行开运算，把字去掉 这里略
	//5，寻找轮廓vector<std::vector<cv::Point>> contours
	vector<vector<Point>> contours;//因为cv::RETR_EXTERNAL 没有层级，所以hierarchy不需要
	cv::findContours(binary, contours,cv::RETR_EXTERNAL,
		cv::CHAIN_APPROX_SIMPLE);//src 必须为二值图 8u1 
	//6,画轮廓
	unsigned int nums =(unsigned int) contours.size();
	int index = -1;
	double max = -1;//最大面积
	for (unsigned int i = 0ULL; i < nums; i++)
	{
		double area = contourArea(contours[i]);
		if (area > max)
		{
			max = area;
			index = i;
		}
		
	}
	/*drawContours(image, contours, index, Scalar(0, 255, 0), 2, 8);
	string contour_win_name = "contour窗口";
	cv::namedWindow(contour_win_name, windows_style);
	imshow(contour_win_name, image);*/
	//7,用逼近函数逼近成一个多边形
	vector<Point> curve = contours[index];
	vector<Point> approxCurve;
	cv::approxPolyDP(curve, approxCurve, 100, true);
	vector<Point2f> srcPts;
	for (size_t i = 0; i < approxCurve.size(); i++) {
		Point  pt = approxCurve[i];
		srcPts.push_back(Point2f(static_cast<float>(pt.x), 
			static_cast<float>(pt.y)));
		//cv::circle(image, pt,4,Scalar(0,0,255),1);
		cout << "x=" << pt.x << " y=" << pt.y << endl;
	}
	/*string circle_win_name = "circle窗口";
	cv::namedWindow(circle_win_name, windows_style);
	imshow(circle_win_name, image);*/
	//8，生成目的
	vector<Point2f> dstPts;
	dstPts.push_back(Point2f(0, 0));
	dstPts.push_back(Point2f(0, 800));
	dstPts.push_back(Point2f(600, 800));
	dstPts.push_back(Point2f(600, 0));
	//9，srcPts dstPts 必须是vector<Point2f> 获得变换矩阵
	Mat h = findHomography(srcPts, dstPts, cv::RANSAC);
	Mat dst;
	warpPerspective(image, dst, h, cv::Size(600, 800));
	string pers_win_name = "Pers窗口";
	cv::namedWindow(pers_win_name, windows_style);
	imshow(pers_win_name, dst);
	//释放资源
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void yolov5pro::CornerDect::demo06_findHomography(void)
{
	const string book_path = "J:/vs2017ws/data/book.jpg";
	const string book_on_desk_path = "J:/vs2017ws/data/book_on_desk.jpg";
	Mat book = util::read_img(book_path);
	Mat book_on_desk = util::read_img(book_on_desk_path);
	string in_win_name = "输入窗口";
	/*int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO;
	cv::namedWindow(in_win_name, windows_style);*/
	//imshow("book", book);
	//imshow("book_on_desk", book_on_desk);
	//1,创建检测算法
	cv::Ptr<cv::ORB> orb=cv::ORB::create(500);
	vector<cv::KeyPoint> kypts_book;
	vector<cv::KeyPoint> kypts_book_on_desk;
	Mat desc_book, desc_book_on_desk;
	orb->detectAndCompute(book, Mat(), kypts_book, desc_book);
	orb->detectAndCompute(book_on_desk, Mat(), kypts_book_on_desk, desc_book_on_desk);
	//2,
	Mat result;
	auto bf_matcher = cv::BFMatcher::create(cv::NORM_HAMMING, false);
	vector<cv::DMatch> matches;
	bf_matcher->match(desc_book, desc_book_on_desk, matches);
	//3,
	float good_rate = 0.15f;
	int num_good_matches = matches.size() * good_rate;
	std::cout << num_good_matches << std::endl;
	std::sort(matches.begin(), matches.end());
	matches.erase(matches.begin() + num_good_matches, matches.end());
	drawMatches(book, kypts_book, book_on_desk, kypts_book_on_desk, matches, result);
	vector<Point2f> obj_pts;
	vector<Point2f> scene_pts;
	//
	for (size_t t = 0; t < matches.size(); t++) {
		obj_pts.push_back(kypts_book[matches[t].queryIdx].pt);
		scene_pts.push_back(kypts_book_on_desk[matches[t].trainIdx].pt);
	}
	Mat h = findHomography(obj_pts, scene_pts, cv::RANSAC);
	vector<Point2f> srcPts;
	srcPts.push_back(Point2f(0, 0));
	srcPts.push_back(Point2f(book.cols, 0));
	srcPts.push_back(Point2f(book.cols, book.rows));
	srcPts.push_back(Point2f(0, book.rows));
	//
	std::vector<Point2f> dstPts(4);
	perspectiveTransform(srcPts, dstPts, h);

	for (int i = 0; i < 4; i++) {
		line(book_on_desk, dstPts[i], dstPts[(i + 1) % 4], Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("暴力匹配", result);
	namedWindow("对象检测", cv::WINDOW_FREERATIO);
	imshow("对象检测", book_on_desk);
	//释放资源
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void yolov5pro::CornerDect::demo07_findHomography(void)
{
	Mat ref_img = cv::imread("J:/vs2017ws/data/form.png");
	Mat img = cv::imread("J:/vs2017ws/data/form_in_doc.jpg");
	imshow("表单模板", ref_img);
	auto orb = cv::ORB::create(500);
	vector<cv::KeyPoint> kypts_ref;
	vector<cv::KeyPoint> kypts_img;
	Mat desc_book, desc_book_on_desk;
	orb->detectAndCompute(ref_img, Mat(), kypts_ref, desc_book);
	orb->detectAndCompute(img, Mat(), kypts_img, desc_book_on_desk);
	Mat result;
	auto bf_matcher = cv::BFMatcher::create(cv::NORM_HAMMING, false);
	vector<cv::DMatch> matches;
	bf_matcher->match(desc_book_on_desk, desc_book, matches);
	float good_rate = 0.15f;
	int num_good_matches = matches.size() * good_rate;
	std::cout << num_good_matches << std::endl;
	std::sort(matches.begin(), matches.end());
	matches.erase(matches.begin() + num_good_matches, matches.end());
	cv::drawMatches(ref_img, kypts_ref, img, kypts_img, matches, result);
	imshow("匹配", result);
	imwrite("J:/vs2017ws/data/result_doc.png", result);

	// Extract location of good matches
	std::vector<Point2f> points1, points2;
	for (size_t i = 0; i < matches.size(); i++)
	{
		points1.push_back(kypts_img[matches[i].queryIdx].pt);
		points2.push_back(kypts_ref[matches[i].trainIdx].pt);
	}
	Mat h = findHomography(points1, points2, cv::RANSAC);
	Mat aligned_doc;
	warpPerspective(img, aligned_doc, h, ref_img.size());
	imwrite("J:/vs2017ws/data/aligned_doc.png", aligned_doc);
	//释放资源
	cv::waitKey(0);
	cv::destroyAllWindows();
}
namespace
{
	void generate_mask(Mat &img, Mat &mask) {
		int w = img.cols;
		int h = img.rows;
		for (int row = 0; row < h; row++) {
			for (int col = 0; col < w; col++) {
				cv::Vec3b p = img.at<cv::Vec3b>(row, col);
				int b = p[0];
				int g = p[1];
				int r = p[2];
				if (b == g && g == r && r == 0) {
					mask.at<uchar>(row, col) = 255;
				}
			}
		}
		imwrite("J:/vs2017ws/data/mask.png", mask);
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

}
void yolov5pro::CornerDect::demo08_findHomography(void)
{
	Mat left = cv::imread("J:/vs2017ws/data/11.jpg");
	Mat right = cv::imread("J:/vs2017ws/data/22.jpg");
	if (left.empty() || right.empty()) {
		printf("could not load image...\n");
		return;
	}

	// 提取特征点与描述子
	vector<cv::KeyPoint> keypoints_right, keypoints_left;
	Mat descriptors_right, descriptors_left;
	auto detector = cv::AKAZE::create();
	detector->detectAndCompute(left, Mat(), keypoints_left, descriptors_left);
	detector->detectAndCompute(right, Mat(), keypoints_right, descriptors_right);

	// 暴力匹配
	vector<cv::DMatch> matches;
	auto matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::BRUTEFORCE);

	// 发现匹配
	std::vector< std::vector<cv::DMatch> > knn_matches;
	matcher->knnMatch(descriptors_left, descriptors_right, knn_matches, 2);
	const float ratio_thresh = 0.7f;
	std::vector<cv::DMatch> good_matches;
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
	imwrite("J:/vs2017ws/data/good_matches.png", dst);

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
	Mat H = findHomography(right_pts, left_pts, cv::RANSAC);

	// 获取全景图大小
	int h = cv::max(left.rows, right.rows);
	int w = left.cols + right.cols;
	Mat panorama_01 = Mat::zeros(cv::Size(w, h), CV_8UC3);
	cv::Rect roi;
	roi.x = 0;
	roi.y = 0;
	roi.width = left.cols;
	roi.height = left.rows;

	// 获取左侧与右侧对齐图像
	left.copyTo(panorama_01(roi));
	imwrite("J:/vs2017ws/data/panorama_01.png", panorama_01);
	Mat panorama_02;
	warpPerspective(right, panorama_02, H, cv::Size(w, h));
	imwrite("J:/vs2017ws/data/panorama_02.png", panorama_02);

	// 计算融合重叠区域mask
	Mat mask = Mat::zeros(cv::Size(w, h), CV_8UC1);
	generate_mask(panorama_02, mask);

	// 创建遮罩层并根据mask完成权重初始化
	Mat mask1 = Mat::ones(cv::Size(w, h), CV_32FC1);
	Mat mask2 = Mat::ones(cv::Size(w, h), CV_32FC1);

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
	imwrite("J:/vs2017ws/data/panorama.png", panorama);

}
