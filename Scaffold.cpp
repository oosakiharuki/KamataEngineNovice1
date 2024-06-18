#include "Scaffold.h"

Scaffold::Scaffold(Vector2 LTpos, Vector2 RTpos, Vector2 LBpos, Vector2 RBpos){
	pos_[0] = LTpos;
	pos_[1] = RTpos;
	pos_[2] = LBpos;
	pos_[3] = RBpos;
	ScreenY[4] = {};
	textureHandle = Novice::LoadTexture("white1x1.png");
}


void Scaffold::Updata(){
	for (int i = 0; i < 4; i++) {
		ScreenY[i] = pos_[i].y;
		ScreenY[i] += -500.0f;
		ScreenY[i] *= -1;
	}
}


void Scaffold::Draw() {
	Novice::DrawQuad(
		(int)pos_[0].x, (int)ScreenY[0],
		(int)pos_[1].x, (int)ScreenY[1],
		(int)pos_[2].x, (int)ScreenY[2],
		(int)pos_[3].x, (int)ScreenY[3],
		1, 1, 1, 1, textureHandle, WHITE);
}