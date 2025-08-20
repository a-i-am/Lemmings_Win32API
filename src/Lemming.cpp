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

	_sprite = _spriteMoveRight;
}

void Lemming::update(float deltaTime)
{

	Vector nextPos = _pos;	 // 10, 10
	float moveAmount = _speed * deltaTime;
	
	// 이동 방향에 따라 위치 계산
	//if (_walkingRight)
	//	nextPos.x += moveAmount;	// 11, 10
	//else
	//	nextPos.x -= moveAmount;

	// 아래 방향 중력/낙하 처리 (간단히 1픽셀씩 내려가면서 충돌 확인
	nextPos.y += 20.0f * deltaTime;

	const int spriteWidth = 16;
	const int spriteHeight = 16;

	// srcX, srcY 부터 시작해서 16레밍즈 한칸 크기만큼
// 충돌체크
// for( y 16 )
//		for( x 16)
//{
		// 레밍즈 자체도 구멍이 있기때문에, 
		//해당 x, y 픽셀을 레밍즈 자체 충돌체크용 픽셀 데이터와 비교해서
		// 0이 아닌경우만, Terrain이랑 충돌체크 실행
		// 
//}


	GameScene* gameScene = Game::getGameScene();
	if (gameScene && gameScene->GetTerrain())
	{
		if (gameScene->GetTerrain()->isSolid(nextPos.x, nextPos.y))
		{
			//if (_sprite == _spriteMoveRight)
			//{
			//	_walkingRight = false;
			//	_sprite = _spriteMoveLeft;
			//}
			//else
			//{
			//	_walkingRight = true;
			//	_sprite = _spriteMoveRight;
			//}
		}
		else
		{
			_pos = nextPos;
		}
	}

	// 화면 경계 체크
	//if (_pos.x < 400) 
	//{ 
	//	_walkingRight = true; 
	//	_sprite = _spriteMoveRight;
	//	_pos.x = 400; 
	//}
	//
	//if (_pos.x > 500) 
	//{
	//	_pos.x = 500; 
	//	_walkingRight = false; 
	//	_sprite = _spriteMoveLeft;

	//}

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

