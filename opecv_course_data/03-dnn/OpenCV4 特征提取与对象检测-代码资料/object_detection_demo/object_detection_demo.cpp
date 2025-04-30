#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	// Mat image = imread("D:/images/butterfly.jpg");
	Mat book = imread("D:/images/book.jpg");
	Mat book_on_desk = imread("D:/images/book_on_desk.jpg");
	imshow("book", book);
	auto orb = ORB::create(500);
	vector<KeyPoint> kypts_book;
	vector<KeyPoint> kypts_book_on_desk;
	Mat desc_book, desc_book_on_desk;
	orb->detectAndCompute(book, Mat(), kypts_book, desc_book);
	orb->detectAndCompute(book_on_desk, Mat(), kypts_book_on_desk, desc_book_on_desk);
	Mat result;
	auto bf_matcher = BFMatcher::create(NORM_HAMMING, false);
	vector<DMatch> matches;
	bf_matcher->match(desc_book, desc_book_on_desk, matches);
	float good_rate = 0.15f;
	int num_good_matches = matches.size() * good_rate;
	std::cout << num_good_matches << std::endl;
	std::sort(matches.begin(), matches.end());
	matches.erase(matches.begin() + num_good_matches, matches.end());
	drawMatches(book, kypts_book, book_on_desk, kypts_book_on_desk, matches, result);
	vector<Point2f> obj_pts;
	vector<Point2f> scene_pts;
	for (size_t t = 0; t < matches.size(); t++) {
		obj_pts.push_back(kypts_book[matches[t].queryIdx].pt);
		scene_pts.push_back(kypts_book_on_desk[matches[t].trainIdx].pt);
	}
	Mat h = findHomography(obj_pts, scene_pts, RANSAC);
	vector<Point2f> srcPts;
	srcPts.push_back(Point2f(0, 0));
	srcPts.push_back(Point2f(book.cols, 0));
	srcPts.push_back(Point2f(book.cols, book.rows));
	srcPts.push_back(Point2f(0, book.rows));

	std::vector<Point2f> dstPts(4);
	perspectiveTransform(srcPts, dstPts, h);

	for (int i = 0; i < 4; i++) {
		line(book_on_desk, dstPts[i], dstPts[(i + 1) % 4], Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("����ƥ��", result);
	namedWindow("������", WINDOW_FREERATIO);
	imshow("������", book_on_desk);
	imwrite("D:/object_find.png", book_on_desk);
	waitKey(0);
	return 0;
}