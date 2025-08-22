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

	_isWalkingRight = true;
	_sprite = _spriteMoveRight;
}

void Lemming::update(float deltaTime)
{
	GameScene* gameScene = Game::getGameScene();
	Vector nextPos = _pos;	 // 10, 10
	if(!gameScene || !gameScene->GetTerrain()) return;

	float landedY;
	if (isSolidFloor(nextPos, landedY))
	{
		_isOnGround = true;
		nextPos.y = landedY;
	}
	else
	{
		// 아래 방향 중력/낙하 처리 (간단히 1픽셀씩 내려가면서 충돌 확인
		nextPos.y += 20.0f * deltaTime;
		_pos.y = nextPos.y;
	}

	float moveAmount = _speed * deltaTime;

	// 수평 이동 처리: 바닥에 있고 벽이 없을 때만
	if (_isOnGround)
	{
		// 이동할 다음 x 위치를 미리 계산
		Vector checkPos = _pos;
		if (_isWalkingRight)
			checkPos.x += _speed * deltaTime;
		else
			checkPos.x -= _speed * deltaTime;

		// 이동할 위치에 벽이 있는지 검사
		if (!isSolidWall(checkPos))
		{
			_pos.x = checkPos.x;
		}
		else
		{
			// 벽이 있다면 방향 전환
			_isWalkingRight = !_isWalkingRight;
		}
	}


// 바닥에 닿았을 때 _pos.y는 업데이트하지 않음
// 대신 nextPos.y를 사용하여 정확한 충돌 위치를 찾을 수 있음
// 아래로 떨어지는데 충돌체크 항상 수행
// 아래쪽 발밑 Y 값을 찾아와야한다.
// nextPos.y = 충돌된 Y
// 발 아래가 충돌이 안되었다면 떨어지는중.
// _onGround = true or false;



	_sprite->updateComponent(deltaTime);
}

void Lemming::render(HDC hdc)
{
	if (_sprite)
	{
		_sprite->renderComponent(hdc, _pos);
	}
}

bool Lemming::isSolidFloor(Vector nextPos, float& landedY)
{
	GameScene* gameScene = Game::getGameScene();
	if (gameScene == nullptr)
		return false;

	if (gameScene->GetTerrain() == nullptr)
		return false;

	const int spriteWidth = 16;
	const int spriteHeight = 16;
	const int textureWidth = _sprite->getTexture()->getTextureWidth();
	const int scale = 3;

	// 발밑에서 몇픽셀 정보가 맵이랑 겹쳐있는지 확인.
	// 맵과의 충돌된 해당 Y 픽셀값을 얻어와서
	// 레밍즈의 Y 위치로 설정한다.
	Vector lemingTexturePos(_sprite->srcX + spriteWidth * 0.5f, _sprite->srcY + spriteHeight * 0.5f);
	for (int y = spriteHeight / 2 - 1; y < spriteHeight / 2+1; ++y) // 발부터 발아래1칸 까지. 
	{
		for (int x = -spriteWidth / 2; x < spriteWidth / 2; ++x) // 중간 기준 왼~오 전부
		{
			Vector lemingCollisionPos = Vector(lemingTexturePos.x + x, lemingTexturePos.y + y); // 레밍 텍스처 중에 충돌검사할 좌표만 넣는다

			// 레밍스 원본 텍스처의 픽셀을 구하는 좌표계
			if (_sprite->getTexture()->getPixelData()[lemingCollisionPos.y * textureWidth + lemingCollisionPos.x] != 0)
			{
				// 최종적으로, 실제 맵 픽셀과 충돌됐는지 확인하기 위해 비율 맞춰준다.
				Vector mapCollisionPos = Vector(nextPos.x + (x * 3), nextPos.y + (y * 3));
				if (gameScene->GetTerrain()->isSolid(mapCollisionPos.x, mapCollisionPos.y))
				{
					landedY = mapCollisionPos.y;
					return true;
				}
			}
		}
	}
	return false; // 루프를 모두 순회했으나 충돌하는 픽셀이 없음
}

// 앞뒤로 갈수있는지 판단.
bool Lemming::isSolidWall(Vector nextPos)
{
	// 좌/우에 대해서만 맵이랑 겹치는지 확인
	// 겹친다면, 갈수없는 지역이라서 방향 전환
	GameScene* gameScene = Game::getGameScene();
	if (gameScene == nullptr)
		return false;

	if (gameScene->GetTerrain() == nullptr)
		return false;

	const int spriteWidth = 16;
	const int spriteHeight = 16;
	const int textureWidth = _sprite->getTexture()->getTextureWidth();
	const int scale = 3;

	Vector lemingTexturePos(_sprite->srcX + spriteWidth * 0.5f, _sprite->srcY + spriteHeight * 0.5f);
	for (int y = spriteHeight / 2-1; y > -spriteHeight / 2+1; --y) // 발보다 위부터 맨 위까지. 
	{
		for (int x = -spriteWidth / 2+1; x < spriteWidth / 2-1; ++x) // 중간 기준 왼~오
		{
			Vector lemingCollisionPos = Vector(lemingTexturePos.x + x, lemingTexturePos.y + y); // 레밍 텍스처 중에 충돌검사할 좌표만 넣는다

			// 레밍스 원본 텍스처의 픽셀을 구하는 좌표계
			if (_sprite->getTexture()->getPixelData()[lemingCollisionPos.y * textureWidth + lemingCollisionPos.x] != 0)
			{
				// 최종적으로, 실제 맵 픽셀과 충돌됐는지 확인하기 위해 비율 맞춰준다.
				Vector mapCollisionPos = Vector(nextPos.x + (x * 3), nextPos.y + (y * 3));

 				if (gameScene->GetTerrain()->isSolid(mapCollisionPos.x, mapCollisionPos.y))
				{
					return true;
				}
			}
		}
	}
	return false; // 루프를 모두 순회했으나 충돌하는 픽셀이 없음
}



bool Lemming::isSolid(Vector nextPos)
{
	const int spriteWidth = 16;
	const int spriteHeight = 16;
	const int textureWidth = _sprite->getTexture()->getTextureWidth();
	const int scale = 3;

	// nextPos 는 월드상(윈도우 화면상의) 좌표계
	GameScene* gameScene = Game::getGameScene();
	if (gameScene == nullptr)
		return false;

	if (gameScene->GetTerrain() == nullptr)
		return false;

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
				Vector mapCollisionPos = Vector(nextPos.x + (x*3), nextPos.y + (y*3));
				if (gameScene->GetTerrain()->isSolid(mapCollisionPos.x, mapCollisionPos.y))
				{
					return true; 
				}
			}
		}
	}
	return false; // 루프를 모두 순회했으나 충돌하는 픽셀이 없음
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

