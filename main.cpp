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
		return b;//0
	}
	else if (a >= c)
	{
		return c;//1
	}

	return 0;
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

	Vector2 MousePointStart = { 0,0 };
	Vector2 MousePointEnd = { 0,0 };

	float circle = 30.0f;

	int MouseX = 0;
	int MouseY = 0;


	Vector2 StartPointPlayer = {};
	Vector2 StartEndPoint = {};

	float nbaX = 0;
	float nbaY = 0;

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

		length1 = sqrtf((StartEndPoint.x * StartEndPoint.x) + (StartEndPoint.y * StartEndPoint.y));



		if (length1 != 0.0f) {
			nbaX = (float)sqrt((StartPointPlayer.x * StartPointPlayer.x) - (StartPointPlayer.y * StartPointPlayer.y));
			nbaY = (float)sqrt((StartPointPlayer.x * StartPointPlayer.x) - (StartPointPlayer.y * StartPointPlayer.y));
		}

		e = { nbaX,nbaY };//正規化


		dot = ((e.x * StartPointPlayer.x) + (e.y * StartPointPlayer.y));
		t = dot / length1;

		t = (float)clamp((int)t, (int)0, (int)1);

		Vector2 f = { ((1.0f - t) * MousePointStart.x) + (t * MousePointEnd.x)
			,((1.0f - t) * MousePointStart.y) + (t * MousePointEnd.y) };

		Vector2 cf = { player_->GetPos_().x - f.x , player_->GetScreenY() - f.y };

		float distance = sqrtf((cf.x * cf.x) + (cf.y * cf.y));


		//線の長さ
		//float sen = (float)sqrt(StartEndPoint.x * StartEndPoint.x + StartEndPoint.y * StartEndPoint.y);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		player_->Draw();

		if (distance < player_->GetRadius_() + circle)
		{
			DestanceFlag = true;
			Novice::DrawEllipse(100, 100, 30, 30, 0.0f, WHITE, kFillModeSolid);
		}
		else
		{
			DestanceFlag = false;
			Novice::DrawEllipse(100, 100, 30, 30, 0.0f, BLUE, kFillModeSolid);
		}

		Novice::DrawLine((int)MousePointStart.x, (int)MousePointStart.y, (int)MousePointEnd.x, (int)MousePointEnd.y, WHITE);
		Novice::DrawEllipse((int)MousePointStart.x, (int)MousePointStart.y, 30, 30, 0.0f, WHITE, kFillModeWireFrame);
		Novice::DrawEllipse((int)MousePointEnd.x, (int)MousePointEnd.y, 30, 30, 0.0f, WHITE, kFillModeWireFrame);


		Novice::ScreenPrintf(0, 0, "mouse: %d", MouseX);
		Novice::ScreenPrintf(0, 20, "Start:%f", MousePointStart.x);
		Novice::ScreenPrintf(0, 40, "End:%f", MousePointEnd.x);
		Novice::ScreenPrintf(0, 60, "distance:%f", distance);
		Novice::ScreenPrintf(0, 80, "radius:%f", player_->GetRadius_() + circle);
		Novice::ScreenPrintf(0, 100, "dot:%f", dot);
		Novice::ScreenPrintf(0, 120, "%f", length1);
		Novice::ScreenPrintf(0, 140, "%f", dot / length1);
		Novice::ScreenPrintf(0, 160, "%f", t);
		Novice::ScreenPrintf(0, 180, "%f,%f", e.x, e.y);

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
