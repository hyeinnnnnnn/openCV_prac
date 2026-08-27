#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat mtx(3, 3, CV_32F); // mtx(행, 열, ..)
	Mat cmtx(10, 1, CV_64FC2);
	Mat img(Size(5, 3), CV_8UC3); // size(width, height, ..)

	Mat mtx2;
	mtx2 = Mat(3, 3, CV_32F);

	Mat cmtx2;
	cmtx2 = Mat(10, 1, CV_64FC1);

	Mat* mtx3 = new Mat(3, 3, CV_32F);
	delete mtx3;

	mtx.setTo(10);
	std::cout << mtx << std::endl;

	cmtx2.setTo(11);
	std::cout << cmtx << std::endl;

	return 0;
}