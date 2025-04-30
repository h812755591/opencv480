#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	// Mat image = imread("D:/images/butterfly.jpg");
	Mat image = imread("D:/images/home.jpg");
	imshow("input", image);
	auto orb = ORB::create(500);
	vector<KeyPoint> kypts;
	orb->detect(image, kypts);
	Mat result;
	drawKeypoints(image, kypts, result, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	Mat desc_orb;
	orb->compute(image, kypts, desc_orb);
	std::cout << desc_orb.rows << " x " << desc_orb.cols << std::endl;
	
	imshow("ORB¹Ø¼üµã¼ì²â", result);
	waitKey(0);
	return 0;
}