#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	// 
	// 32F : 32bit floating-point matrix
	Mat mtx(3, 3, CV_32F); // mtx(행, 열, [행렬 안에 있는 값들의 데이터 타입])

	// 64FC2 : 64bit floating-point 2-Channel
	Mat cmtx(10, 1, CV_64FC2);

	// 8UC3 : 8bit UnsignedCharactor 3-Channel 이미지 (3채널 == color)
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
	std::cout << cmtx2 << std::endl;

	cmtx2.setTo(11);
	std::cout << cmtx << std::endl;		// -> 10,1 행렬이지만, 채널이 두개라서 11,11 ; 11,11; 11,11; ,, 이렇게 쯤

	return 0;
}