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
	_spriteMoveRight->getTexture()->generateCollisionData(256, 224);
	_spriteMoveLeft->getTexture()->generateCollisionData(256, 224);

	_sprite = _spriteMoveRight;
}

void Lemming::update(float deltaTime)
{
	Vector nextPos = _pos;	 // 10, 10
	float moveAmount = _speed * deltaTime;
	
	// 이동 방향에 따라 위치 계산
	if (_isWalkingRight)
		nextPos.x += moveAmount;	// 11, 10
	else
		nextPos.x -= moveAmount;

	// 아래 방향 중력/낙하 처리 (간단히 1픽셀씩 내려가면서 충돌 확인
	nextPos.y += 20.0f * deltaTime;

	GameScene* gameScene = Game::getGameScene();
	if (gameScene && gameScene->GetTerrain())
	{
		if (isSolid(nextPos))
		{
			_pos.x = nextPos.x;
		}
		else
		{
			_pos.y = nextPos.y;
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

bool Lemming::isSolid(Vector nextPos)
{
	GameScene* gameScene = Game::getGameScene();
	if (gameScene == nullptr)
		return false;

	if (gameScene->GetTerrain() == nullptr)
		return false;

	// nextPos 는 월드상(윈도우 화면상의) 좌표계

	const int spriteWidth = 16;
	const int spriteHeight = 16;
	const int textureWidth = _sprite->getTexture()->getTextureWidth();

	bool isFloor = false;
	bool isLeftWall = false;
	bool isRightWall = false;

	// 스프라이트가 그려지고 있는 위치는 센터기준
	Vector lemingTexturePos(_sprite->srcX + spriteWidth*0.5f, _sprite->srcY + spriteHeight * 0.5f);
	for (int y = spriteHeight / 2 - 1; y > -spriteHeight / 2; --y) // Y축은 바닥부터 충돌체크하면 더 좋을것 같아서 반대로 뒤집어서 충돌체크
	{
		for (int x = -spriteWidth / 2; x < spriteWidth / 2; ++x)
		{
			Vector lemingCollisionPos = Vector(lemingTexturePos.x + x, lemingTexturePos.y + y);

			// 레밍스 원본 텍스처의 픽셀을 구하는 좌표계
			if (_sprite->getTexture()->getPixelData()[lemingCollisionPos.y * textureWidth + lemingCollisionPos.x] != 0)
			{
				int scale = 3;

				// 맵과 충돌체크를 하는겁니다.
				Vector mapCollisionPos = Vector(nextPos.x + (x * scale), nextPos.y + (y * scale)); // 어디든 스프라이트 닿는 위치
				Vector mapRightWallCollisionPos = Vector(nextPos.x + (spriteWidth / 2 - 1) * scale, nextPos.y + y * scale); // 중심 기준 오른쪽 끝
				Vector mapLeftWallCollisionPos = Vector(nextPos.x + (-spriteWidth / 2) * scale, nextPos.y + y * scale); //  중심 기준 왼쪽 끝

				if (gameScene->GetTerrain()->isSolid(mapCollisionPos.x, mapCollisionPos.y))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}

	}

}

bool Lemming::outOfMap()
{
	Vector pos = getPosition();

	return (pos.x < 0 || pos.y < 0 || pos.x > GWinSizeX || pos.y > GWinSizeY);
}
bool Lemming::isWalkingRight()
{
	return _isWalkingRight;
}
void Lemming::setWalkingRight(bool value)
{



	_isWalkingRight = right;
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

