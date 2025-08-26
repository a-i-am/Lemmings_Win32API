#pragma once
#include "Job.h"

class Digger : public Job
{
public:
	void InitAnims(Actor* owner) override;
	void UpdateStateMachine(int deltaTime) override;
	string GetName() override;

	void SetWalkingRight(bool value);
private:
	void Dig();
	bool CanDig();
private:
	enum DiggerState
	{
		DIGGING_STATE
	};


private:
	DiggerState state;

};

