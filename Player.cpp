#include "Player.h"

Player::Player(float posX, float posY, float speed, float radius) {
	pos_.x = posX;
	pos_.y = posY;
	ScreenY = 0.0f;
	velocity_ = { 0.0f,0.0f };
	aclloration_ = { 0.0f,-0.8f };
	speed_ = speed;
	radius_ = radius;
	JumpFlag_ = false;


	scaffold_[0] = new Scaffold({ 0,0 }, { 300, 0 }, { 0,-100 }, { 300,-100 });
	scaffold_[1] = new Scaffold({ 700,0 }, { 1000, 0 }, { 700,-100 }, { 1000,-100 });

	distance[2] = {};

	SenScreenY = 50;
}

void Player::Updata(char* keys, char* preKeys,bool DFlag,float SenY) {
	ScreenY = pos_.y;
	ScreenY += -500.0f;
	ScreenY *= -1;

	if (keys[DIK_D]) {
		pos_.x += speed_;
	}
	if (keys[DIK_A]) {
		pos_.x -= speed_;
	}
	if (keys[DIK_W] && !preKeys[DIK_W]) {
		JumpFlag_ = true;
		velocity_.y = 20.0f;
	}	

	if (JumpFlag_) {
		velocity_.y += aclloration_.y;
		pos_.y += velocity_.y;
	}
	
	//sikaku no asiba
	//if (pos_.x< scaffold_[0]->pos_[0].x  && scaffold_[0]->pos_[1].x < pos_.x) {
	//	distance[0] = pos_.y - scaffold_[0]->pos_[0].y;
	//	distance[1] = pos_.y - scaffold_[0]->pos_[1].y;
	//}

	//if (distance[0] < radius_ * radius_ || distance[1] > radius_ * radius_) {
	//	velocity_.y = 0;
	//}

	SenScreenY = SenY;
	SenScreenY += -500.0f;
	SenScreenY *= -1;

	if (DFlag == true) {
		velocity_.y = 0;
		aclloration_.y = 0;
		pos_.y = SenScreenY;
	}else {
		aclloration_.y = -0.8f;
	}



	if (pos_.y <= radius_) {
		pos_.y = radius_;
 		JumpFlag_ = false;
	}


	for (int i = 0; i < 2; i++) {
		scaffold_[i]->Updata();
	}
}

void Player::Draw() {
	Novice::DrawEllipse((int)pos_.x,(int)ScreenY,(int)radius_,(int)radius_,0.0f,GREEN,kFillModeSolid);

	for(int i = 0;i< 2;i++){
		scaffold_[i]->Draw();
	}
}