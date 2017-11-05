#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>

using namespace std;

string getCameraFeed(int width, int height, int fps) {
	return "nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(width) + ", height=(int)" + std::to_string(height) + ", framerate=(fraction)" + std::to_string(fps) + "/1, format NV12 ! nvvidconv flip-method=4 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

int main() {
	int WIDTH = 1280;
	int HEIGHT = 720;
	int FPS = 30;

	string pipeline = getCameraFeed(WIDTH, HEIGHT, FPS);
	cout << "Using pipeline: \n\t" << pipeline << "\n";

	cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
	if (!cap.isOpened()) {
		cout << "Connection Failed";
		return -1;
	}

	cv::Mat frame;
	while (1) {
		cap >> frame;

		imshow("Camera Liveview", frame);
		cv::waitKey(1);
	}
}
