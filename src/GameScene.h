#pragma once
#include "Terrain.h"
#include "Lemming.h"
#include "Door.h"
#include "ResourceManager.h"
#include "GameState.h"
#include "Actor.h"

class Texture;
class ImageRenderer;
class SpriteRenderer;

class GameScene : public GameState
{
private:
	std::vector<Actor*> _actors;  // 모든 액터를 저장
	bool paused = false;
	bool speedUp = false;

public:
	Terrain* GetTerrain() { return _terrain; }
	Door* GetDoor() const { return _door; }

	virtual	void Init();
	virtual void destory();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);

protected:
	virtual void eraseMask(int32 x, int32 y);
	virtual void applyMask(int32 x, int32 y);
	virtual void eraseSpecialMask(int32 x, int32 y);
	virtual void applySpecialMask(int32 x, int32 y);

	virtual void changePauseStatus();
	virtual void changeSpeedUpStatus();
	virtual bool isPaused();
	virtual bool isSpeedUp();

private:
	Door* _door = nullptr;
	Terrain* _terrain = nullptr;
	vector<Lemming> _lemmings;
	Vector _lemmingPos;
};