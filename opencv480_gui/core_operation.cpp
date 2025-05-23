#include <string>
#include <iostream>
#include "opencv_head.h"
#include "core_operation.h"
using std::string;
using std::cout;
using std::endl;

namespace {
	string base_path("J:/vs2017ws/data/");

}
void basic_operation::demo01_access_modify(void)
{
	Mat img = Mat::zeros(cv::Size(640, 320), CV_8UC3);
	string win_name = "black";
	int windows_style = cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO;
	namedWindow(win_name, windows_style);
	//  CV_8UC3 每个通道对应的是3个uchar
	cv::Vec3b pixel=img.at<cv::Vec3b>(100, 200);
	cout << pixel <<" " << (unsigned )pixel[0]<<endl;
	img.at<cv::Vec3b>(100, 200) = cv::Vec3b(255, 0, 0);
	// 设置一个整个区域
	// img.setTo(cv::Scalar(0, 255, 0));
	cv::Rect roi=cv::Rect(50, 50, 100, 50);
	cv::Mat roiImage = img(roi);
	roiImage.setTo(cv::Scalar(0, 255, 0));
	imshow(win_name, img);
	cv::waitKey(0);
	cv::destroyAllWindows();

}

void basic_operation::demo02_split_merge(void)
{
	Mat img=imread(base_path+"doc_data/"+"home.jpg",cv::IMREAD_COLOR);
	if (img.empty())
	{
		cout << " load error";
		return;
	}
	std::vector<cv::Mat> channels; // B G R
	
	cv::split(img, channels);
	cv::Mat b = channels[0];  // 蓝色通道
	cv::Mat g = channels[1];  // 绿色通道
	cv::Mat r = channels[2];  // 红色通道
	cv::Mat merged_img;
	cv::merge(channels, merged_img);
	imshow("asasd", merged_img);
	cv::waitKey(0);
	cv::destroyAllWindows();

}

void basic_operation::demo03_boarder(void)
{
	Mat img = imread(base_path + "doc_data/" + "opencv-logo.png");
	if (img.empty())
	{
		cout << " load error";
		return;
	}
	Mat replicate;
	// aaaaaa|abcdefgh|hhhhhhh 复制最后一个像素
	imshow("replicate", img);
	cv::copyMakeBorder(img, replicate, 10, 10, 10, 10, cv::BORDER_REPLICATE);
	imshow("replicate", replicate);
	
	// fedcba | abcdefgh | hgfedcb
	Mat reflect;
	cv::copyMakeBorder(img, reflect, 10, 10, 10, 10, cv::BORDER_REFLECT);
	imshow("reflect", reflect);
	Mat reflect101;
	// gfedcb|abcdefgh|gfedcba
	cv::copyMakeBorder(img, reflect101, 10, 10, 10, 10, cv::BORDER_REFLECT101);
	//  cdefgh|abcdefgh|abcdefg
	Mat wrap;
	cv::copyMakeBorder(img, wrap, 10, 10, 10, 10, cv::BORDER_WRAP);
	Mat constant;
	const Scalar BLUE(255, 0, 0);
	cv::copyMakeBorder(img, constant, 10, 10, 10, 10, cv::BORDER_CONSTANT, BLUE);
	imshow("constant", constant);
	imshow("asasd", img);
	cv::waitKey(0);
	cv::destroyAllWindows();
	// res = cv.warpAffine(img, M, (cols, rows), borderMode=cv.BORDER_ISOLATED)
	// 

}

void arithmetic_operation::demo01_add(void)
{
	Mat img = imread(base_path  +"doc_data/"+ "dog.jpeg");
	if (img.empty())
	{
		cout << " load error";
		return;
	}
	// 创建logo
	Mat logo = Mat::zeros(200,200,CV_8UC3);
	Mat mask = Mat::zeros(200, 200, CV_8UC1);
	// 获取区域 进行常量填充
	logo(cv::Range(20, 120), cv::Range(20, 120)) = cv::Vec3b(0, 0, 255);
	logo(cv::Range(80, 180), cv::Range(80, 180)) = cv::Vec3b(0, 255, 0);
	//
	mask(cv::Range(20, 120), cv::Range(20, 120)) = 255;
	mask(cv::Range(80, 180), cv::Range(80, 180)) = 255;
	imshow("mask",mask);
	// 对mask按位求反
	cv::Mat m;
	cv::bitwise_not(mask, m);
	imshow("mnot", m);
	//
	cv::Mat roi = img(cv::Rect(0, 0, 200, 200));
	//
	cv::Mat tmp;
	// 掩膜中的元素可以是任意值，但 OpenCV 仅根据“是否为零”判断有效性。
	// 但是一般情况下  ​0（无效）和 255（有效）​​ 的二值掩膜
	// cv::bitwise_and(roi, roi, tmp, m); 非0值为有效区域，保留，0值置零
	cv::bitwise_and(roi, roi, tmp, m);// 指定mask
	//​方式2​：掩膜非零区域写入 roi 值，掩膜零区域 ​保留tmp原值​ 必须tmp 全零才和上面等价
	//roi.copyTo(tmp,m);
	//
	// 合成图像
	cv::Mat dst;
	// 一般情况下 我们用add 不用+
	cv::add(tmp, logo, dst);
	imshow("dst", dst);
	imshow("tmp", tmp);
	imshow("img", img);
	imshow("logo", logo);
	dst.copyTo(img(cv::Rect(0, 0, 200, 200)));
	cv::imshow("dog", img);

	cv::waitKey(0);
	cv::destroyAllWindows();

}
/*
案例分析 目的是将roi区域填充成不同颜色 这个区域是不规则多边形两个正方形重叠
1,首先获取roi 区域
2,roi 区域 使用mask 进行挖洞 这个洞是两个正方向重叠区域
cv::bitwise_and(roi, roi, tmp, m);挖洞的范围是mask
3,然后roi 区域再用logo 填充 ，具体方法是add
4,然后再将roi区域拷贝到原图

*/
void arithmetic_operation::demo02_add_weight(void)
{
	string mid_path("doc_data/");
	Mat ml = imread(base_path + mid_path + "ml.png");
	Mat logo = imread(base_path + mid_path + "opencv-logo.png");
	cv::imshow("ml", ml);
	cv::imshow("logo", logo);
	if (ml.empty() || logo.empty())
	{
		cout << " load error";
		return;
	}
	// addWeighted() 函数要求两个输入图像必须具有相同的尺寸和通道数
	cout << ml.size() << endl;
	cout << logo.size() << endl;
	cv::resize(logo, logo, ml.size());  // 将 logo 调整为和 ml 一样大
	cout << logo.size() << endl;
	
	cv::imshow("logo1", logo);
	Mat dst;
	cv::addWeighted(ml, 0.7, logo, 0.3, 0, dst);
	cv::namedWindow("dog", cv::WINDOW_NORMAL);  // 允许手动调整窗口
	cv::resizeWindow("dog", 800, 800);          // 设置较大的显示尺寸
	cv::imshow("dog", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void arithmetic_operation::demo03_add_weight(void)
{
	string mid_path("doc_data/lilao/");
	Mat m1 = imread(base_path + mid_path + "back.jpeg");
	Mat m2 = imread(base_path + mid_path + "smallcat1.jpeg");
	cv::imshow("ml", m1);
	cv::imshow("logo", m2);
	if (m1.empty() || m2.empty())
	{
		cout << " load error";
		return;
	}
	cout << m1.size() << endl;
	cout << m2.size() << endl;
	Mat dst;
	cv::addWeighted(m1, 0.3, m2, 0.7,0, dst);
	cv::imshow("dst", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void arithmetic_operation::demo05_Bitwise_Operations(void)
{
	string mid_path = "doc_data/";
	Mat m1 = imread(base_path + mid_path + "messi5.jpg");                // 主图像
	Mat m2 = imread(base_path + mid_path + "opencv-logo-white.png");     // 白底 logo 图

	if (m1.empty() || m2.empty()) {
		cout << "load error" << endl;
		return;
	}

	// 获取 ROI（主图中贴图的位置，左上角）
	Mat roi = m1(cv::Rect(0, 0, m2.cols, m2.rows));

	// Step 1: 将 logo 转灰度，用于生成掩模
	Mat m2_gray;
	cvtColor(m2, m2_gray, cv::COLOR_BGR2GRAY);

	// Step 2: 创建正向掩模（保留 logo 图案，忽略白色背景）
	Mat mask;
	threshold(m2_gray, mask, 100, 255, cv::THRESH_BINARY);  // logo 图案区域为 255
	Mat mask_inv;
	bitwise_not(mask, mask_inv);                      // 背景区域为 255，用于“挖洞”

	// Step 3: 用 mask_inv 在主图 roi 中“挖出洞”
	Mat roi_bg;
	bitwise_and(roi, roi, roi_bg, mask_inv);          // 清除背景区域

	// Step 4: 用 mask 取出 logo 的有效图案
	Mat logo_fg;
	bitwise_and(m2, m2, logo_fg, mask);

	// Step 5: 将 logo 图案与 roi 背景加权融合（实现透明叠加）
	Mat blended;
	double alpha = 0.2;
	addWeighted(roi_bg, 1.0 - alpha, logo_fg, alpha, 0.0, blended);

	// Step 6: 把融合结果贴回主图
	blended.copyTo(m1(cv::Rect(0, 0, blended.cols, blended.rows)));

	// Step 7: 显示结果
	imshow("Blended Result", m1);
	imshow("mask", mask);
	cv::waitKey(0);
	cv::destroyAllWindows();

	/*
	1,二值化 获取mask
	2,去掉roi区域背景用于填充
	4,提取logo增加背景并进行融合
	5,填充
	6,优化
	GaussianBlur(logo_fg, logo_fg, Size(3, 3), 0); 对 logo 做轻度模糊柔化边缘
	方式一：用 distance transform 对 mask 做渐变

	方式二：手动生成 alpha mask（中心透明度高、边缘低） 生成透明渐变掩模（羽化效果）
	Mat mask_f;
	mask.convertTo(mask_f, CV_32F, 1.0 / 255); // 归一化掩模
	cv::GaussianBlur(mask_f, mask_f, Size(31, 31), 15);  // feather
	然后改用 cv::multiply() 做 alpha blend 而不是 addWeighted()。


	*/
}
