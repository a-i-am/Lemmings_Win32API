#pragma once

#include "Actor.h"
#include "Collider.h"
#include "SpriteRenderer.h"
#include "Job.h"
//#include <memory>

class Lemming : public Actor
{
	using Super = Actor;
public:
	Lemming(Vector pos);
	void update(float deltaTime) override;
	void render(HDC hdc) override;

	void setSprite(SpriteRenderer* sprite) { _sprite = sprite;  }
	bool isWalkingRight();
	void setWalkingRight(bool right);

private:
	bool outOfMap();
	//Job* job;
	Collider* _collider = nullptr;
	SpriteRenderer* _sprite = nullptr;
	bool  _walkingRight = true;
	float _speed = 50.f;


};