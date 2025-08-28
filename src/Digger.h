#pragma once
#include "Job.h"

class Digger : public Job
{
public:
	void InitAnims(Actor* owner) override;
	void UpdateStateMachine(float deltaTime) override;
	string GetName() override;
	SpriteRenderer* GetCurrentJobSprite() const override
	{
		return diggerSprite;
	}
	void SetWalkingRight(bool value);

protected: 
	SpriteRenderer* diggerSprite;

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

