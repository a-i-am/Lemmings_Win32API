#pragma once
#include "Terrain.h"
#include "Lemming.h"
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
	virtual	void init();
	virtual void destory();
	virtual void update(float deltaTime);
	virtual void Render(HDC hdc);

protected:
	virtual void eraseMask(int x, int y);
	virtual void applyMask(int x, int y);
	virtual void eraseSpecialMask(int x, int y);
	virtual void applySpecialMask(int x, int y);

	virtual void changePauseStatus();
	virtual void changeSpeedUpStatus();
	virtual bool isPaused();
	virtual bool isSpeedUp();

private:
	Terrain* _terrain = nullptr;
	vector<Lemming> _lemmings;
	Vector _lemmingPos;
};