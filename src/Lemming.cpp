#include "pch.h"
#include "Lemming.h"
#include "ResourceManager.h"
#include "Game.h"
#include "GameScene.h"



Lemming::Lemming(Vector pos) : Super(pos) 
{
	_spriteMoveRight = CreateSpriteComponent("lemming", 1.0f, 16 * 3.f, 14 * 3.f);
	_spriteMoveRight->setAnimationClip(0, 10);

	_spriteMoveLeft = CreateSpriteComponent("rotated_lemming", 1.0f, 16 * 3.f, 14 * 3.f);
	_spriteMoveLeft->setAnimationClip(6, 15);

	// 땅파는 모션
	//_spriteDig = CreateSpriteComponent("lemming", 1.0f, 16 * 3.f, 14 * 3.f);
	//_spriteDig->setAnimationClip(0, 8);
	_spriteMoveRight->getTexture()->GenerateCollisionData(256, 224);
	_spriteMoveLeft->getTexture()->GenerateCollisionData(256, 224);

	setWalkingRight(true);
	_sprite = _spriteMoveRight;
}

enum WalkerAnims
{
	WALKING_LEFT, WALKING_RIGHT
};

void Lemming::setWalkingRight(bool value)
{
	_isWalkingRight = value;

	if (_isWalkingRight) {
		state = WALKING_RIGHT_STATE;

		if(_sprite != _spriteMoveRight) 
		_sprite = _spriteMoveRight;
	}
	else {
		state = WALKING_LEFT_STATE;

		if (_sprite != _spriteMoveLeft)
			_sprite = _spriteMoveLeft;

	}
}

void Lemming::update(float deltaTime)
{
	GameScene* gameScene = Game::getGameScene();
	if (!gameScene || !gameScene->GetTerrain()) return;

	Vector nextPos = _pos;
	int fall;

	switch (state)
	{
	case WALKING_LEFT_STATE:
		// 걷기
		nextPos += Vector(-1, 0) * deltaTime * _speed;

		// 벽 충돌 검사
		if (isSolid(nextPos))
		{
			// 되돌리기 + 방향 전환
			nextPos -= Vector(-1, 0) * deltaTime * _speed;
			setWalkingRight(true);
		}
		else
		{
			// 낙하 검사
			fall = isSolidFloor(nextPos, 4);
			if (fall < 4) {
				nextPos += Vector(0, fall);
			}
		}
		break;

	case WALKING_RIGHT_STATE:
		// 걷기
		nextPos += Vector(+1, 0) * deltaTime * _speed;

		// 벽 충돌 검사
		if (isSolid(nextPos))
		{
			nextPos -= Vector(+1, 0) * deltaTime * _speed;
			setWalkingRight(false);
		}
		else
		{
			fall = isSolidFloor(nextPos, 4);
			if (fall < 4) {
				nextPos += Vector(0, fall);
			}
		}
		break;
	}

	_pos = nextPos;
	_sprite->updateComponent(deltaTime);
}


bool Lemming::isSolid(Vector nextPos)
{
	GameScene* gameScene = Game::getGameScene();
	if (!gameScene || !gameScene->GetTerrain()) return false;

	_debugFrontPoints.clear();

	// 발 앞으로 충돌 검사 (스프라이트 좌표 기준)
	Vector frontPoint1(2, 5);
	Vector frontPoint2(-2, 5);

	Vector mapCollisionPos1 = nextPos + (frontPoint1 * 3.f);
	Vector mapCollisionPos2 = nextPos + (frontPoint2 * 3.f);

	_debugFrontPoints.push_back(mapCollisionPos1);
	_debugFrontPoints.push_back(mapCollisionPos2);

	// Terrain에 실제 픽셀이 있으면 벽
	if (gameScene->GetTerrain()->isSolid(mapCollisionPos1.x, mapCollisionPos1.y) != 0 ||
		gameScene->GetTerrain()->isSolid(mapCollisionPos2.x, mapCollisionPos2.y) != 0)
	{
		return true;
	}

	return false;
}
int Lemming::isSolidFloor(Vector nextPos, int maxFall)
{
	GameScene* gameScene = Game::getGameScene();
	if (!gameScene || !gameScene->GetTerrain()) return 0;

	_debugFloorPoints.clear();

	// 레밍 발바닥 기준 좌표 (스프라이트 좌상단 기준 offset)
	Vector footPoint1(2, 16);
	Vector footPoint2(-2, 16);

	int fall = 0;
	bool bContact = false;

	while ((fall < maxFall) && !bContact)
	{
		Vector mapCollisionPos1 = nextPos + (footPoint1 + Vector(0, fall)) * 3.f;
		Vector mapCollisionPos2 = nextPos + (footPoint2 + Vector(0, fall)) * 3.f;

		_debugFloorPoints.push_back(mapCollisionPos1);
		_debugFloorPoints.push_back(mapCollisionPos2);

		// 두 지점 모두 빈 공간이면 계속 낙하
		if (gameScene->GetTerrain()->isSolid(mapCollisionPos1.x, mapCollisionPos1.y) == 0 &&
			gameScene->GetTerrain()->isSolid(mapCollisionPos2.x, mapCollisionPos2.y) == 0)
		{
			fall += 1;
		}
		else
		{
			bContact = true; // 땅을 찾음

		}
	}

	return fall;
}

void Lemming::Render(HDC hdc)
{
	if (_sprite)
	{
		_sprite->renderComponent(hdc, _pos);

		GameScene* gameScene = Game::getGameScene();
		if (!gameScene || !gameScene->GetTerrain()) return;
		Terrain* terrain = gameScene->GetTerrain();

		// 🔹 디버그 충돌 영역 표시

		HBRUSH frontBrush = CreateSolidBrush(RGB(0, 255, 0));
		for (auto& p : _debugFrontPoints)
		{
			// 월드 좌표 → Terrain 좌상단 기준 화면 좌표
			Vector local = terrain->worldToLocal(p.x, p.y);
			RECT rc = { (int)local.x, (int)local.y, (int)local.x + 2, (int)local.y + 2 };
			FillRect(hdc, &rc, frontBrush);
		}
		DeleteObject(frontBrush);

		HBRUSH floorBrush = CreateSolidBrush(RGB(255, 0, 0));
		for (auto& p : _debugFloorPoints)
		{
			Vector local = terrain->worldToLocal(p.x, p.y);
			RECT rc = { (int)local.x, (int)local.y, (int)local.x + 2, (int)local.y + 2 };
			FillRect(hdc, &rc, floorBrush);
		}
		DeleteObject(floorBrush);
	}
}

bool Lemming::outOfMap()
{
	Vector pos = getPosition();

	return (pos.x < 0 || pos.y < 0 || pos.x > GWinSizeX || pos.y > GWinSizeY);
}

//void Lemming::changeJob(Job* nextJob)
//{
//	if (_job)
//	{
//		delete _job;
//	}
//	_job = nextJob;
//}
//


//
//bool Lemming::isDead() const
//{
//	return !_alive;
//}
//
//bool Lemming::isSaved() const
//{
//	return _saved;
//}
//
//Job* Lemming::getJob() const
//{
//	return _job;
//}

