#pragma once

#include "Job.h"

class Walker : public Job
{
public:
	void InitAnims(Actor* owner) override;
	void UpdateStateMachine(float deltaTime) override;
	string GetName() override;

	void SetWalkingRight(bool value);
	SpriteRenderer* GetCurrentJobSprite() const override;

protected:
	SpriteRenderer* jobSprite = nullptr;
	SpriteRenderer* jobSprite_rotated = nullptr;

private:
	enum WalkerState
	{
		WALKING_LEFT_STATE, WALKING_RIGHT_STATE, FALLING_STATE, DIGGING_STATE
	};

	WalkerState state;
private:
	void CheckEscape(const Vector& pos);
	bool TryStepOver(Vector& nextPos, bool right);

	void HandleWalking(bool right, float deltaTime, Vector& nextPos);
	void HandleFalling(float deltaTime, Vector& nextPos);
};