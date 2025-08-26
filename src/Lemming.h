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
	// TODO : Job Ŭ������ ���� Job���� ����� �ؼ� �ű⿡ �Ʒ����� ������ ����
	// (_jobSprite->jobSprite->Position() == door->GetEscapePosition())
	bool outOfMap();
	
	// TODO : Job �����̸���� Ŭ���� ���� �� SpriteRenderer* jobSprite�� ��ü�ϱ�
	Job* job;
	SpriteRenderer* _jobSprite = nullptr;  // ���� ������ ��ü�߿��� ����� ���� ���¸� �׷����ϴ��� ��Ÿ���� ����

	// ���� ������ ��ü
	SpriteRenderer* _spriteMoveRight = nullptr;
	SpriteRenderer* _spriteMoveLeft = nullptr;	
	SpriteRenderer* _spriteDig = nullptr;
	SpriteRenderer* _spriteEscape = nullptr;
	SpriteRenderer* _spriteFall = nullptr;

	bool _isWalkingRight = true;
	bool _isOnGround = false;
	float _walkSpeed = 0.f;
	float _fallSpeed = 0.f;
	float _footOffsetY = 0.f; // �� ��ġ (Sprite ����)
	int32 _groundClearance = 0;   // �ٴ� �� ���� ���� (�ȼ�)
};