//#include <cmath>
//#include <ctime>
#include "pch.h"

#include "Game.h"
#include "GameScene.h"
#include "GameState.h"

#include "Texture.h"
#include "SpriteRenderer.h"
#include "ImageRenderer.h"
#include "ResourceManager.h"

#include "SceneMouseManager.h"
#include "SceneKeyboardManager.h"
#include "Scroller.h"
#include "Cursor.h"

#include "HardMaskManager.h"
#include "EasyMaskManager.h"


void GameScene::destory()
{

}

void GameScene::init()
{
	keyboardManager = &SceneKeyboardManager::getInstance();
	mouseManager = &SceneMouseManager::getInstance();
	
	// TODO : 지금은 생성할 때 _pos로 조정하지만, 스크롤러 만들 때 카메라 위치로 맞추기
	_terrain = new Terrain(Vector{ GWinSizeX * 0.5f , GWinSizeY * 0.5f});
	_actors.push_back(_terrain);

	Actor* trapdoors = new Actor(Vector{ 540.f, 150.f });
	trapdoors->CreateSpriteComponent("trapdoors", 1.0f, 41 * 3.f, 25 * 3.f);
	trapdoors->getComponent<SpriteRenderer>()->setAnimationClip(0, 10);
	_actors.push_back(trapdoors);

	_door = new Door(Vector{ 875.f, 335.f });
	_actors.push_back(_door);

	_lemmingPos = { 820.f, 325.f };
	Lemming* lemming = new Lemming(_lemmingPos);
	_actors.push_back(lemming);
}

void GameScene::update(float deltaTime)
{
	for (Actor* actor : _actors)
	{
		actor->Update(deltaTime);
	}
}

void GameScene::Render(HDC hdc)
{
	for (Actor* actor : _actors)
	{
		//lemming->Render(hdc);
		actor->Render(hdc);
	}
}

void GameScene::changePauseStatus()
{
}

void GameScene::changeSpeedUpStatus()
{
}

bool GameScene::isPaused()
{
	return false;
}

bool GameScene::isSpeedUp()
{
	return false;
}

void GameScene::eraseMask(int x, int y)
{
}

void GameScene::applyMask(int x, int y)
{

}

void GameScene::eraseSpecialMask(int x, int y)
{
}

void GameScene::applySpecialMask(int x, int y)
{
}