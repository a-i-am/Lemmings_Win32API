// Component.h
#pragma once
#include "pch.h"

class Actor; // 전방 선언

class Component
{
public:
	virtual ~Component() {}

	void setOwner(Actor* owner) { _owner = owner; }
	Actor* getOwner() const { return _owner; }

	virtual void initComponent() {}
	virtual void updateComponent(float deltaTime) {}
	virtual void renderComponent(HDC hdc, Vector pos) {}

protected:
	Actor* _owner = nullptr;
};
