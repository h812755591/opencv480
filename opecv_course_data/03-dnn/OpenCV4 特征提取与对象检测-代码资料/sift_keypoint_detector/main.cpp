#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	// Mat image = imread("D:/images/butterfly.jpg");
	Mat image = imread("D:/images/home.jpg");
	imshow("input", image);
	auto sift = SIFT::create(500);
	vector<KeyPoint> kypts;
	sift->detect(image, kypts);
	Mat result;
	drawKeypoints(image, kypts, result, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	std::cout << kypts.size() << std::endl;
	for (int i = 0; i < kypts.size(); i++) {
		std::cout <<"pt:" <<kypts[i].pt <<" angle:"<< kypts[i].angle << "size: " <<kypts[i].size << std::endl;
	}
	Mat desc_orb;
	sift->compute(image, kypts, desc_orb);
	std::cout << desc_orb.rows << " x " << desc_orb.cols << std::endl;

	imshow("SIFT¹Ø¼üµã¼ì²â", result);
	waitKey(0);
	return 0;
}