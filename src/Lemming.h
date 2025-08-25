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
	std::vector<Vector> _debugFrontPoints; // �� �˻� �ȼ���
	std::vector<Vector> _debugFloorPoints;     // �ٴ� �˻� �ȼ���
private:
	// TODO : Job Ŭ������ ���� Job���� ����� �ؼ� �ű⿡ �Ʒ����� ������ ����
	// (_jobSprite->jobSprite->Position() == door->GetEscapePosition())

	bool isSolidWall(Vector nextPos);
	bool isSolid(Vector nextPos);
	int isSolidFloor(Vector nextPos, int maxFall);
	bool outOfMap();
	
	// TODO : Job �����̸���� Ŭ���� ���� �� SpriteRenderer* jobSprite�� ��ü�ϱ�
	Job* _jobSprite;

	SpriteRenderer* _sprite = nullptr;  // ���� ������ ��ü�߿��� ����� ���� ���¸� �׷����ϴ��� ��Ÿ���� ����

	// ���� ������ ��ü
	SpriteRenderer* _spriteMoveRight = nullptr;
	SpriteRenderer* _spriteMoveLeft = nullptr;	
	SpriteRenderer* _spriteDig = nullptr;
	SpriteRenderer* _spriteEscaper = nullptr;

	bool  _isWalkingRight;
	bool _isOnGround = false;
	float _speed = 25.0f;
	float _fallSpeed = 0;

	float _footOffsetY = 23.0f; // �� ��ġ (Sprite ����)
	int _groundClearance = 1;   // �ٴ� �� ���� ���� (�ȼ�)
};