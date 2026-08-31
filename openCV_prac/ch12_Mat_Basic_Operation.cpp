#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	// Mat::ones : 생성과 동시에 값이 1로 설정됨.
	// Mat::zeros : 생성과 동시에 값이 0으로 설정됨.
	Mat m = Mat::ones(3, 3, CV_64F); 
	m = m * 3;
	cout << "m" << endl << m << endl;

	double dm[3][3] = { {1, 2, 1}, {0, 1, 1}, {1, 0, 1} };
	Mat m2 = Mat(3, 3, CV_64F, dm);

	cout << "m2" << endl << m2 << endl << endl;
	cout << "m + m2" << endl << m + m2 << endl << endl;	// 원소 별 
	cout << "m - m2" << endl << m - m2 << endl << endl;	// 원소 별
	cout << "m * m2" << endl << m * m2 << endl << endl;	// 행렬곱
	cout << "m * m2" << endl << m.mul(m2) << endl << endl; // 원소 별 곱셈을 원하면 m.mul(m2);
	cout << "m / m2" << endl << m / m2 << endl << endl; //	3/0 -> inf(무한대) // 원소 별
	cout << "m2.inv()" << endl << m2.inv() << endl << endl; // 역행렬
	cout << "m2.t()" << endl << m2.t() << endl << endl;		// 전치


	return 0;
}