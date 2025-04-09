#include <opencv2/opencv.hpp>
#include <iostream>
using  std::cout;
using  std::endl;
using  std::string;
using cv::Mat;

int main(int argc, char * argv[])
{
	cout << "hello world" << endl;
	string root_dir = "J:/vs2017ws/models/face_detector/";
	string model_path = root_dir + "opencv_face_detector_uint8.pb";
	string config_path = root_dir + "opencv_face_detector.pbtxt";
	cv::dnn::Net net = cv::dnn::readNetFromTensorflow(model_path, config_path);
		
	cv::VideoCapture cap(0);
	if (!cap.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
		return -1;
	}
	cv::Mat frame;
	for (;;)
	{
		
		cap.read(frame);
		// check if succ
		if (frame.empty()) {
			std::cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		Mat blob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(300, 300), 
			cv::Scalar(104, 177, 123), false, false);
		net.setInput(blob);// NCHW
		Mat probs = net.forward(); // 
		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());
		for (int i = 0; i < detectionMat.rows; i++) {
			float confidence = detectionMat.at<float>(i, 2);
			if (confidence > 0.5) {
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3)*frame.cols);
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4)*frame.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5)*frame.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6)*frame.rows);
				cv::Rect box(x1, y1, x2 - x1, y2 - y1);
				cv::rectangle(frame, box, cv::Scalar(0, 0, 255), 2, 8, 0);
			}
		}
		imshow("人脸检测演示", frame);
		if (cv::waitKey(1) == 'q')
		{
			break;
		}

	}

	//释放资源
	cap.release();
	return 0;
}