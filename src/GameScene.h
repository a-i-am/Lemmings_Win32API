#pragma once

#include "GameState.h"
#include "Actor.h"

class Texture;
class ImageRenderer;

class GameScene : public GameState
{
private:
	std::vector<Actor*> _actors;  // 모든 액터를 저장
	bool paused = false;
	bool speedUp = false;

	ImageRenderer* mapRenderer = nullptr;

	void initSpriteSheets();
	void initImages();

public:
	virtual	void init() ;
	virtual void destory() ;
	virtual void update(int deltaTime) ;
	virtual void render(HDC hdc) ;

protected:
	//virtual void loadResource();
	virtual void updateUI();

	virtual void eraseMask(int x, int y);
	virtual void applyMask(int x, int y);
	virtual void eraseSpecialMask(int x, int y);
	virtual void applySpecialMask(int x, int y);

	virtual void changePauseStatus();
	virtual void changeSpeedUpStatus();
	virtual bool isPaused();
	virtual bool isSpeedUp();
};
/*
	//Texture* mapCut[8] = {};
	Vector mapCutPos[8] = {};

	// 디폴트는 윈도우 사이즈가 맵사이즈, or 텍스처의 사이즈
	//int32 _mapSizeX = ;
	//int32 _mapSizeY = ;


	//int32 _mapCutSizeX = 60;
	//int32 _mapCutSizeY = 95;

	//VariableTexture maskTex;

	//	Vector mapPos;
//	Vector trapDoorPos;
//	Vector doorPos;
*/


