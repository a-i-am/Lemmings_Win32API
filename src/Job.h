#pragma once
#include "Actor.h"
#include "SpriteRenderer.h"
#include "Lemming.h"

class Job
{

public:
	virtual ~Job() {}

	virtual void InitAnims(Actor* owner) = 0;
	virtual void UpdateStateMachine(float deltaTime) = 0;
	virtual SpriteRenderer* GetCurrentJobSprite() const = 0;
	virtual string GetName() = 0;


	//virtual void SetWalkingRight(bool value) = 0;
	void SetWalkingRight(bool value) { isWalkingRight = value; }
	bool GetIsWalkingRight() const { return isWalkingRight; }

	bool IsFinished() { return isFinished; }
	float GetWalkSpeed() { return walkSpeed; }
	float GetFallSpeed() { return fallSpeed; }
	float GetFootOffsetY() { return footOffsetY; }
	int32 GetGroundClearence() { return groundClearance; }
	vector<Vector> GetDebugFrontPoints() { return debugFrontPoints; }
	vector<Vector> GetDebugFloorPoints() { return debugFloorPoints; }
	Job* GetNextJob() { return nextJob; }

protected:
	bool IsCollisionWall(Vector nextPos);
	bool IsCollisionFront(Vector nextPos);
	int32 CollideFloor(Vector nextPos, int32 maxFall);

protected:
	Actor* jobActor;
	Job* nextJob;


	bool  isWalkingRight = true;
	vector<Vector> debugFrontPoints;	 // �� �˻� �ȼ���
	vector<Vector> debugFloorPoints;     // �ٴ� �˻� �ȼ���

	float walkSpeed = 25.0f;
	float fallSpeed = 25.0f;
	float footOffsetY = 23.0f;			// �� ��ġ (Sprite ����)
	int32 groundClearance = 1;			// �ٴ� �� ���� ���� (�ȼ�)

	bool isFinished;
};