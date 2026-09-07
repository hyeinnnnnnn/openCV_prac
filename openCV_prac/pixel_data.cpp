#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int pixel_data(string imagePath)
{
	namedWindow("img", 1);
	Mat img = imread(imagePath);

	// img 정보 ===================
	cout << "img.elemSize() : " << img.elemSize() << endl;
	cout << "img.channels() : " << img.channels() << endl;
	cout << "img.rows : " << img.rows << endl;
	cout << "img.cols : " << img.cols << endl;
	cout << "img.step : " << img.step << endl;
	cout << "img.step / img.rows : " << img.step / img.rows << endl;

	/*
	*	img.step : 한 행이 메모리에서 차지하는 전체 바이트 수(패딩 포함)
	*	img.channels() : 채널 개수(Count)
	*	img.elemSize() : 픽셀 하나가 차지하는 바이트 수 ( 8bit 3채널 BGR 이미지는 3Byte)
	*
	*/

	// ===========================


	// using data
	// 내장 함수 있음
	// cv::bitwise_not(img, img)->더 빠름
	for (int i = img.rows / 10 * 1; i < img.rows / 10 * 2; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			// i * img.step : i번째 행의 시작 위치로 이동
			// j * img.elemSize() : 해당 행의 j번째 열 위치로 이동
			unsigned r, g, b;
			b = img.data[i * img.step + j * img.elemSize() + 0];
			g = img.data[i * img.step + j * img.elemSize() + 1];
			r = img.data[i * img.step + j * img.elemSize() + 2];



			// 해당 픽셀 위치의 데이터 = 색상 반전 대입
			img.data[i * img.step + j * img.elemSize() + 0] = unsigned char(255 - b);
			img.data[i * img.step + j * img.elemSize() + 1] = unsigned char(255 - g);
			img.data[i * img.step + j * img.elemSize() + 2] = unsigned char(255 - r);
		}
	}

	// using at
	for (int i = img.rows / 10 * 3; i < img.rows / 10 * 4; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			// Vec3b -> Vector of 3 unsigned bytes
			unsigned char b = img.at<Vec3b>(i, j)[0];
			unsigned char g = img.at<Vec3b>(i, j)[1];
			unsigned char r = img.at<Vec3b>(i, j)[2];
			
			img.at<Vec3b>(i, j)[0] = unsigned char(255 - b);
			img.at<Vec3b>(i, j)[1] = unsigned char(255 - g);
			img.at<Vec3b>(i, j)[2] = unsigned char(255 - r);
		}
	}

	// using ptr
	for (int i = img.rows / 10 * 5; i < img.rows / 10 * 6; i++)
	{
		Vec3b* ptr = img.ptr<cv::Vec3b>(i);

		for (int j = 0; j < img.cols; j++)
		{

			Vec3b bgr = ptr[j];
			unsigned char b = (bgr[0]);
			unsigned char g = (bgr[1]);
			unsigned char r = (bgr[2]);

			ptr[j] = Vec3b(255 - b, 255 - g, 255 - r);
		}
	}

	imshow("img", img);
	waitKey(0);

	destroyAllWindows();
	return 0;
}