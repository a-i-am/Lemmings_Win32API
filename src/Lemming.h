#pragma once

#include "Actor.h"
#include "SpriteRenderer.h"
#include "Job.h"
//#include <memory>

class Lemming : public Actor
{
	using Super = Actor;
public:
	Lemming(Vector pos);
	void update(float deltaTime) override;
	void render(HDC hdc) override;

	bool isWalkingRight();
	void setWalkingRight(bool right);



private:
	bool isSolid(Vector nextPos);
	bool outOfMap();
	//Job* job;
	SpriteRenderer* _sprite = nullptr;  // 원본 생성된 객체중에서 현재는 무슨 상태를 그려야하는지 나타내는 변수

	SpriteRenderer* _spriteMoveRight = nullptr;	// 원본 생성된 객체
	SpriteRenderer* _spriteMoveLeft = nullptr;	// 원본 생성된 객체
	SpriteRenderer* _spriteDig = nullptr; // 원본 생성된 객체
	bool  _walkingRight = true;
	float _speed = 50.f;


};