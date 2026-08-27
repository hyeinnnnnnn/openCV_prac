#include <opencv2/opencv.hpp>
using namespace cv;

int main(int, char)
{
	VideoCapture cap(0); // 0번 카메라(기본 웹캠) 열기
	if (!cap.isOpened()) return -1;

	Mat edges;	// 결과 담을 이미지
	namedWindow("edges", 1);	// 창 생성

	for (;;)
	{
		Mat frame; 
		cap >> frame; // 카메라에서 한 프레임 읽어 frame에 저장
		cvtColor(frame, edges, COLOR_BGR2GRAY); // 컬러 -> 흑백
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5); // 가우시안 블러(노이즈 제거)
		Canny(edges, edges, 0, 30, 3); // Canny Edge 검출(윤곽선만 추출) -> 경계선(밝기 급변 지점) 검출. 0, 30은 임계값, 3은 커널 크기
		imshow("edges", edges); // 창에 표시
		if (waitKey(30) >= 0)	// 프레임당 30ms 대기 -> 약 초당 33프레임. 이게 있어야 imshow 창이 실제로 그려짐(필수)
			break;				// 키 입력 있으면 [>= 0] 이 참 -> 루프 탈출
	}
	return 0;
}