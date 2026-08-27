#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void main()
{
	//file load
	VideoCapture capture("resource\\videos\\01_moving_shapes.mp4");
	Mat frame;

	//check
	if (!capture.isOpened())
	{
		printf("AVI file can not open.\n");
		return;
	}

	// create window
	namedWindow("w");

	while (1)
	{
		//grab frame for file & throw to Mat
		capture >> frame;
		if (frame.empty())	// Is video end?
			break;

		//processing example
		Sobel(frame, frame, frame.depth(), 1, 0);

		//displat and delay
		imshow("w", frame);
		if (waitKey(10) > 0)
			break;
	}
}