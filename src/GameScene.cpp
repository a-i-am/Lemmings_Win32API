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
	
	_terrain = new Terrain(Vector{ GWinSizeX * 0.5f, GWinSizeY * 0.5f });
	_terrain->load();
	_actors.push_back(_terrain);

	Actor* trapdoors = new Actor(Vector{ 550, 130 });
	trapdoors->CreateSpriteComponent("trapdoors", 1.0f, 41 * 3.f, 25 * 3.f);
	trapdoors->getComponent<SpriteRenderer>()->setAnimationClip(0, 10);
	_actors.push_back(trapdoors);

	Actor* doors = new Actor(Vector{ 855, 320 });
	doors->CreateSpriteComponent("doors", 1.0f, 40 * 3.f, 32 * 3.f);
	doors->getComponent<SpriteRenderer>()->setAnimationClip(0, 6);
	_actors.push_back(doors);

	_lemmingPos = { 400.0f, 220.0f };
	Lemming* lemming = new Lemming(Vector{ _lemmingPos });

	_actors.push_back(lemming);



}

void GameScene::update(float deltaTime)
{
	/*for (auto& lemming : _lemmings)
	{

	}*/
	Vector lemmingLocalPos = _terrain->worldToLocal(_lemmingPos.x, _lemmingPos.y);
	//if (_terrain->isSolid(static_cast<int>(lemmingLocalPos.x), static_cast<int>(lemmingLocalPos.y)))
	{

	}
	for (Actor* actor : _actors)
	{
		actor->update(deltaTime);
	}
}

void GameScene::render(HDC hdc)
{
	/*for (auto& lemming : _lemmings)
	{
		lemming->render(hdc);
	
	}*/
	for (Actor* actor : _actors)
	{
		//lemming->render(hdc);
		actor->render(hdc);
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