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

	void setWalkingRight(bool right);


private:
	bool _debugDrawCollision = false;
	std::vector<Vector> _debugFloorPoints;
	std::vector<Vector> _debugWallPoints;

private:
	enum WalkerState
	{
		WALKING_LEFT_STATE, WALKING_RIGHT_STATE, FALLING_LEFT_STATE, FALLING_RIGHT_STATE
	};
private:
	WalkerState state;

private:
	int isSolidFloor(int maxFall);
	bool isSolid();
	bool outOfMap();
	//Job* job;
	SpriteRenderer* _sprite = nullptr;  // ���� ������ ��ü�߿��� ����� ���� ���¸� �׷����ϴ��� ��Ÿ���� ����

	SpriteRenderer* _spriteMoveRight = nullptr;	// ���� ������ ��ü
	SpriteRenderer* _spriteMoveLeft = nullptr;	// ���� ������ ��ü
	SpriteRenderer* _spriteDig = nullptr; // ���� ������ ��ü

	bool  _isWalkingRight;
	bool _isOnGround = false;
	float _speed = 50.f;
	
	void toggleDebugDraw() { _debugDrawCollision = false; }
};