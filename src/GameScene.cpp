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
	
	ResourceManager::getInstance()->loadTexture("map", "levels/fun1/map.bmp", -1, 1, 1);
	// 액터 생성
	Actor* map = new Actor();
	map->addComponent<ImageRenderer>("map");
	mapRenderer = map->getComponent<ImageRenderer>(); // 컴포넌트 캐싱
	mapRenderer->getTexture()->setTextureWidth(GWinSizeX);
	mapRenderer->getTexture()->setTextureHeight(GWinSizeY);

	
	map->setPosition(Vector{ GWinSizeX * 0.5f, GWinSizeY * 0.5f }); // 위치 지정
	_actors.push_back(map); // Actor 목록에 저장
}

void GameScene::initSpriteSheets()
{
// trapdoors(배출구) 초기화 
	ResourceManager::getInstance()->loadTexture("trapdoors", "levels/lemming_trapdoors.bmp", RGB(255, 255, 255), 2, 10);
	
	Actor* trapdoors = new Actor();
	
	SpriteRenderer* spriteRenderer = trapdoors->addComponent<SpriteRenderer>("trapdoors", 1.0f);
	trapdoors->setPosition(Vector{ 550, 150 }); // 위치 지정
	
	spriteRenderer->setFrameRange(0, 0, 1, 10); // 2x10 스프라이트 중, 0번 가로 라인만 사용 (세로 10프레임)


// doors(나가는 곳) 초기화
	ResourceManager::getInstance()->loadTexture("doors", "levels/lemming_doors.bmp", RGB(255, 255, 255), 3, 8);
	Actor* doors = new Actor();
	doors->addComponent<SpriteRenderer>("doors", 1.0f);
	doors->setPosition(Vector{ 900, 350 });

	spriteRenderer->setFrameRange(0, 0, 3, 2);


// 레밍 초기화
	ResourceManager::getInstance()->loadTexture("lemming", "lemming_anim.bmp", RGB(255, 255, 255), 16, 14);
	Actor* lemming = new Actor();
	lemming->addComponent<SpriteRenderer>("lemming", 1.0f);
	lemming->setPosition(Vector{ 550, 150 });

	spriteRenderer->setFrameRange(0, 0, 16, 1);
	
	// Actor 목록에 저장
	_actors.push_back(lemming); 
	_actors.push_back(doors); 
	_actors.push_back(trapdoors);
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
	for (Actor* actor : _actors)
	{
		// * 이 구조는 Actor::render(hdc)가 내부적으로 ImageRenderer 또는 SpriteRenderer를 찾아서 그려주는 구조를 전제로 함.
		actor->render(hdc); // 각 actor가 가진 Renderer가 draw 하도록 위임
	}
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
* //	ResourceManager::getInstance()->loadTexture("doors", "levels/lemming_doors.bmp", 1, 1, RGB(255, 255, 255));
//	ResourceManager::getInstance()->loadTexture("doors", "levels/lemming_trapdoors.bmp", 1, 1, RGB(255, 255, 255));
	//trapDoors.setSize(246, 750); //원본x3
*
	//mapTex.render(hdc, mapPos, Vector{ 0, 0 });
	//trapDoors.render(hdc, trapDoorPos, Vector{ 0, 0 });
	//mapRenderer = new ImageRenderer("map");
	//mapPos = Vector{ GWinSizeX * 0.5f, GWinSizeY * 0.5f };
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