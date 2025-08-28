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
	vector<Vector> debugFrontPoints;	 // 벽 검사 픽셀들
	vector<Vector> debugFloorPoints;     // 바닥 검사 픽셀들

	float walkSpeed = 25.0f;
	float fallSpeed = 25.0f;
	float footOffsetY = 23.0f;			// 발 위치 (Sprite 기준)
	int32 groundClearance = 1;			// 바닥 위 여유 공간 (픽셀)

	bool isFinished;
};