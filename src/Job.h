class Actor;
class SpriteRenderer;
class Lemming;

class Job
{

public:
	virtual void UpdateStateMachine(int deltaTime) = 0;
	virtual void InitAnims(Actor* owner) = 0;
	virtual void SetWalkingRight(bool value) = 0;
	virtual string GetName() = 0;

	bool Finished();
	
	Job* GetNextJob();
	SpriteRenderer* GetJobSprite() { return jobSprite; }
	bool GetIsWalkingRight() { return isWalkingRight; }
	float GetWalkSpeed() { return walkSpeed; }
	float GetFallSpeed() { return fallSpeed; }
	float GetFootOffsetY() { return footOffsetY; }
	int32 GetGroundClearence() { return groundClearance; }
	vector<Vector> GetDebugFrontPoints() { return debugFrontPoints; }
	vector<Vector> GetDebugFloorPoints() { return debugFloorPoints; }


protected:
	bool IsCollisionWall(Vector nextPos);
	bool IsCollisionFront(Vector nextPos);
	int CollideFloor(Vector nextPos, int maxFall);

protected:
	vector<Vector> debugFrontPoints;	 // 벽 검사 픽셀들
	vector<Vector> debugFloorPoints;     // 바닥 검사 픽셀들
	
	bool  isWalkingRight = true;
	float walkSpeed = 25.0f;
	float fallSpeed = 0;
	float footOffsetY = 23.0f;			// 발 위치 (Sprite 기준)
	int32 groundClearance = 1;			// 바닥 위 여유 공간 (픽셀)

	

	bool isFinished;
	Job* nextJob;
	Lemming* lemming;
	SpriteRenderer* jobSprite;
	
};