#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat ref_img = imread("D:/images/form.png");
	Mat img = imread("D:/images/form_in_doc.jpg");
	imshow("±íµ¥Ä£°å", ref_img);
	auto orb = ORB::create(500);
	vector<KeyPoint> kypts_ref;
	vector<KeyPoint> kypts_img;
	Mat desc_book, desc_book_on_desk;
	orb->detectAndCompute(ref_img, Mat(), kypts_ref, desc_book);
	orb->detectAndCompute(img, Mat(), kypts_img, desc_book_on_desk);
	Mat result;
	auto bf_matcher = BFMatcher::create(NORM_HAMMING, false);
	vector<DMatch> matches;
	bf_matcher->match(desc_book_on_desk, desc_book, matches);
	float good_rate = 0.15f;
	int num_good_matches = matches.size() * good_rate;
	std::cout << num_good_matches << std::endl;
	std::sort(matches.begin(), matches.end());
	matches.erase(matches.begin() + num_good_matches, matches.end());
	drawMatches(ref_img, kypts_ref, img, kypts_img, matches, result);
	imshow("Æ¥Åä", result);
	imwrite("D:/result_doc.png", result);

	// Extract location of good matches
	std::vector<Point2f> points1, points2;
	for (size_t i = 0; i < matches.size(); i++)
	{
		points1.push_back(kypts_img[matches[i].queryIdx].pt);
		points2.push_back(kypts_ref[matches[i].trainIdx].pt);
	}
	Mat h = findHomography(points1, points2, RANSAC);
	Mat aligned_doc;
	warpPerspective(img, aligned_doc, h, ref_img.size());
	imwrite("D:/aligned_doc.png", aligned_doc);
	waitKey(0);
	destroyAllWindows();
	return 0;
}