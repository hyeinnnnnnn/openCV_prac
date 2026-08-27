# OpenCV 학습용 테스트 데이터

## images/

| 파일 | 용도 |
|---|---|
| 01_shapes_colors.png | 기본 도형/색상 - 그리기, 색공간 변환 연습 |
| 02_gray_steps.png | 그레이 계단 - threshold 연습 |
| 03_noisy_gaussian.png | 가우시안 노이즈 - GaussianBlur, fastNlMeansDenoising 연습 |
| 04_noisy_saltpepper.png | 소금-후추 노이즈 - medianBlur 연습 |
| 05_hue_gradient.png | Hue 그라디언트 - BGR/HSV 변환 연습 |
| 06_edges_shapes_text.png | 도형+텍스트 - Canny 엣지 검출 연습 |
| 07_contours_shapes.png | 분리된 도형 5개(원/사각/삼각/별/타원) - findContours 연습 |
| 08_colored_objects.png | 색이 다른 공 6개 - HSV inRange 색상 기반 검출 연습 |
| 09_chessboard_flat.png | 정면 체스보드(10x7, 내부 코너 9x6) - findChessboardCorners 연습 |
| 10_chessboard_angle1~3.png | 원근 변환된 체스보드 3장 - calibrateCamera 연습 (여러 각도 필요) |

## videos/ (640x480, 20fps, 8초)

| 파일 | 용도 |
|---|---|
| 01_moving_shapes.mp4 | 움직이는 도형 3개(왕복/반복/원운동) - 객체 트래킹 연습 |
| 02_background_subtraction.mp4 | 고정 배경 + 1초 후 등장하는 이동 객체 - BackgroundSubtractorMOG2/KNN 연습 |
| 03_optical_flow.mp4 | 코너가 뚜렷한 체스보드 패턴이 이동 - Lucas-Kanade/Farneback 옵티컬 플로우 연습 |

생성 스크립트: generate.py (재실행하면 노이즈 이미지는 매번 랜덤하게 새로 생성됨)
