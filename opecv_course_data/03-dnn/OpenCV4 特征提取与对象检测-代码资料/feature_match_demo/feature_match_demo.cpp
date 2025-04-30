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
	drawMatches(book, kypts_book, book_on_desk, kypts_book_on_desk, matches, result);

	imshow("±©¡¶∆•≈‰", result);
	waitKey(0);
	return 0;
}