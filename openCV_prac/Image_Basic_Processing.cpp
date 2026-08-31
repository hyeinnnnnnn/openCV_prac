#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int Image_Basic_Processing()
{
	namedWindow("img", 0);
	namedWindow("img2", 0);

	Mat img = imread("resource\\images\\09_chessboard_flat.png");
	Mat img2;

	// sobel : 소벨필터를 사용하여 Gradient값을 구하는 방법
	//Sobel(img, img2, img2.depth(), 1, 0);

	// flip : 가로로 대칭시킴
	flip(img, img2, 1);

	imshow("img", img); // show
	imshow("img2", img2); // show

	waitKey(0);

	destroyAllWindows();

	return 0;
}