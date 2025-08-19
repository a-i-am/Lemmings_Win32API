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
	std::vector<Actor*> _actors;  // ��� ���͸� ����
	bool paused = false;
	bool speedUp = false;

	
public:
	virtual	void init() ;
	virtual void destory() ;
	virtual void update(float deltaTime) ;
	virtual void render(HDC hdc) ;

protected:
	//virtual void loadResource();
	virtual void eraseMask(int x, int y);
	virtual void applyMask(int x, int y);
	virtual void eraseSpecialMask(int x, int y);
	virtual void applySpecialMask(int x, int y);

	virtual void changePauseStatus();
	virtual void changeSpeedUpStatus();
	virtual bool isPaused();
	virtual bool isSpeedUp();

private:
	Terrain* _terrain;
	vector<Lemming> _lemmings;
	Vector _lemmingPos;
};



/*
	//Texture* mapCut[8] = {};
	Vector mapCutPos[8] = {};

	// ����Ʈ�� ������ ����� �ʻ�����, or �ؽ�ó�� ������
	//int32 _mapSizeX = ;
	//int32 _mapSizeY = ;


	//int32 _mapCutSizeX = 60;
	//int32 _mapCutSizeY = 95;

	//VariableTexture maskTex;

	//	Vector mapPos;
//	Vector trapDoorPos;
//	Vector doorPos;
*/


