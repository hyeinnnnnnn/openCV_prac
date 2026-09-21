#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int Mat_and_Image_Video_write(string imagePath)
{
	Mat img = imread(imagePath);
	vector<Mat> rgbMat(3);
	cv::split(img, rgbMat);

	namedWindow("img", 0);
	imshow("img", rgbMat[2]);
	waitKey(0);

	imwrite("r.jpg", rgbMat[2]);
	imwrite("g.jpg", rgbMat[1]);
	imwrite("b.jpg", rgbMat[0]);

	/*
	// 다 용량이 다름
	imwrite("new_img.jpg", img);
	imwrite("new_img.bmp", img);
	imwrite("new_img.tif", img);
	imwrite("new_img.png", img);*/

	Mat img2;
	Sobel(img, img, CV_8U, 1, 0);
	imwrite("sobel_img.png", img);

	return 0;
}