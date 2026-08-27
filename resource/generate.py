import cv2
import numpy as np
import os

IMG_DIR = "images"
VID_DIR = "videos"
W, H = 640, 480

def save(name, img):
    path = os.path.join(IMG_DIR, name)
    cv2.imwrite(path, img)
    print("saved", path)

# ---------- 1. 기본 이미지 처리 ----------

# 1-1. 도형 + 색상 (기본 그리기/색공간 변환 연습용)
img = np.full((H, W, 3), 255, dtype=np.uint8)
cv2.rectangle(img, (40, 40), (200, 180), (0, 0, 255), -1)      # red
cv2.circle(img, (350, 110), 90, (0, 255, 0), -1)                # green
cv2.ellipse(img, (520, 110), (80, 50), 30, 0, 360, (255, 0, 0), -1)  # blue
pts = np.array([[100, 260], [220, 260], [160, 400]], np.int32)
cv2.fillPoly(img, [pts], (0, 255, 255))                          # yellow triangle
cv2.rectangle(img, (280, 280), (420, 420), (255, 0, 255), -1)    # magenta
cv2.circle(img, (540, 350), 70, (255, 255, 0), -1)               # cyan
save("01_shapes_colors.png", img)

# 1-2. 그레이스케일 계단 (threshold 연습용)
gray_steps = np.zeros((H, W), dtype=np.uint8)
n = 8
step_w = W // n
for i in range(n):
    gray_steps[:, i*step_w:(i+1)*step_w] = int(255 * i / (n - 1))
save("02_gray_steps.png", cv2.cvtColor(gray_steps, cv2.COLOR_GRAY2BGR))

# 1-3. 노이즈 이미지 (blur / denoise 연습용) - base는 도형 이미지
base = img.copy()
gauss = base.astype(np.float32) + np.random.normal(0, 25, base.shape).astype(np.float32)
gauss = np.clip(gauss, 0, 255).astype(np.uint8)
save("03_noisy_gaussian.png", gauss)

sp = base.copy()
prob = 0.02
mask = np.random.rand(H, W)
sp[mask < prob/2] = [0, 0, 0]
sp[mask > 1 - prob/2] = [255, 255, 255]
save("04_noisy_saltpepper.png", sp)

# 1-4. 색상 그라디언트 (HSV 변환 연습용, 무지개)
hsv = np.zeros((H, W, 3), dtype=np.uint8)
for x in range(W):
    hue = int(179 * x / W)
    hsv[:, x, 0] = hue
    hsv[:, x, 1] = 255
    hsv[:, x, 2] = 255
grad_bgr = cv2.cvtColor(hsv, cv2.COLOR_HSV2BGR)
save("05_hue_gradient.png", grad_bgr)

# 1-5. 엣지 검출용 (Canny 연습용) - 텍스트 + 도형
edge_img = np.full((H, W, 3), 255, dtype=np.uint8)
cv2.rectangle(edge_img, (60, 60), (260, 220), (0, 0, 0), 3)
cv2.circle(edge_img, (450, 140), 100, (0, 0, 0), 3)
cv2.line(edge_img, (60, 300), (580, 300), (0, 0, 0), 4)
cv2.putText(edge_img, "OpenCV", (120, 420), cv2.FONT_HERSHEY_SIMPLEX, 2.5, (0, 0, 0), 4)
save("06_edges_shapes_text.png", edge_img)

# ---------- 2. 객체 / 윤곽선 검출 ----------

# 2-1. 뚜렷이 분리된 여러 도형 (findContours 연습용, 검정 배경 + 흰 도형)
cont_img = np.zeros((H, W, 3), dtype=np.uint8)
cv2.circle(cont_img, (100, 100), 60, (255, 255, 255), -1)
cv2.rectangle(cont_img, (220, 40), (360, 160), (255, 255, 255), -1)
tri = np.array([[450, 40], [560, 40], [505, 160]], np.int32)
cv2.fillPoly(cont_img, [tri], (255, 255, 255))
# 오각형(별 대용)
star_pts = []
cx, cy, r_out, r_in = 120, 340, 80, 35
for i in range(10):
    ang = np.pi/2 + i * np.pi / 5
    r = r_out if i % 2 == 0 else r_in
    star_pts.append([cx + r*np.cos(ang), cy - r*np.sin(ang)])
star_pts = np.array(star_pts, np.int32)
cv2.fillPoly(cont_img, [star_pts], (255, 255, 255))
cv2.ellipse(cont_img, (420, 340), (100, 60), 0, 0, 360, (255, 255, 255), -1)
save("07_contours_shapes.png", cont_img)

# 2-2. 색상 기반 객체 검출용 (HSV inRange 연습, 서로 다른 색 공)
color_img = np.full((H, W, 3), (200, 200, 200), dtype=np.uint8)  # 회색 배경
balls = [
    ((110, 120), 55, (0, 0, 255)),    # red
    ((280, 120), 55, (0, 255, 0)),    # green
    ((450, 120), 55, (255, 0, 0)),    # blue
    ((110, 320), 55, (0, 255, 255)),  # yellow
    ((280, 320), 55, (0, 140, 255)),  # orange
    ((450, 320), 55, (255, 0, 255)),  # magenta
]
for (cx, cy), r, color in balls:
    cv2.circle(color_img, (cx, cy), r, color, -1)
    cv2.circle(color_img, (cx, cy), r, (30, 30, 30), 2)
save("08_colored_objects.png", color_img)

# ---------- 3. 카메라 캘리브레이션용 체스보드 ----------

def make_chessboard(cols=10, rows=7, sq=60):
    cb_w, cb_h = cols * sq, rows * sq
    board = np.zeros((cb_h, cb_w), dtype=np.uint8)
    for r in range(rows):
        for c in range(cols):
            if (r + c) % 2 == 0:
                board[r*sq:(r+1)*sq, c*sq:(c+1)*sq] = 255
    return board

board = make_chessboard()
canvas = np.full((H, W), 255, dtype=np.uint8)
bh, bw = board.shape
y0, x0 = (H - bh)//2, (W - bw)//2
canvas[y0:y0+bh, x0:x0+bw] = board
save("09_chessboard_flat.png", cv2.cvtColor(canvas, cv2.COLOR_GRAY2BGR))

# 원근 변환으로 여러 각도 시뮬레이션
canvas_bgr = cv2.cvtColor(canvas, cv2.COLOR_GRAY2BGR)
src_pts = np.float32([[0, 0], [W, 0], [W, H], [0, H]])
perspective_variants = [
    np.float32([[40, 60], [W-30, 10], [W-60, H-20], [80, H-70]]),
    np.float32([[0, 100], [W-120, 0], [W, H], [100, H]]),
    np.float32([[80, 0], [W, 40], [W-60, H], [20, H-40]]),
]
for i, dst_pts in enumerate(perspective_variants, start=1):
    Mp = cv2.getPerspectiveTransform(src_pts, dst_pts)
    warped = cv2.warpPerspective(canvas_bgr, Mp, (W, H), borderValue=(255, 255, 255))
    save(f"10_chessboard_angle{i}.png", warped)

print("=== 이미지 생성 완료 ===")

# ---------- 4. 동영상 ----------

def writer(name, fps=20):
    path = os.path.join(VID_DIR, name)
    fourcc = cv2.VideoWriter_fourcc(*"mp4v")
    return cv2.VideoWriter(path, fourcc, fps, (W, H)), path

# 4-1. 이동하는 도형 (트래킹 / 옵티컬 플로우 연습용)
fps = 20
duration = 8
n_frames = fps * duration
vw, path = writer("01_moving_shapes.mp4", fps)
for i in range(n_frames):
    frame = np.full((H, W, 3), 40, dtype=np.uint8)
    t = i / n_frames
    # 원: 좌우로 왕복
    cx = int(W/2 + (W/2 - 80) * np.sin(2*np.pi*t*1.0))
    cy = 150
    cv2.circle(frame, (cx, cy), 40, (0, 0, 255), -1)
    # 사각형: 대각선 이동 (반복)
    sx = int((i * 6) % (W + 100)) - 50
    sy = 300
    cv2.rectangle(frame, (sx, sy), (sx+60, sy+60), (0, 255, 0), -1)
    # 삼각형: 원운동
    tcx = int(W/2 + 150*np.cos(2*np.pi*t*1.5))
    tcy = int(H/2 + 150*np.sin(2*np.pi*t*1.5))
    tri = np.array([[tcx, tcy-25], [tcx-25, tcy+20], [tcx+25, tcy+20]], np.int32)
    cv2.fillPoly(frame, [tri], (255, 0, 0))
    cv2.putText(frame, f"frame {i}", (10, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,255,255), 1)
    vw.write(frame)
vw.release()
print("saved", path)

# 4-2. 배경 제거 연습용 (정적 배경 + 중간부터 등장하는 움직이는 객체)
vw, path = writer("02_background_subtraction.mp4", fps)
# 텍스처 있는 정적 배경 생성 (고정 시드)
rng = np.random.RandomState(42)
static_bg = np.full((H, W, 3), 90, dtype=np.uint8)
for _ in range(150):
    x, y = rng.randint(0, W), rng.randint(0, H)
    r = rng.randint(5, 15)
    c = tuple(int(v) for v in rng.randint(60, 160, size=3))
    cv2.circle(static_bg, (x, y), r, c, -1)
n_frames = fps * duration
for i in range(n_frames):
    frame = static_bg.copy()
    # 처음 1초는 배경만 (배경 모델 학습 구간)
    if i > fps * 1:
        t = (i - fps*1) / (n_frames - fps*1)
        x = int(-80 + (W + 160) * t)
        y = int(H/2 + 80*np.sin(2*np.pi*t*3))
        cv2.circle(frame, (x, y), 35, (0, 0, 255), -1)
    vw.write(frame)
vw.release()
print("saved", path)

# 4-3. 옵티컬 플로우 연습용 (코너가 뚜렷한 체스보드 패턴이 이동)
vw, path = writer("03_optical_flow.mp4", fps)
cb = make_chessboard(cols=6, rows=5, sq=70)
cb_bgr = cv2.cvtColor(cb, cv2.COLOR_GRAY2BGR)
bh, bw = cb.shape[:2]
n_frames = fps * duration
for i in range(n_frames):
    frame = np.full((H, W, 3), 200, dtype=np.uint8)
    t = i / n_frames
    x = int((W - bw) * (0.5 + 0.5*np.sin(2*np.pi*t*0.7)))
    y = int((H - bh) * (0.5 + 0.5*np.cos(2*np.pi*t*0.5)))
    x = max(0, min(W-bw, x))
    y = max(0, min(H-bh, y))
    frame[y:y+bh, x:x+bw] = cb_bgr
    vw.write(frame)
vw.release()
print("saved", path)

print("=== 동영상 생성 완료 ===")
