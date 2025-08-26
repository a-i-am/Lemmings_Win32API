#pragma once

#include "Job.h"

class Faller : public Job
{
public:
	void InitAnims(Actor* owner) override;
	void UpdateStateMachine(int deltaTime) override;
	string GetName() override;

	void SetWalkingRight(bool value);
};

