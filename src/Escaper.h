#pragma once
#include "Job.h"

class Escaper : public Job
{
public:
	void InitAnims(Actor* owner) override;
	void UpdateStateMachine(float deltaTime) override;
	SpriteRenderer* GetCurrentJobSprite() const override
	{
		return escaperSprite;
	}
	string GetName() override;
	void SetWalkingRight(bool value);
protected:
	SpriteRenderer* escaperSprite;
private:
};

