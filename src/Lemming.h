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
	SpriteRenderer* _sprite = nullptr;  // ���� ������ ��ü�߿��� ����� ���� ���¸� �׷����ϴ��� ��Ÿ���� ����

	SpriteRenderer* _spriteMoveRight = nullptr;	// ���� ������ ��ü
	SpriteRenderer* _spriteMoveLeft = nullptr;	// ���� ������ ��ü
	SpriteRenderer* _spriteDig = nullptr; // ���� ������ ��ü
	bool  _walkingRight = true;
	float _speed = 50.f;


};