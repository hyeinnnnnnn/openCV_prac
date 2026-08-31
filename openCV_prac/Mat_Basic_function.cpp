#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int Mat_Basic_Function()
{
	Mat img = imread("resource\\images\\01_shapes_colors.png");
	
	// ========== 이미지 반전 처리 ==========
	Mat img2;
	bitwise_not(img, img2); // 이미지 반전

	// ========== 이미지 얕은 복사 ==========
	Mat img_s = img; // 대입x 참조o

	// ========== 이미지 깊은 복사 ==========
	Mat imgClone = img.clone();

	// ========== Rect  ([col처음 좌표], [row 처음 좌표], [col길이], [row길이]) ==========
	Rect r(img.cols / 4, img.rows / 4, img.cols / 4 * 2, img.rows / 4 * 2);
	cout << r << endl;
	Mat imgRect = img(r).clone();
	 
	// ========== CopyTo() -> 깊은 복사 ==========
	Mat imgCopy;
	img.copyTo(imgCopy);

	// ========== CopyTo() -> 크기 지정 깊은 복사 ==========
	Mat imgCopy2;
	img(r).copyTo(imgCopy2);

	// ========== CopyTo() -> 활용 ========== 
	Mat imgCopy3(Size(img.cols * 2, img.rows), img.type()); // img의 가로 2배 크기로 초기화
	imgCopy3.setTo(255); // 배경 흰색으로

	// 왼쪽 : 원본(0부터 img 가로 크기만큼
	img.copyTo(imgCopy3(Range::all(), Range(0, img.cols))); 

	// 오른쪽 : img2(반전처리 이미지) img가로 크기 위치좌표부터 끝까지
	img2.copyTo(imgCopy3(Range::all(), Range(imgClone.cols, imgClone.cols * 2))); 

	// ========== SET ROI ==========
	Mat roi(img, r);
	//invert color
	bitwise_not(roi, roi);

	// ========== 출력 ============
	//bitwise_not(img, img);
	//imshow("img", img);
	//imshow("img_s", img_s);
	//imshow("imgClone", imgClone);
	//imshow("imgRect", imgRect);
	//imshow("imgCopy", imgCopy);
	//imshow("imgCopy2", imgCopy2);
	//imshow("imgCopy3", imgCopy3);
	//imshow("roi", roi);
	//imshow("img", img);
	// ============================

	waitKey(0);

	return 0;
}