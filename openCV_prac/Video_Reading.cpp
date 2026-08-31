#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int Video_Reading()
{
	// VideoCapture cap(0); // open the default camera
	VideoCapture cap("resource\\videos\\01_moving_shapes.mp4");
	Mat frame;

	if (!cap.isOpened()) // check if we succeeded
	{
		printf("영상을 열지 못했습니다.\n");		
		return -1;
	}

	namedWindow("VidoeWindow", 1);
	for (;;)
	{
		// grap frame from file & throw to Mat
		cap >> frame; // get a new frame from camera

		// 비디오가 끝나면 종료
		if (frame.empty())
			break;

		// Sobel Filler
		Sobel(frame, frame, frame.depth(), 1, 0);

		// display and delay
		imshow("VidoeWindow", frame);

		// 아무 키나 누르면 종료
		if (waitKey(30) == 27) // ESC
			break;
	}

	return 0;
}