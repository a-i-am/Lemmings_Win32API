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
	bool IsWalkingRight();
	void SetWalkingRight(bool value);
	Vector GetPosition() { return _pos; }


private:
	// TODO : Job 클래스의 하위 Job에서 상속을 해서 거기에 아래같은 내용을 구현
	// (_jobSprite->jobSprite->Position() == door->GetEscapePosition())
	bool outOfMap();
	
	// TODO : Job 동작이름대로 클래스 만들 때 SpriteRenderer* jobSprite로 대체하기
	Job* job;
	SpriteRenderer* _jobSprite = nullptr;  // 원본 생성된 객체중에서 현재는 무슨 상태를 그려야하는지 나타내는 변수

	// 원본 생성된 객체
	SpriteRenderer* _spriteMoveRight = nullptr;
	SpriteRenderer* _spriteMoveLeft = nullptr;	
	SpriteRenderer* _spriteDig = nullptr;
	SpriteRenderer* _spriteEscape = nullptr;
	SpriteRenderer* _spriteFall = nullptr;

	bool _isWalkingRight = true;
	bool _isOnGround = false;
	float _walkSpeed = 0.f;
	float _fallSpeed = 0.f;
	float _footOffsetY = 0.f; // 발 위치 (Sprite 기준)
	int32 _groundClearance = 0;   // 바닥 위 여유 공간 (픽셀)
};