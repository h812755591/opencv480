#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

String objNames[] = { "background",
"aeroplane", "bicycle", "bird", "boat",
"bottle", "bus", "car", "cat", "chair",
"cow", "diningtable", "dog", "horse",
"motorbike", "person", "pottedplant",
"sheep", "sofa", "train", "tvmonitor" };

int main(int argc, char** argv) {
	Mat frame = imread("D:/images/dog.jpg");
	if (frame.empty()) {
		printf("could not load image...\n");
		return 0;
	}
	namedWindow("input image", WINDOW_AUTOSIZE);
	imshow("input image", frame);
	std::string model_text_file = "D:/projects/opencv_tutorial/data/models/ssd/MobileNetSSD_deploy.prototxt";
	std::string modelFile = "D:/projects/opencv_tutorial/data/models/ssd/MobileNetSSD_deploy.caffemodel";
	Net net = readNetFromCaffe(model_text_file, modelFile);
	Mat blobImage = blobFromImage(frame, 0.007843,
		Size(300, 300),
		Scalar(127.5, 127.5, 127.5), false, false);
	printf("blobImage width : %d, height: %d\n", blobImage.cols, blobImage.rows);

	net.setInput(blobImage, "data");
	Mat detection = net.forward("detection_out");

	// post-process
	Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
	float confidence_threshold = 0.5;
	for (int i = 0; i < detectionMat.rows; i++) {
		float* curr_row = detectionMat.ptr<float>(i);
		int image_id = (int)(*curr_row++);
		size_t objIndex = (size_t)(*curr_row++);
		float score = *curr_row++;
		if (score > confidence_threshold) {
			float tl_x = (*curr_row++) * frame.cols;
			float tl_y = (*curr_row++) * frame.rows;
			float br_x = (*curr_row++) * frame.cols;
			float br_y = (*curr_row++) * frame.rows;

			Rect object_box((int)tl_x, (int)tl_y, (int)(br_x - tl_x), (int)(br_y - tl_y));
			rectangle(frame, object_box, Scalar(0, 0, 255), 2, 8, 0);
			putText(frame, format(" confidence %.2f, %s", score, objNames[objIndex].c_str()), Point(tl_x - 10, tl_y - 5), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 0, 0), 2, 8);
		}
	}
	imshow("ssd-demo", frame);

	waitKey(0);
	return 0;
}