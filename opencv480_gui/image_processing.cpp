#include <string>
#include <iostream>
#include <time.h>
#include "opencv_head.h"
#include "image_processing.h"
using std::string;
using std::cout;
using std::endl;
int H_min = 0, S_min = 0, V_min = 0;
int H_max = 179, S_max = 255, V_max = 255;
namespace {
	string base_path("J:/vs2017ws/data/");
	string doc_path("J:/vs2017ws/data/doc_data/");
	void on_trackbar(int, void*) {
		// 空函数，只为了刷新回调
	}
	void tracer_hsv(Mat &img,Mat &hsv)
	{
		// 创建窗口和滑块
		namedWindow("Trackbars", cv::WINDOW_AUTOSIZE);

		// 创建6个滑块，参数指针传 nullptr，推荐方式
		cv::createTrackbar("H min", "Trackbars", nullptr, 179, on_trackbar);
		cv::createTrackbar("H max", "Trackbars", nullptr, 179, on_trackbar);
		cv::createTrackbar("S min", "Trackbars", nullptr, 255, on_trackbar);
		cv::createTrackbar("S max", "Trackbars", nullptr, 255, on_trackbar);
		cv::createTrackbar("V min", "Trackbars", nullptr, 255, on_trackbar);
		cv::createTrackbar("V max", "Trackbars", nullptr, 255, on_trackbar);

		// 设置默认值
		cv::setTrackbarPos("H min", "Trackbars", 35);
		cv::setTrackbarPos("H max", "Trackbars", 85);
		cv::setTrackbarPos("S min", "Trackbars", 50);
		cv::setTrackbarPos("S max", "Trackbars", 255);
		cv::setTrackbarPos("V min", "Trackbars", 50);
		cv::setTrackbarPos("V max", "Trackbars", 255);

		while (true) {
			// 获取当前滑块值
			int H_min = cv::getTrackbarPos("H min", "Trackbars");
			int H_max = cv::getTrackbarPos("H max", "Trackbars");
			int S_min = cv::getTrackbarPos("S min", "Trackbars");
			int S_max = cv::getTrackbarPos("S max", "Trackbars");
			int V_min = cv::getTrackbarPos("V min", "Trackbars");
			int V_max = cv::getTrackbarPos("V max", "Trackbars");

			// 转换到 HSV 空间
			Mat mask, result;
		

			// 创建掩膜并提取颜色
			inRange(hsv, Scalar(H_min, S_min, V_min), Scalar(H_max, S_max, V_max), mask);
			bitwise_and(img, img, result, mask);

			// 显示窗口
			imshow("Original", img);
			imshow("Mask", mask);
			imshow("Extracted", result);

			// 按 ESC 键退出
			if (cv::waitKey(30) == 27) break;
		}
	}


}



void changing_colorspaces::demo01_inRange(void)
{
	Mat img = imread(base_path + "greenback.png", cv::IMREAD_COLOR);
	if (img.empty())
	{
		cout << " load error";
		return;
	}
	//
	int windows_style = cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO;
	//
	string src_name = "img";
	cv::namedWindow(src_name, windows_style);
	imshow(src_name,img);
	//转hsv
	Mat img_hsv;
	cv::cvtColor(img,img_hsv,cv::COLOR_BGR2HSV);
	cv::namedWindow("img_hsv", windows_style);
	imshow("img_hsv", img_hsv);
	//因为是绿色 我们需要找到绿色的范围
	Mat mask;
	//Scalar是 cv::Scalar_<double>  的别名
	Scalar lower=Scalar(35, 43, 46);
	Scalar upper = Scalar(77, 255, 255);
	cv::inRange(img_hsv, lower,upper,mask);
	//
	string mask_pic_name = "mask_pic_name";
	cv::namedWindow(mask_pic_name, windows_style);
	imshow(mask_pic_name, mask);
	//tracer_hsv(img,img_hsv);
	Mat dst;
	Mat mask_inv  ;
	cv::bitwise_not(mask, mask_inv);
	cv::bitwise_and(img,img,dst, mask_inv);//挖洞
	//

	cv::namedWindow("dst", windows_style);
	imshow("dst", dst);
	//
	cv::waitKey(0);
	cv::destroyAllWindows();
	/*
	1,我们要提取一个区域，比如一块绿色区域，就必须找到mask
	2,通过bitwise_and
	*/
}
void changing_colorspaces::demo02_inRange(void)
{
	/*
	cv::inRange 可以用于灰度图和彩色图。
	他只能用于范围 比如[a,b]范围内
	cv::threshold 则一般用于灰度图 其原理属于>变为1 小于变为0 
	二者属于互补关系
	*/
	Mat img = imread(base_path + "greenback.png", cv::IMREAD_COLOR);
	if (img.empty()) {
		cout << "读取失败";
		return;
	}
	int windows_style = cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO;
	string win_name = "img";
	cv::namedWindow(win_name,windows_style);
	imshow(win_name,img);
	//转为hsv
	Mat hsv_img;
	cv::cvtColor(img, hsv_img,cv::COLOR_BGR2HSV);

	Mat mask;//最终转化为二值图
	//Scalar是 cv::Scalar_<double>  的别名
	//最终的比较是内部处理 ，不需要我们关心
	//这三个值可以表示BGR 也可以表示HSV 这里是HSV
	Scalar lower = Scalar(35, 43, 46);
	Scalar upper = Scalar(77, 255, 255);
	cv::inRange(hsv_img, lower, upper, mask);
	win_name = "hsv_img";
	
	cv::namedWindow(win_name, windows_style);
	Mat mask_inv;
	//bitwise_not这个如何处理呢？ 执行按位取反操作 mask 是 
	//mask 非零区域：执行位取反 其它区域不变
	cv::bitwise_not(mask, mask_inv);
	imshow(win_name, mask_inv);
	//
	Mat dst;
	
	//按位与操作 mask_inv 限定了0变为0 ，非0（执行操作）
	/*
	特性	cv::bitwise_and 的mask处理	cv::bitwise_or 的mask处理
	​mask非零区域​	执行按位与操作	    执行按位或操作
	​mask为零区域​	输出设为0（纯黑）	​    保持dst原始值不变​
	​本质操作​	强制修改mask=0区域为黑色	保护mask=0区域不被修改
	​在您案例中的效果​	绿幕图中创建"黑洞"（黑色人物剪影）	保持新背景完整
	​适合场景​	去除背景/挖洞	前景合成/贴图
	*/
	//所以bitwise_and和bitwise_or 对于mask 的处理方式不一样
	cv::bitwise_and(img, img, dst, mask_inv);//挖洞
	win_name = "dst_img";
	cv::namedWindow(win_name, windows_style);
	imshow(win_name, dst);
	//我们可以用

	//
	cv::waitKey(0);
	cv::destroyAllWindows();

}
/*

*/
void image_thresholding::demo01_threshold(void)
{
	
	Mat img = imread(doc_path + "gradient.png", cv::IMREAD_COLOR);
	if (img.empty())
	{
		cout << " load error";
		return;
	}
	//
	int windows_style = cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO;
	//
	string src_name = "img";
	cv::namedWindow(src_name, windows_style);
	imshow(src_name, img);

	//全局阈值
	Mat img_gray;
	cv::cvtColor(img,img_gray,cv::COLOR_BGR2GRAY);
	//
	Mat m1;
	Mat m2;

	Mat m3;
	Mat m4;
	cv::threshold(img_gray, m1, 127, 255, cv::THRESH_BINARY);
	cv::threshold(img_gray, m2, 127, 255, cv::THRESH_BINARY_INV);
	//​当像素值 > 阈值时​：将像素值截断为阈值（127）
	//当像素值 ≤ 阈值时​：保持原值不变  这个不属于二值化
	//减少图像中高光区域的亮度过曝
	cv::threshold(img_gray, m3, 127, 255, cv::THRESH_TRUNC);
	//如果像素值 src(x,y) ​大于​ 阈值 thresh，则保持原值：dst(x,y) = src(x,y)。
	//如果像素值 src(x,y) ​小于等于​ 阈值 thresh，则将该像素值设为0​：dst(x,y) = 0。
	//也不属于二值化
	cv::threshold(img_gray, m4, 127, 255, cv::THRESH_TOZERO);
	//cv::threshold(img_gray, m2, 127, 255, cv::THRESH_TOZERO_INV);
	
	//分离前景和背景 去掉不必要的信息 如纹理和渐变等等 方便后续操作
	Mat m5;
	//0没有用 只是占位 
	//使用Otsu算法自动计算最佳阈值，并使用标准二值化方法
	//通过分析图像直方图自动确定最佳阈值
	//基于类间方差最大化原理
	//特别适用于双峰直方图图像（前景 / 背景分明）
	//不需要我们手动计算
	double thres2 = cv::threshold(img_gray, m5, 0, 255, 
		cv::THRESH_OTSU | cv::THRESH_BINARY);

	Mat binary_trangle;
	double thres1 = cv::threshold(img_gray, binary_trangle, 0, 255, 
		cv::THRESH_TRIANGLE | cv::THRESH_BINARY);
	/*
	​计算灰度直方图​：
	统计图像中各灰度级的像素数量
	对直方图进行平滑处理(防止噪声影响)
	​三角法计算阈值​
	最佳场景​：目标占比很小的单峰直方图图像
	​计算特点​：几何算法比统计分析更简单高效
	​典型应用​：文档、医疗、显微图像等前背景比例悬殊的情况
	对于文档类图像处理（白纸黑字），三角法通常比OTSU更优。在扫描照片或打印文本时，它能更好地区分纸张底色和文字墨迹。实际应用中建议：

	先尝试三角法
	效果不佳时切换到OTSU
	复杂图像使用分块处理
	*/



	cv::waitKey(0);
	cv::destroyAllWindows();
}

void image_thresholding::demo02_adaptive_threshold(void)
{
	Mat img = imread(doc_path + "sudoku.png", cv::IMREAD_COLOR);
	if (img.empty())
	{
		cout << " load error";
		return;
	}
	//
	int windows_style = cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO;
	//
	string src_name = "img";
	cv::namedWindow(src_name, windows_style);
	imshow(src_name, img);
	//
	Mat img_gray;
	cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
	Mat binary_adtive1;
	/*
	计算步骤
	​确定邻域范围​：
	对于图像中的每个像素点 (x, y)，以其为中心确定一个大小为 blockSize × blockSize 的邻域。
	注意：blockSize 必须是奇数（如 3, 5, 7 等），以确保中心点存在。
	​计算邻域均值​：
	计算该邻域内所有像素的灰度值的算术平均值（mean）。
	计算公式：
	mean= 
	blockSize×blockSize
	1
	​
  
	i∈邻域
	∑
	​
	 I(i)
	其中 I(i) 表示邻域内第 i 个像素的灰度值。
	​计算阈值​：
	将计算得到的均值减去常数 C（即参数中的 C 值）得到该像素的阈值 T(x, y)：
	T(x,y)=mean−C
	​应用阈值​：
	根据阈值类型（THRESH_BINARY 或 THRESH_BINARY_INV）进行二值化：
	*/
	cv::adaptiveThreshold(img_gray, binary_adtive1, 255,
		cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 25, 7);
	//
	Mat binary_adtive2;
	//只是进行了加权求和
	//w(i, j) = exp(-((i-x)^2 + (j-y)^2) / (2 * sigma^2)) 
	//sigma = 0.3 * ((blockSize-1)*0.5 - 1) + 0.8

	cv::adaptiveThreshold(img_gray, binary_adtive2, 255,
		cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 25, 7);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void smoothing_images::demo01_filter2D(void)
{
	Mat img = imread(doc_path + "opencv-logo.png", cv::IMREAD_COLOR);
	if (img.empty())
	{
		cout << " load error";
		return;
	}
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_KEEPRATIO;
	//
	string src_name = "img";
	cv::namedWindow(src_name, windows_style);
	imshow(src_name, img);
	
	//
	//filter2D 自定义任意核	
	// 锐化  将原始图像与模糊图像的差值（即高频细节）按比例加回到原始图像上
	cv::Mat sharpen_kernel = (cv::Mat_<float>(3, 3) <<
		0, -1, 0,
		-1, 5, -1,
		0, -1, 0);
	Mat sharpened;
	// ​**ddepth = -1**​ 输出图像使用与输入图像相同的位深度
	//逐通道独立卷积，共享核参数
	//锐化核本质是原始图像与拉普拉斯算子的组合：

	cv::filter2D(img, sharpened, -1, sharpen_kernel);
	string sharpen_kernel_name = "sharpen_kernel";
	cv::namedWindow(sharpen_kernel_name, windows_style);
	imshow(sharpen_kernel_name, sharpened);
	//
	cv::waitKey(0);
	cv::destroyAllWindows();
	/*
	#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 可视化卷积核函数
void visualizeKernel(Mat kernel, String name) {
    // 归一化核为0-255范围
    Mat kernel_viz;
    normalize(kernel, kernel_viz, 0, 255, NORM_MINMAX, CV_8U);
    
    // 放大可视化
    resize(kernel_viz, kernel_viz, Size(200, 200), 0, 0, INTER_NEAREST);
    
    // 显示核
    imshow("Kernel: " + name, kernel_viz);
}

int main() {
    // 1. 读取图像
    Mat img = imread("opencv-logo.png", IMREAD_COLOR);
    if (img.empty()) {
        cerr << "Error: Could not load image!" << endl;
        return -1;
    }
    
    // 调整大小以便显示
    resize(img, img, Size(600, 600 * img.rows / img.cols));
    
    // 创建显示窗口
    namedWindow("Original Image", WINDOW_AUTOSIZE);
    imshow("Original Image", img);
    
    // 2. 定义不同卷积核
    // 锐化核
    Mat sharpen_kernel = (Mat_<float>(3, 3) << 
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0);
    
    // 边缘检测核 (Sobel水平)
    Mat edge_kernel = (Mat_<float>(3, 3) <<
        -1, -2, -1,
        0, 0, 0,
        1, 2, 1);
    
    // 模糊核 (高斯近似)
    Mat blur_kernel = (Mat_<float>(5, 5) << 
        1, 4, 6, 4, 1,
        4, 16, 24, 16, 4,
        6, 24, 36, 24, 6,
        4, 16, 24, 16, 4,
        1, 4, 6, 4, 1) / 256.0;
    
    // 浮雕效果核
    Mat emboss_kernel = (Mat_<float>(3, 3) << 
        -1, -1, 0,
        -1, 1, 1,
        0, 1, 1);
    
    // 可视化所有核
    visualizeKernel(sharpen_kernel, "Sharpen");
    visualizeKernel(edge_kernel, "Edge Detection");
    visualizeKernel(blur_kernel, "Blur");
    visualizeKernel(emboss_kernel, "Emboss");
    
    // 3. 应用卷积核
    Mat sharpened, edges, blurred, embossed;
    
    // 锐化处理 (保留色彩)
    Mat img_yuv;
    cvtColor(img, img_yuv, COLOR_BGR2YUV);
    vector<Mat> channels;
    split(img_yuv, channels);
    filter2D(channels[0], channels[0], -1, sharpen_kernel); // 仅处理亮度通道
    merge(channels, img_yuv);
    cvtColor(img_yuv, sharpened, COLOR_YUV2BGR);
    
    // 边缘检测
    Mat img_gray;
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    filter2D(img_gray, edges, CV_16S, edge_kernel); // 使用有符号输出
    convertScaleAbs(edges, edges); // 转换为绝对值
    
    // 模糊处理
    filter2D(img, blurred, -1, blur_kernel);
    
    // 浮雕效果
    filter2D(img, embossed, -1, emboss_kernel, Point(-1, -1), 150); // 添加偏移量150
    
    // 4. 显示结果
    namedWindow("Sharpened (YUV)", WINDOW_AUTOSIZE);
    namedWindow("Edge Detection", WINDOW_AUTOSIZE);
    namedWindow("Blurred", WINDOW_AUTOSIZE);
    namedWindow("Embossed", WINDOW_AUTOSIZE);
    
    imshow("Sharpened (YUV)", sharpened);
    imshow("Edge Detection", edges);
    imshow("Blurred", blurred);
    imshow("Embossed", embossed);
    
    // 5. 高级应用：选择性锐化
    // 创建边缘掩码
    Mat edges_mask;
    Canny(img, edges_mask, 100, 200);
    
    // 整体锐化
    Mat globally_sharpened;
    filter2D(img, globally_sharpened, -1, sharpen_kernel);
    
    // 组合结果：仅在边缘区域应用锐化
    Mat selectively_sharpened = img.clone();
    globally_sharpened.copyTo(selectively_sharpened, edges_mask);
    
    namedWindow("Selective Sharpening", WINDOW_AUTOSIZE);
    imshow("Selective Sharpening", selectively_sharpened);
    
    // 6. 性能对比测试
    cout << "=== Performance Test ===" << endl;
    
    // 测试不同核大小的速度
    Mat large_blur_kernel = getGaussianKernel(15, 2.0) * getGaussianKernel(15, 2.0).t();
    
    Mat test_img;
    resize(img, test_img, Size(1200, 1200)); // 更大的测试图像
    
    double t;
    
    // 小核 (3x3)
    t = (double)getTickCount();
    filter2D(test_img, sharpened, -1, sharpen_kernel);
    t = ((double)getTickCount() - t) / getTickFrequency();
    cout << "3x3 kernel time: " << t * 1000 << " ms" << endl;
    
    // 大核 (15x15)
    t = (double)getTickCount();
    filter2D(test_img, blurred, -1, large_blur_kernel);
    t = ((double)getTickCount() - t) / getTickFrequency();
    cout << "15x15 kernel time: " << t * 1000 << " ms" << endl;
    
    // 可分离核优化
    cout << "\nOptimization Techniques:" << endl;
    
    // 使用 sepFilter2D 优化
    Mat row_kernel = getGaussianKernel(15, 2.0);
    Mat col_kernel = row_kernel.t();
    
    t = (double)getTickCount();
    sepFilter2D(test_img, blurred, -1, row_kernel, col_kernel);
    t = ((double)getTickCount() - t) / getTickFrequency();
    cout << "Separable kernel time: " << t * 1000 << " ms" << endl;
    
    // 7. 实时视频处理示例
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Cannot open camera!" << endl;
    } else {
        namedWindow("Real-time Edge Detection", WINDOW_AUTOSIZE);
        
        Mat frame, processed;
        while (waitKey(30) != 27) { // 按ESC退出
            cap >> frame;
            if (frame.empty()) break;
            
            // 转换为灰度
            cvtColor(frame, processed, COLOR_BGR2GRAY);
            
            // 应用边缘检测
            filter2D(processed, processed, CV_16S, edge_kernel);
            convertScaleAbs(processed, processed);
            
            // 显示结果
            imshow("Real-time Edge Detection", processed);
        }
    }
    
    waitKey(0);
    destroyAllWindows();
    return 0;
}
	*/
}

void smoothing_images::demo01_blur(void)
{
	Mat img = imread(doc_path + "opencv-logo-white.png", cv::IMREAD_COLOR);
	if (img.empty())
	{
		cout << " load error";
		return;
	}
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_KEEPRATIO;
	//
	string src_name = "img";
	cv::namedWindow(src_name, windows_style);
	imshow(src_name, img);

	//cv::boxFilter 可以归一化 也可以不归一化，归一化和cv::blur一样
	Mat dst;
	cv::blur(img,dst,cv::Size(3,3));
	string blur_name = "blur";
	cv::namedWindow(blur_name, windows_style);
	imshow(blur_name, dst);//

	cv::waitKey(0);
	cv::destroyAllWindows();
	/*
	Gaussian Blurring 利用高斯公式
	Median Blurring  取窗口 排序  取中值  去除椒盐噪声（如旧照片扫描、传感器噪声等）  
	                 //需要保留边缘的去噪任务
                     //医学图像处理（如去除X光图像的噪声）
	Bilateral Filtering  双边滤波
	也就是说如果窗口时3*3，其要计算各个位置上的空间权重和像素值权重，统计总的权重，
	然后再相加求和 计算中心点的像素值 

	*/
}

void morphological_transformation::demo01_erosion(void)
{
	
}
#include <fstream>

void geometric_transformations::demo01_warpAffine(void)
{
	/*
	https://docs.opencv.org/4.8.0/da/d6e/
	tutorial_py_geometric_transformations.html
	*/
	Mat img = imread("Resources/messi5.jpg", cv::IMREAD_COLOR);
	if (img.empty())
	{
		cout << " load error";
		return;
	}
	int windows_style = cv::WINDOW_AUTOSIZE | cv::WINDOW_KEEPRATIO;
	//
	string win_name = "img";
	cv::namedWindow(win_name, windows_style);
	imshow(win_name, img);
	//
	Mat dst;
	Size size=Size();
	//我们只需要制定一个就行 size优先级大于缩放比例
	//cv::INTER_CUBIC 用于放大图像
	cv::resize(img,dst, size, 2.0, 2.0, cv::INTER_CUBIC);
	win_name = "resize_img";
	cv::namedWindow(win_name, windows_style);
	imshow(win_name, dst);
	//实现平移 平移可以参考线性代数的线性变换
	//旋转矩阵必须是浮点数 可以是CV_32F（单精度浮点）或CV_64
	//创建旋转矩阵
	float tx = 100.0f;  // x方向平移：右移1像素
	float ty = 50.0f;  // y方向平移：下移2像素
	cv::Mat transform_matrix = (cv::Mat_<float>(2,3) << 
		1, 0, tx,
		0, 1, ty
	);
	cv::Mat translated_img;
	cv::warpAffine(
		img,                    // 输入图像
		translated_img,          // 输出图像
		transform_matrix,        // 变换矩阵
		img.size(),              // 输出尺寸（与输入相同）
		cv::INTER_LINEAR,        // 插值方法
		cv::BORDER_CONSTANT,     // 边界处理方式 也是默认的处理方式
		cv::Scalar(0, 0, 0)      // 边界填充颜色（黑色）
	);
	//旋转 当θ为正时​：表示逆时针旋转 
	win_name = "trans_img";
	cv::namedWindow(win_name, windows_style);
	imshow(win_name, translated_img);
	//
	cv::waitKey(0);
	cv::destroyAllWindows();
}
