#pragma once

// TODO : Job Ŭ���� ���
#include "Job.h"

class Walker : public Job
{
public:
	void InitAnims(Actor* owner) override;
	void UpdateStateMachine(float deltaTime) override;
	string GetName() override;

	void SetWalkingRight(bool value);

private:
	enum WalkerState
	{
		WALKING_LEFT_STATE, WALKING_RIGHT_STATE, FALLING
	};

private:
	WalkerState state;
};


