#pragma once

#include "Actor.h"
#include "SpriteRenderer.h"
#include "Job.h"

class Door;

//#include <memory>

class Lemming : public Actor
{
	using Super = Actor;

public:
	Lemming(Vector pos);
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;

	void setWalkingRight(bool right);


private:
	enum WalkerState
	{
		WALKING_LEFT_STATE, WALKING_RIGHT_STATE, FALLING
	};
private:
	WalkerState state;
	std::vector<Vector> _debugFrontPoints; // 벽 검사 픽셀들
	std::vector<Vector> _debugFloorPoints;     // 바닥 검사 픽셀들
private:
	// TODO : Job 클래스의 하위 Job에서 상속을 해서 거기에 아래같은 내용을 구현
	// (_jobSprite->jobSprite->Position() == door->GetEscapePosition())

	bool isSolidWall(Vector nextPos);
	bool isSolid(Vector nextPos);
	int isSolidFloor(Vector nextPos, int maxFall);
	bool outOfMap();
	
	// TODO : Job 동작이름대로 클래스 만들 때 SpriteRenderer* jobSprite로 대체하기
	Job* _jobSprite;

	SpriteRenderer* _sprite = nullptr;  // 원본 생성된 객체중에서 현재는 무슨 상태를 그려야하는지 나타내는 변수

	// 원본 생성된 객체
	SpriteRenderer* _spriteMoveRight = nullptr;
	SpriteRenderer* _spriteMoveLeft = nullptr;	
	SpriteRenderer* _spriteDig = nullptr;
	SpriteRenderer* _spriteEscaper = nullptr;

	bool  _isWalkingRight;
	bool _isOnGround = false;
	float _speed = 25.0f;
	float _fallSpeed = 0;

	float _footOffsetY = 23.0f; // 발 위치 (Sprite 기준)
	int _groundClearance = 1;   // 바닥 위 여유 공간 (픽셀)
};