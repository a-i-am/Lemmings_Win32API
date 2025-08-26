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
	vector<Vector> debugFrontPoints;	 // �� �˻� �ȼ���
	vector<Vector> debugFloorPoints;     // �ٴ� �˻� �ȼ���
	
	bool  isWalkingRight = true;
	float walkSpeed = 25.0f;
	float fallSpeed = 0;
	float footOffsetY = 23.0f;			// �� ��ġ (Sprite ����)
	int32 groundClearance = 1;			// �ٴ� �� ���� ���� (�ȼ�)

	

	bool isFinished;
	Job* nextJob;
	Lemming* lemming;
	SpriteRenderer* jobSprite;
	
};