#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "kcftracker.hpp"

#include <dirent.h>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{

	if (argc > 5)
		return -1;

	bool HOG = true;
	bool FIXEDWINDOW = false;
	bool MULTISCALE = true;
	bool SILENT = true;
	bool LAB = false;

	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "hog") == 0)
			HOG = true;
		if (strcmp(argv[i], "fixed_window") == 0)
			FIXEDWINDOW = true;
		if (strcmp(argv[i], "singlescale") == 0)
			MULTISCALE = false;
		if (strcmp(argv[i], "show") == 0)
			SILENT = false;
		if (strcmp(argv[i], "lab") == 0)
		{
			LAB = true;
			HOG = true;
		}
		if (strcmp(argv[i], "gray") == 0)
			HOG = false;
	}

	// Create KCFTracker object
	KCFTracker tracker(HOG, FIXEDWINDOW, MULTISCALE, LAB);

	// Tracker results
	Rect result;

	string inputPath = "../video/tv_tuanliu.mkv";
	string resultsPath = "../video/output_video.mp4";

	VideoCapture cap(inputPath);
	if (!cap.isOpened())
	{
		cerr << "Error: Could not open video." << endl;
		return -1;
	}

	// 获取视频帧率和帧尺寸
	double fps = cap.get(CAP_PROP_FPS);
	int width = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
	int height = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));
	VideoWriter video_writer(resultsPath, VideoWriter::fourcc('a', 'v', 'c', '1'), fps, Size(width, height));

	Mat frame;
	if (!cap.read(frame))
	{
		cerr << "Error: Could not read the first frame." << endl;
		return -1;
	}
	Rect bbox_first = Rect(706, 679, 155, 141);

	tracker.init(bbox_first, frame);

	rectangle(frame, bbox_first, cv::Scalar(0, 255, 0), 2);
	if (!imwrite("../frame/first_frame.jpg", frame))
	{
		cerr << "Error: Could not save the first frame to ../frame/first_frame.jpg" << endl;
		return -1;
	}

	while (cap.read(frame))
	{
		double t1 = getTickCount();
		result = tracker.update(frame);
		// rectangle(frame, Point(result.x, result.y), Point(result.x + result.width, result.y + result.height), Scalar(0, 255, 0), 2, 8);
		rectangle(frame, result, Scalar(0, 255, 0), 2);
		imwrite("../frame/debug_frame.jpg", frame);
		video_writer.write(frame);

		double t2 = getTickCount();
		double process_time_ms = (t2 - t1) * 1000 / getTickFrequency();
		double fps_value = getTickFrequency() / (t2 - t1);
		cout << "每帧处理时间: " << process_time_ms << " ms, FPS: " << fps_value << endl;
	}
	// resultsFile.close();
	cap.release();
	video_writer.release();

	return 0;
}
