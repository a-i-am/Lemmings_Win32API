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

	// TODO : Job Ŭ������ ���� Job���� ����� �ؼ� �ű⿡ �Ʒ����� ������ ����
	// (_jobSprite->jobSprite->Position() == door->GetEscapePosition())
private:
	bool IsOutOfMap();
private:
	// TODO : Job �����̸���� Ŭ���� ���� �� SpriteRenderer* jobSprite�� ��ü�ϱ�
	Job* job;
	SpriteRenderer* _jobSprite = nullptr;  // ���� ������ ��ü�߿��� ����� ���� ���¸� �׷����ϴ��� ��Ÿ���� ����
	//Countdown* countdown;

	bool _isWalkingRight = true;
	bool _isAlive;
	bool _isSaved;
	bool _isOnGround = false;

	float _walkSpeed = 0.f;
	float _fallSpeed = 0.f;
	float _footOffsetY = 0.f; // �� ��ġ (Sprite ����)
	int32 _groundClearance = 0;   // �ٴ� �� ���� ���� (�ȼ�)
};