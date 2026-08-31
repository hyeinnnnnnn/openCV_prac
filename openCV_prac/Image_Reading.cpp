#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int Image_Reading()
{
	// image reading
	Mat img = imread("resource\\images\\01_shapes_colors.png");
	// imread("image", 0); -> grayScale

	namedWindow("imageWindow", 0); // 0 -> 리사이징 가능, 1 -> 고정
	imshow("imageWindow", img);
	waitKey(0);

	return 0;
}