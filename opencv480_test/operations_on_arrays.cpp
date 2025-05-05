#include <opencv2/opencv.hpp>
#include <iostream>
#include "operations_on_arrays.h"
using cv::Mat;
using cv::SVD;
using std::cout;
using std::endl;
using cv::Rect;
void OperationsOnArrays::demo01_SVD(void)
{
	// 定义 2x3 矩阵（示例值）
	float data[6] = { 3.0, 0.0, 4.0, 5.0, 2.0, 1.0 };
	Mat A(2, 3, CV_32F, data);

	// 执行 SVD 分解
	Mat U, S, Vt;
	SVD::compute(A, S, U, Vt, SVD::FULL_UV);

	// 构造奇异值对角矩阵 Σ (2x3)
	Mat Sigma = Mat::zeros(A.rows, A.cols, CV_32F);
	for (int i = 0; i < S.rows; ++i) {
		Sigma.at<float>(i, i) = S.at<float>(i);
	}

	// 输出结果
	cout << "原始矩阵 A:\n" << A << endl;
	cout << "左奇异矩阵 U:\n" << U << endl;
	cout << "奇异值矩阵 Σ:\n" << Sigma << endl;
	cout << "右奇异矩阵 Vt:\n" << Vt << endl;

	// 验证分解正确性：A ≈ U * Σ * Vt
	Mat reconstructed = U * Sigma * Vt;
	cout << "重构矩阵 UΣVt:\n" << reconstructed << endl;
}

void OperationsOnArrays::demo02_SVD(void)
{
	Mat src1 = cv::imread("J:/vs2017ws/data/example.png");
	cv::imshow("Original1", src1);
	//
	Mat src;
	cv::cvtColor(src1, src,cv::COLOR_BGR2GRAY);
	cout << "src size=" << src.size() << endl;//src size=[353 x 496]
	if (src.empty()) return;
	// 2. 转换为浮点型矩阵（SVD需要浮点输入）
	Mat src_float;
	src.convertTo(src_float, CV_32F, 1.0 / 255.0);

	// 3. SVD分解（注意参数顺序）
	Mat S, U, Vt;
	SVD::compute(src_float, S, U, Vt, SVD::FULL_UV);  // 
	cout << "U size=" << U.size() << endl;//U size=[496 x 496]
	cout << "S size=" << S.size() << endl;//S size=[1 x 353]
	cout << "Vt size=" << Vt.size() << endl;//Vt size=[353 x 353]
	// 4. 设置压缩率（保留前k个奇异值）
	int k = 50;  // 压缩比约 (k*(m + n +1))/(m*n)
	cout << "保留奇异值数量: " << k << "/" << S.rows << endl;

	// 5. 截取关键矩阵
	// 左奇异矩阵U的前k列（m x k）
	Mat U_trunc = U(cv::Rect(0, 0, k, U.rows));
	// 右奇异矩阵Vt的前k行（k x n）
	Mat Vt_trunc = Vt(Rect(0, 0, Vt.cols, k));
	// 构建k x k对角奇异值矩阵
	Mat S_trunc = Mat::zeros(k, k, CV_32F);
	for (int i = 0; i < k; i++) {
		S_trunc.at<float>(i, i) = S.at<float>(i);
	}

	// 6. 重构压缩图像
	Mat compressed = U_trunc * S_trunc * Vt_trunc;//实际上这个计算是需要交换的
	cout << "U_trunc size=" << U_trunc.size() << endl;//U_trunc size=[50 x 496]
	cout << "S_trunc size=" << S_trunc.size() << endl;//S_trunc size=[50 x 50]
	cout << "Vt_trunc size=" << Vt_trunc.size() << endl;//Vt_trunc size=[353 x 50]
	compressed.convertTo(compressed, CV_8U, 255.0);  // 还原到0-255范围[8](@ref)
	cout << "compressed size=" << compressed.size() << endl;//
	// 7. 显示对比结果
	imshow("原始图像", src);
	imshow("压缩图像 (k=" + std::to_string(k) + ")", compressed);
	cv::waitKey(0);
	cv::destroyAllWindows();
}
