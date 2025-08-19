#include "pch.h"
#include "Lemming.h"
#include "Collider.h"
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

	_sprite = _spriteMoveRight;
}

void Lemming::update(float deltaTime)
{
	Vector nextPos = _pos;	 // 10, 10
	float moveAmount = _speed * deltaTime;

	// 이동 방향에 따라 위치 계산
	if (_walkingRight)
		nextPos.x += moveAmount;	// 11, 10
	else
		nextPos.x -= moveAmount;

	// 아래 방향 중력/낙하 처리 (간단히 1픽셀씩 내려가면서 충돌 확인
	Vector checkPos = nextPos;
	checkPos.y += 1;

	_pos = nextPos;

	//GameScene* gameScene = Game::getGameScene();
	//if (gameScene && gameScene->GetTerrain())
	//{
	//	gameScene->GetTerrain()->픽셀충돌

	//}

	// 화면 경계 체크
	if (_pos.x < 200) 
	{ 
		_pos.x = 200; 
		_walkingRight = true; 
		_sprite = _spriteMoveRight;	// 오른쪽 이미지로 교체
	}
	
	if (_pos.x > 500) 
	{
		_pos.x = 500; 
		_walkingRight = false; 
		_sprite = _spriteMoveLeft;	// 왼쪽 이미지로 교체

	}

	_sprite->updateComponent(deltaTime);
}

void Lemming::render(HDC hdc)
{
	if (_sprite)
	{
		_sprite->renderComponent(hdc, _pos);
	}
}

bool Lemming::outOfMap()
{
	Vector pos = getPosition();

	return (pos.x < 0 || pos.y < 0 || pos.x > GWinSizeX || pos.y > GWinSizeY);
}
bool Lemming::isWalkingRight()
{
	return _walkingRight;
}
void Lemming::setWalkingRight(bool value)
{
	_walkingRight = right;
	//job->setWalkingRight(right);
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

