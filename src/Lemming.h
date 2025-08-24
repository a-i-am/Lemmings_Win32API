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
	void Render(HDC hdc) override;

	void setWalkingRight(bool right);


private:
	enum WalkerState
	{
		WALKING_LEFT_STATE, WALKING_RIGHT_STATE, FALLING_LEFT_STATE, FALLING_RIGHT_STATE
	};
private:
	WalkerState state;
	std::vector<Vector> _debugFrontPoints; // �� �˻� �ȼ���
	std::vector<Vector> _debugFloorPoints;     // �ٴ� �˻� �ȼ���
private:
	int isSolidFloor(Vector nextPos, int maxFall);
	bool isSolid(Vector nextPos);
	bool outOfMap();
	//Job* job;
	SpriteRenderer* _sprite = nullptr;  // ���� ������ ��ü�߿��� ����� ���� ���¸� �׷����ϴ��� ��Ÿ���� ����

	SpriteRenderer* _spriteMoveRight = nullptr;	// ���� ������ ��ü
	SpriteRenderer* _spriteMoveLeft = nullptr;	// ���� ������ ��ü
	SpriteRenderer* _spriteDig = nullptr; // ���� ������ ��ü

	bool  _isWalkingRight;
	bool _isOnGround = false;
	float _speed = 50.f;
};