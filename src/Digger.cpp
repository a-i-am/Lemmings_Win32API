#include "pch.h"
#include "Digger.h"
#include "Game.h"
#include "Scene.h"
#include "JobFactory.h"

enum DiggerAnims
{
	DIGGER
};

void Digger::InitAnims(Actor* owner)
{
	jobSprite = owner->CreateSpriteComponent("lemming", 1.0f, 16 * 3.f, 14 * 3.f);
	jobSprite->SetLemmingAnimationData(0, 9, 8, false, true);

	state = DIGGING_STATE;
}

void Digger::UpdateStateMachine(float deltaTime)
{
}

void Digger::SetWalkingRight(bool value)
{
	isWalkingRight = value;
}

string Digger::GetName()
{
	return string();
}

void Digger::Dig()
{
}

bool Digger::CanDig()
{
	return false;
}
