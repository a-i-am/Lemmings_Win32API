#include "pch.h"
//#include <cmath>
//#include <ctime>

#include "Game.h"
#include "GameScene.h"
#include "GameState.h"

#include "Texture.h"
#include "SpriteRenderer.h"
#include "ImageRenderer.h"
#include "ResourceManager.h"

#include "ParticleSystemManager.h"
#include "StateManager.h"

#include "SceneMouseManager.h"
#include "SceneKeyboardManager.h"
#include "Scroller.h"
#include "Cursor.h"

#include "HardMaskManager.h"
#include "EasyMaskManager.h"

// 맵 데이터 리셋
/*
* GameScene::GameScene()
{
	map = NULL;
}
GameScene::~GameScene()
{
	if (map != NULL)
		delete map;
}
*/

void GameScene::init()
{
	keyboardManager = &SceneKeyboardManager::getInstance();
	mouseManager = &SceneMouseManager::getInstance();

	initImages();
	initSpriteSheets();
}

void GameScene::initImages()
{
	// 맵 초기화 
	// ex : ResourceManager::GetInstance()->LoadTexture("Effect_Crash", "Effect_Crash.bmp", RGB(0, 0, 0), 3, 1);
	ResourceManager::getInstance()->loadTexture("map", "levels/fun1/map.bmp", RGB(255, 255, 255), 1, 1);
	mapRenderer = new ImageRenderer("map");
	mapPos = Vector{ GWinSizeX * 0.5f, GWinSizeY * 0.5f };
}



void GameScene::initSpriteSheets()
{
//	ResourceManager::getInstance()->loadTexture("doors", "levels/lemming_doors.bmp", 1, 1, RGB(255, 255, 255));
//	ResourceManager::getInstance()->loadTexture("doors", "levels/lemming_trapdoors.bmp", 1, 1, RGB(255, 255, 255));
}

void GameScene::destory()
{
}

void GameScene::update(int deltaTime)
{
}

void GameScene::updateUI()
{
}

void GameScene::render(HDC hdc)
{
	//mapTex.render(hdc, mapPos, Vector{ 0, 0 });
	//trapDoors.render(hdc, trapDoorPos, Vector{ 0, 0 });

}


//GameScene* GameScene::getGameScene()
//{
//	return dynamic_cast<GameScene*>(Game::getInstance()->GetCurrScene());
//}


//void GameScene::loadResource()
//{
	// 씬마다 필요한 텍스처를 정해서 로딩한다.
	/*
	ResourceManager::GetInstance()->LoadTexture("BG", L"BG.bmp", -1);
	ResourceManager::GetInstance()->LoadTexture("Player", L"Player.bmp", RGB(252, 0, 255));
	ResourceManager::GetInstance()->LoadTexture("Enemy1", L"Enemy1.bmp", RGB(255, 0, 255));
	ResourceManager::GetInstance()->LoadTexture("Enemy2", L"Enemy2.bmp", RGB(255, 0, 255));
	ResourceManager::GetInstance()->LoadTexture("Enemy3", L"Enemy3.bmp", RGB(255, 0, 255));
	ResourceManager::GetInstance()->LoadTexture("Enemy4", L"Enemy4.bmp", RGB(255, 0, 255));
	ResourceManager::GetInstance()->LoadTexture("PlayerBullet", L"PlayerBullet.bmp", RGB(252, 0, 255));
	ResourceManager::GetInstance()->LoadTexture("PlayerHP", L"PlayerHP.bmp", RGB(252, 0, 255));

	ResourceManager::GetInstance()->LoadTexture("EnemyBullet", L"EnemyBullet.bmp", -1, 5, 1);
	ResourceManager::GetInstance()->LoadTexture("Explosion", L"explosion.bmp", RGB(0, 0, 0), 6, 2);
	ResourceManager::GetInstance()->LoadTexture("Effect_Crash", L"Effect_Crash.bmp", RGB(0, 0, 0), 3, 1);
	*/
//}


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















/*

//mapTex.load(L"levels/fun1/map.bmp", 1, 1, RGB(255, 255, 255));
//mapTex.setSize(GWinSizeX, GWinSizeY);
//mapPos = Vector{ GWinSizeX * 0.5f , GWinSizeY * 0.5f };

//// 레밍 배출 입구 초기화
//Game::spriteSheets().trapdoorSprites.load(L"levels/lemming_trapdoors.bmp", 1, 1, RGB(255, 255, 255));
//trapDoors.setSize(246, 750); //원본x3
//trapDoorPos = Vector{ 600, 600 };

	// 맵 마스크 초기화
	//maskTex.load(L"levels/fun1/mask.bmp", RGB(255, 255, 255));

	
	// 맵 자른 이미지 초기화

	//mapTex.load(L"levels/fun1/batch_map_cut.bmp", 1, 1, RGB(255, 255, 255));
	for (int i = 0; i < 7; i++)
	{
		std::wstring fileName = L"levels/fun1/batch_g" + std::to_wstring(i + 1) + L".bmp";

		mapCut[i] = new Texture(); // 메모리 할당(생성자 호출)


		mapCut[i]->load(fileName.c_str(), 1, 1, RGB(255, 255, 255));

		mapCutPos[i] = Vector{ 410.0f + static_cast<float>(_mapCutSizeX) * i,
							   250.0f };

		mapCut[i]->setSize(_mapCutSizeX, _mapCutSizeY);
	}

		// 자른 지형 렌더링
	for (int i = 0; i < 7; i++)
	{
		mapCut[i]->render(hdc, mapCutPos[i], Vector{0, 0});
	}

	//mapCut[1]->render(hdc, mapCutPos[0], Vector{ 0, 0 });
*/