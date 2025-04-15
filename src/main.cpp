#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	// 读取视频文件
	// VideoCapture cap("../video/girl_dance.mp4");
	VideoCapture cap("../video/input_tracking.mp4");
	int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
	int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
	if (!cap.isOpened())
	{
		std::cout << "Error opening video file\n";
		return -1;
	}
	// 写入视频文件
	VideoWriter videowriter(
		// "../video/girl_dance_kcf.mp4",
		"../video/input_tracking_kcf.mp4",
		VideoWriter::fourcc('a', 'v', 'c', '1'),
		cap.get(cv::CAP_PROP_FPS),
		Size(width, height));

	Mat frame;
	cap.read(frame);

	// 设定屏幕大小
	// const int screenWidth = 2560;
	// const int screenHeight = 1440;

	// 初始化目标框
	// Rect2d roi = selectROI("Select ROI", frame);
	int count = 0;
	// =======girl_dance(255, 155, 62, 60)======
	//  Rect rectRoi = Rect(255, 155, 62, 60);
	// =======input_tracking=====
	Rect rectRoi = Rect(680, 680, 156, 127);

	if (rectRoi.width == 0 || rectRoi.height == 0)
	{
		std::cout << "ROI selection canceled\n";
		return -1;
	}

	// 创建KCF跟踪器
	Ptr<TrackerKCF> tracker = TrackerKCF::create();

	// 将Rect2d类型转换为Rect类型
	// Rect rectRoi(static_cast<int>(roi.x), static_cast<int>(roi.y),
	// 			 static_cast<int>(roi.width), static_cast<int>(roi.height));

	// 初始化跟踪器
	tracker->init(frame, rectRoi);

	// 保存最后一帧的目标框位置
	Rect2d lastRect = rectRoi;

	// 循环处理视频帧
	while (cap.read(frame))
	{

		if (frame.empty())
		{
			std::cerr << "无效帧！跳过！" << std::endl;
			break;
		}
		// 更新跟踪器
		bool success = tracker->update(frame, rectRoi);
		if (success)
		{
			// 在图像上绘制跟踪框
			std::cout << "[success] Tracking success  count: " << ++count << std::endl;
			printf("roi : [x->%d , y->%d , w->%d, h->%d]\n", rectRoi.x, rectRoi.y, rectRoi.width, rectRoi.height);
			rectangle(frame, rectRoi, Scalar(0, 255, 0), 2);
			if (count == 1)
			{
				imwrite("../frame/input_tracking_first.jpg", frame);
			}
			lastRect = rectRoi; // 更新最后一帧的目标框位置
		}
		else
		{
			printf("roi : [x->%d , y->%d , w->%d, h->%d]\n", rectRoi.x, rectRoi.y, rectRoi.width, rectRoi.height);
			if (lastRect.width > 0 && lastRect.height > 0)
			{
				// tracker->~TrackerKCF();
				tracker = TrackerKCF::create();
				tracker->init(frame, lastRect);
				std::cout << "[failure]Tracking failure detected\n";
				rectRoi = lastRect; // 使用最后一帧的目标框位置
			}
		}

		// 将帧调整为与屏幕大小相同
		// resize(frame, frame, Size(screenWidth, screenHeight));

		// 显示当前帧
		// imshow("Tracking", frame);

		// 视频写入
		videowriter.write(frame);

		// 等待大约16毫秒，以实现60帧每秒的播放速度//== 27 的部分是在检查用户是否按下了键盘上的 Escape 键（ASCII码为27）。如果用户按下了 Escape 键，条件成立，就会跳出循环，从而退出程序。
		// if (waitKey(16) == 27)
		// {
		// 	break;
		// }
	}

	// 释放资源
	cap.release();
	videowriter.release();
	destroyAllWindows();

	return 0;
}