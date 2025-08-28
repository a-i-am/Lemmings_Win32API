#include "pch.h"
#include "Door.h"
#include "Game.h"
#include "GameScene.h"


Door::Door(Vector pos) : Super(pos)
{
	_doorSprite = CreateSpriteComponent("doors", 1.0f, 40 * 3.f, 32 * 3.f);
	_doorSprite->SetAllDoorsAnimationData(0, 6, true, false);

	_sprite = _doorSprite;
}

void Door::Update(float deltaTime)
{
	GameScene* gameScene = Game::getGameScene();
	if (!gameScene || !gameScene->GetTerrain()) return;

	_sprite->UpdateComponent(deltaTime);
}

void Door::Render(HDC hdc)
{
	if (_sprite)
	{
		_sprite->RenderComponent(hdc, _pos);
	}
}

Vector Door::GetEscapePosition()
{
	return _pos;
}

// WinAPI RECT + �ϴ� �Ա� ���� ��ȯ
RECT Door::GetEscapeBounds()
{
	float width = 5.0f;       // �� ��������Ʈ ��
	float height = 32 * 3.0f;      // �� ��������Ʈ ����
	float entranceHeight = 10.0f;  // �Ա� ���� ����

	RECT rect;
	float offsetX = 5.5f;
	rect.left = static_cast<LONG>(_pos.x - width * 0.5f + offsetX);
	rect.right = static_cast<LONG>(_pos.x + width * 0.5f + offsetX);

	rect.top = static_cast<LONG>(_pos.y + height * 0.5f - entranceHeight);
	rect.bottom = rect.top + static_cast<LONG>(entranceHeight);

	return rect;
}

