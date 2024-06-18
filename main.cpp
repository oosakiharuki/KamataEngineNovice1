#include <Novice.h>
#include "Player.h"
#include"Vector2.h"
#define _USE_MATH_DEFINES
#include <math.h>

int clamp(int a, int b, int c)// t,0,1
{	
	if (a > b || a < c)
	{
		return a;//t
	}
	else if (a <= b)
	{
		return a;//0
	}
	else if (a >= c)
	{
		return a;//1
	}

	return a;
}

float Dot(const Vector2& v1, const Vector2& v2) {
	float result;
	result = (v1.x * v2.x) + (v1.y * v2.y);
	return result;
}

float Length(const Vector2& v) {
	float result;
	result = (float)sqrt((v.x * v.x) + (v.y * v.y));
	return result;
}

Vector2 Normalize(const Vector2& v) {
	Vector2 result;
	result.x = v.x / (float)sqrt((v.x * v.x) + (v.y * v.y));
	result.y = v.y / (float)sqrt((v.x * v.x) + (v.y * v.y));
	return result;
}

const char kWindowTitle[] = "LC1B_03_オオサキ_ハルキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Player* player_ = new Player(100.0f, 0.0f, 5.0f, 20.0f);

	Vector2 MousePointStart = { 100,200 };
	Vector2 MousePointEnd = { 500,200 };

	float circle = 30.0f;

	int MouseX = 0;
	int MouseY = 0;


	Vector2 StartPointPlayer = {};
	Vector2 StartEndPoint = {};

	//float nbaX = 0;
	//float nbaY = 0;

	float t = 0;

	bool DestanceFlag = false;

	float length1;
	Vector2 e;
	float dot;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		player_->Updata(keys, preKeys, DestanceFlag, MousePointStart.y);

		Novice::GetMousePosition(&MouseX, &MouseY);

		if (Novice::IsTriggerMouse(0)) {
			MousePointStart.x = (float)MouseX;
			MousePointStart.y = (float)MouseY;
		}

		if (Novice::IsPressMouse(0)) {
			MousePointEnd.x = (float)MouseX;
			MousePointEnd.y = (float)MouseY;

		}

		StartPointPlayer = { player_->GetPos_().x - MousePointStart.x,player_->GetScreenY() - MousePointStart.y };
		StartEndPoint = { MousePointEnd.x - MousePointStart.x,MousePointEnd.y - MousePointStart.y };

		//nbaX = StartEndPoint.x;
		//nbaY = StartEndPoint.y;

		length1 = Length(StartEndPoint);

		e = Normalize(StartEndPoint);//正規化

		dot = Dot(StartPointPlayer,e);
		t = dot / length1;

		//t = (float)clamp((int)t, (int)0, (int)1);

		Vector2 f = { ((1.0f - t) * MousePointStart.x) + (t * MousePointEnd.x)
			,((1.0f - t) * MousePointStart.y) + (t * MousePointEnd.y) };

		Vector2 cf = { player_->GetPos_().x - f.x , player_->GetScreenY() - f.y };

		float distance = Length(cf);


		//線の長さ
		//float sen = (float)sqrt(StartEndPoint.x * StartEndPoint.x + StartEndPoint.y * StartEndPoint.y);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		player_->Draw();

		if (t < 0 || t > 1)
		{
			DestanceFlag = false;
			Novice::DrawEllipse(1000, 100, 30, 30, 0.0f,RED, kFillModeSolid);
		}
		else if (distance < player_->GetRadius_() + circle)
		{
			DestanceFlag = true;
			Novice::DrawEllipse(1000, 100, 30, 30, 0.0f, WHITE, kFillModeSolid);
		}
		else
		{
			DestanceFlag = false;
			Novice::DrawEllipse(1000, 100, 30, 30, 0.0f, BLUE, kFillModeSolid);
		}

		Novice::DrawLine((int)MousePointStart.x, (int)MousePointStart.y, (int)MousePointEnd.x, (int)MousePointEnd.y, WHITE);
		Novice::DrawEllipse((int)MousePointStart.x, (int)MousePointStart.y, 30, 30, 0.0f, WHITE, kFillModeWireFrame);
		Novice::DrawEllipse((int)MousePointEnd.x, (int)MousePointEnd.y, 30, 30, 0.0f, WHITE, kFillModeWireFrame);


		Novice::ScreenPrintf(0, 0, "mouse: %d", MouseY);
		Novice::ScreenPrintf(0, 20, "Start:%f", MousePointStart.y);
		Novice::ScreenPrintf(0, 40, "End:%f", MousePointEnd.y);
		Novice::ScreenPrintf(0, 60, "distance:%f", distance);
		Novice::ScreenPrintf(0, 80, "radius:%f", player_->GetRadius_() + circle);
		Novice::ScreenPrintf(0, 100, "dot:%f", dot);
		Novice::ScreenPrintf(0, 120, "length1:%f", length1);
		Novice::ScreenPrintf(0, 140, "dot / length1:%f", dot / length1);
		Novice::ScreenPrintf(0, 160, "t :%f", t);
		Novice::ScreenPrintf(0, 180, " e.x, e.y :%f,%f", e.x, e.y);
		Novice::ScreenPrintf(0, 200, " f.x, f.y :%f,%f", f.x, f.y);

		Novice::ScreenPrintf(0, 400, " %f", (float)clamp((int)t, (int)0, (int)1));

		


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
