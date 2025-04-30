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
	std::string config = "D:/projects/opencv_tutorial/data/models/face_detector/deploy.prototxt";
	std::string model = "D:/projects/opencv_tutorial/data/models/face_detector/res10_300x300_ssd_iter_140000_fp16.caffemodel";
	Net net = readNetFromCaffe(config, model);
	net.setPreferableBackend(DNN_BACKEND_INFERENCE_ENGINE);
	net.setPreferableTarget(DNN_TARGET_CPU);
	VideoCapture cap(0);
	Mat frame;
	while (true) {
		int64 start = getTickCount();
		bool ret = cap.read(frame);
		flip(frame, frame, 1);
		if (!ret) {
			break;
		}
		Mat blobImage = blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);
		net.setInput(blobImage);
		Mat detection = net.forward();
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
		float fps = getTickFrequency() / (getTickCount() - start);
		float time = (getTickCount() - start) / getTickFrequency();
		ostringstream ss;
		ss << "FPS : " << fps << " detection time: " << time * 1000 << " ms";
		putText(frame, ss.str(), Point(20, 20), 0, 0.5, Scalar(0, 0, 255));
		imshow("ÈËÁ³¼ì²â", frame);
		char c = waitKey(1);
		if (c == 27) { // ESC
			break;
		}
	}
	destroyAllWindows();
	return 0;
}