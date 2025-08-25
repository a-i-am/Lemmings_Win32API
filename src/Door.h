#pragma once
#include "Actor.h"
#include "SpriteRenderer.h"
#include "Texture.h"


class Door : public Actor
{
	using Super = Actor;

public:
	Door(Vector pos);
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;
	Vector GetEscapePosition();
	RECT GetEscapeBounds();

protected:
	// ���� ������ ��ü
	SpriteRenderer* _doorSprite = nullptr;
	SpriteRenderer* _sprite = nullptr;

};

