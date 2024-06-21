#pragma once
#include <Novice.h>
#include"Vector2.h"
#include "Scaffold.h"

class Player
{
public:
	Player(float posX,float posY,float speed, float radius);
	void Updata(char* keys, char* preKeys , bool DFlag , float SenY);
	void Draw();
	Vector2 GetPos_() { return pos_; }
	float GetScreenY() { return ScreenY; }
	float GetRadius_() { return radius_; }

private:
	Vector2 pos_;
	float ScreenY;
	Vector2 velocity_;
	float velocityMaxY;
	Vector2 aclloration_;
	float speed_;
	float radius_;
	bool JumpFlag_;
	bool fallFlag_;

	Scaffold* scaffold_[2];
	float distance[2];

	float SenScreenY;
};

