#pragma once

#include "Job.h"

class Faller : public Job
{
public:
	void InitAnims(Actor* owner) override;
	void UpdateStateMachine(float deltaTime) override;
	string GetName() override;
	SpriteRenderer* GetCurrentJobSprite() const override {
		return fallerSprite;
	}
	void SetWalkingRight(bool value);

protected:
	SpriteRenderer* fallerSprite = nullptr;

private:
	enum FallerState
	{
		FALLING_LEFT_STATE, FALLING_RIGHT_STATE, FALLING_DEATH_STATE
	};

private:
	FallerState state;
	int currentDistance = 0;
	bool dead = false;

	//const SoundManager* soundManager;
	//FMOD::Sound* deathEffect;
};

