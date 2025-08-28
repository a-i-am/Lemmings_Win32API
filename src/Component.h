#pragma once
#include "pch.h"
// Component.h

class Actor; // 전방 선언

class Component
{
public:
	virtual ~Component() {}

	void setOwner(Actor* owner) { _owner = owner; }
	Actor* getOwner() const { return _owner; }

	virtual void InitComponent() {}
	virtual void UpdateComponent(float deltaTime) {}
	virtual void RenderComponent(HDC hdc, Vector pos) {}

protected:
	Actor* _owner = nullptr;
};
