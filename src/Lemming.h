#pragma once
#include "Actor.h"
#include "SpriteRenderer.h"
//#include "Countdown.h"

class Job;
class Door;

//#include <memory>

class Lemming : public Actor
{
	using Super = Actor;

public:
	Lemming(Vector pos);

	void Update(float deltaTime) override;
	void Render(HDC hdc) override;
	
	void SetWalkingRight(bool value);
	bool GetIsWalkingRight() { return  _isWalkingRight; }
	bool GetIsDead()  { return !_isAlive; }
	bool GetIsSaved() { return _isSaved; }
	Vector GetPosition() { return _pos; }
	Job* GetJob() { return job; }
	void ChangeJob(Job* nextJob);
	void WriteDestiny();

	// TODO : Job 클래스의 하위 Job에서 상속을 해서 거기에 아래같은 내용을 구현
	// (_jobSprite->jobSprite->Position() == door->GetEscapePosition())
private:
	bool IsOutOfMap();
private:
	// TODO : Job 동작이름대로 클래스 만들 때 SpriteRenderer* jobSprite로 대체하기
	Job* job;
	SpriteRenderer* _jobSprite = nullptr;  // 원본 생성된 객체중에서 현재는 무슨 상태를 그려야하는지 나타내는 변수
	//Countdown* countdown;

	bool _isWalkingRight = true;
	bool _isAlive;
	bool _isSaved;
	bool _isOnGround = false;

	float _walkSpeed = 0.f;
	float _fallSpeed = 0.f;
	float _footOffsetY = 0.f; // 발 위치 (Sprite 기준)
	int32 _groundClearance = 0;   // 바닥 위 여유 공간 (픽셀)
};