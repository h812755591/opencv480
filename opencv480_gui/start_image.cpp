#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include "start_image.h"
using std::string;
using cv::Mat;
using cv::imread;
using cv::waitKey;
namespace {
	string base_path("J:/vs2017ws/data/");

}
void start_image::show(void)
{
	string image_path = base_path + "book.jpg";
	// 读取是BGR
	Mat img = imread(image_path, cv::IMREAD_COLOR);
	if (img.empty())
	{
		std::cout << "Could not read the image: " << image_path << std::endl;
		return;
	}
	imshow("Display window", img);
	int k = waitKey(0);// 超时返回-1  
	if (k == 's')
	{
		// 保存 也需要是BGR
		/*
		在使用 OpenCV 的 imwrite 保存图像时，若发现保存后的图片体积与原图不一致，
		核心原因与 ​图像格式的压缩特性​ 和 ​
		OpenCV 默认参数设置​ 有关

		​JPG 格式的有损压缩特性​
		JPG 是一种有损压缩格式，保存时会丢弃部分高频细节以减小文件体积
		。若原图已经是低质量 JPG，保存时即使使用默认参数（质量 95），也可能导致 ​体积进一步缩小；
		若原图是无损格式（如 BMP/PNG），保存为 JPG 时体积会显著减小
		。
		​默认压缩参数的差异​
		OpenCV 的 imwrite 默认保存 JPG 的质量参数为 95
		。若原图质量参数更高（如 100），保存后体积会因压缩率增加而 ​变小；若原图质量参数更低，保存后体积可能 ​变大。
		​重复保存的累积压缩损失​
		多次保存 JPG 文件会导致图像质量逐次下降，体积逐渐缩小（类似“压缩迭代”）
		。例如，原图 233MB 的 JPG 保存后可能变为 229MB，多次操作后体积持续减少
		​注意事项​：即使设为 100，仍存在轻微压缩（非完全无损）
。		若需完全保留图像数据，改用 ​PNG 或 BMP​ 格式
		*/
		std::vector<int> compression_params;
		compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
		compression_params.push_back(100);
		imwrite("starry_night.jpg", img, compression_params);
	}
	cv::destroyAllWindows();
}

void start_image::write(void)
{

}
