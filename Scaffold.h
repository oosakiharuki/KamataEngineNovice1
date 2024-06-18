#pragma once
#include <Novice.h>
#include"Vector2.h"

class Scaffold
{
public:
	Scaffold(Vector2 LTpos, Vector2 RTpos, Vector2 LBpos, Vector2 RBpos);
	void Updata();
	void Draw();

//private:
	Vector2 pos_[4];
	float ScreenY[4];
	int textureHandle;
};

