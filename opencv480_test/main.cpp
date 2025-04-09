#include <opencv2/opencv.hpp>
#include "util.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using cv::Mat;
int main(void)
{
	const string path = "J:/vs2017ws/data/example.png";
	Mat image=read_img(path);
	string in_win_name = "输入窗口";
	cv::namedWindow(in_win_name, cv::WINDOW_NORMAL | cv::WINDOW_FREERATIO);
	imshow(in_win_name,image);
	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}