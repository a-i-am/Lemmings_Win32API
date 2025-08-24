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
	}
	else {
		_isWalkingRight = false;
		state = WALKING_LEFT_STATE;
	}
}



void Lemming::update(float deltaTime)
{
	GameScene* gameScene = Game::getGameScene();
	//Vector nextPos = _pos;	 // 10, 10
	if(!gameScene || !gameScene->GetTerrain()) return;

	//float landedY;
	//if (isSolidFloor(nextPos, landedY))
	//{
	//	_isOnGround = true;
	//	nextPos.y = landedY;
	//}
	//else
	//{
	//	// 아래 방향 중력/낙하 처리 (간단히 1픽셀씩 내려가면서 충돌 확인
	//	nextPos.y += 20.0f * deltaTime;
	//	_pos.y = nextPos.y;
	//}

	//float moveAmount = _speed * deltaTime;
	//// 수평 이동 처리: 바닥에 있고 벽이 없을 때만
	//if (_isOnGround)
	//{
	//	// 이동할 다음 x 위치를 미리 계산
	//	
	//	if (_isWalkingRight)
	//		nextPos.x += _speed * deltaTime;
	//	else
	//		nextPos.x -= _speed * deltaTime;
	//
	//}
// 바닥에 닿았을 때 _pos.y는 업데이트하지 않음
// 대신 nextPos.y를 사용하여 정확한 충돌 위치를 찾을 수 있음
// 아래로 떨어지는데 충돌체크 항상 수행
// 아래쪽 발밑 Y 값을 찾아와야한다.
// nextPos.y = 충돌된 Y
// 발 아래가 충돌이 안되었다면 떨어지는중.
// _onGround = true or false;

	int fall;

	switch (state)
	{
	case WALKING_LEFT_STATE:
		_pos += Vector(-1, +2);

		if (isSolid())
		{
			_pos -= Vector(-1, +2);
			_isWalkingRight = true;
		}
		else
		{
			fall = isSolidFloor(4);
			if (fall < 4) {
				_pos += Vector(0, fall);
			}

		}
		break;
	case WALKING_RIGHT_STATE:
		_pos += Vector(1, +2);
		if (isSolid())
		{
			_pos -= Vector(1, +2);
			_isWalkingRight = false;
		}
		else
		{
			fall = isSolidFloor(4);
			if (fall < 4) {
				_pos += Vector(0, fall);
			}
		}
		break;
	}
	
	_sprite->updateComponent(deltaTime);
}

void Lemming::render(HDC hdc)
{
	if (_sprite)
	{
		_sprite->renderComponent(hdc, _pos);
	}


#pragma region 충돌 영역 표시
//	HPEN hOldPen, hNewPen;
//	HBRUSH hOldBrush, hNewBrush;
//
//	hNewPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
//	hNewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);//투명 브러쉬
//
//	hOldPen = (HPEN)SelectObject(hdc, hNewPen);
//	hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
//
//	const int spriteWidth = 16 * 3;
//	const int spriteHeight = 16 * 3;
//
//	// 레밍 좌표를 좌상단 좌표로 변환
//	int left = _pos.x - spriteWidth / 2;
//	int top = _pos.y - spriteHeight / 2;
//	int right = _pos.x + spriteWidth / 2;
//	int bottom = _pos.y + spriteHeight / 2;
//
//	// 바닥 충돌 검사 ( 노란색 )
//	hNewPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
//	SelectObject(hdc, hNewPen);
//
//	int floorCheckLeft = left;
//	int floorCheckTop = bottom - (3 * 3); // 바닥 검사 영역을 레밍 발바닥 근처로 설정
//	int floorCheckRight = right;
//	int floorCheckBottom = bottom + (3 * 3);
//	Rectangle(hdc, floorCheckLeft, floorCheckTop, floorCheckRight, floorCheckBottom);
//
//	// 벽 충돌 검사 ( 초록색 )
//	hNewPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
//	SelectObject(hdc, hNewPen);
//
//	int wallCheckWidth = 3 * 3; // 3픽셀 * 3배 스케일
//	int wallCheckHeight = spriteHeight;
//
//	// 오른쪽/왼쪽 벽 충돌 검사
//	int rightWallLeft = right - wallCheckWidth;
//	int rightWallTop = top;
//	int rightWallRight = right;
//	int rightWallBottom = bottom;
//
//	int leftWallLeft = left;
//	int leftWallTop = top;
//	int leftWallRight = left + wallCheckWidth;
//	int leftWallBottom = bottom;
//
//	// 펜과 브러쉬 복원
//	SelectObject(hdc, hOldPen);
//	SelectObject(hdc, hOldBrush);
//	DeleteObject(hNewPen);
//	DeleteObject(hNewBrush);
#pragma endregion

}

int Lemming::isSolidFloor(int maxFall)
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

	bool bContact = false;
	int fall = 0;

	Vector lemingTexturePos(_sprite->srcX + spriteWidth * 0.5f, _sprite->srcY + spriteHeight * 0.5f);
	
	Vector posBase = _pos;

	//for (int y = spriteHeight / 2 + 1; y > -spriteHeight / 2; --y)
	//{
	//	for (int x = -spriteWidth / 2; x < spriteWidth / 2; ++x) // 중간 기준 왼~오 전부
	//	{
	//		Vector mapCollisionPos = Vector(lemingTexturePos.x + (x * scale),
	//										lemingTexturePos.y + (y * scale));
	//	}
	//}

	while (fall < maxFall && !bContact)
	{
		if ((gameScene->GetTerrain()->isSolid(posBase.x, posBase.y) == 0)
		&& (gameScene->GetTerrain()->isSolid(posBase.x + 1, posBase.y) == 0))
		{
			fall += 1;
		}
		else
		{
			bContact = true;
		}
	}

	//		// 레밍 텍스처 중에 충돌검사할 좌표만 넣는다
	//		Vector lemingCollisionPos = Vector(lemingTexturePos.x + x,
	//										   lemingTexturePos.y + y);
	//		// 월드좌표 위치 + 레밍 충돌 검사할 범위 = 맵과 충돌감지할 레밍의 실제 렌더 범위
	//		// 실제 맵 픽셀과 충돌하는지 확인하기 위해 렌더링되는 비율 똑같이 맞춰준다.

	//		std::stringstream ss;
	//		ss << "[DEBUG] x=" << x
	//			<< " lemingTex=(" << lemingCollisionPos.x << "," << lemingCollisionPos.y << ")"
	//			<< " map=(" << mapCollisionPos.x << "," << mapCollisionPos.y << ")"
	//			<< " nextPos=(" << _pos.x << "," << _pos.y << ")\n";
	//		OutputDebugStringA(ss.str().c_str());
	//		// 그 값을 레밍즈 원본 텍스처의 픽셀을 구하는 좌표계에 넣는다.
	//		if (_sprite->getTexture()->getPixelData()[lemingCollisionPos.y * textureWidth + lemingCollisionPos.x] != 0)
	//		{
	//			// 맵과 충돌하니?
	//			if (gameScene->GetTerrain()->isSolid(mapCollisionPos.x, mapCollisionPos.y))
	//			{
	//				// 맵과의 충돌 지점을 넘겨준다.
	//				//landedY = mapCollisionPos.y;
	//				
	//				return true;
	//			}
	//		}
	//	}
	//}

	return false;
}

bool Lemming::isSolid()
{
	// nextPos 는 월드상(윈도우 화면상의) 좌표계
	GameScene* gameScene = Game::getGameScene();
	if (gameScene == nullptr)
		return false;

	if (gameScene->GetTerrain() == nullptr)
		return false;

	const int spriteWidth = 16;
	const int spriteHeight = 16;
	const int textureWidth = _sprite->getTexture()->getTextureWidth();
	const int scale = 3;

	// 스프라이트가 그려지고 있는 위치는 센터기준
	Vector lemingTexturePos(_sprite->srcX + spriteWidth*0.5f, _sprite->srcY + spriteHeight * 0.5f);
	
	Vector posBase = _pos;
	posBase += Vector(7, 15);

	if ((gameScene->GetTerrain()->isSolid(posBase.x, posBase.y) == 0)
		&& (gameScene->GetTerrain()->isSolid(posBase.x + 1, posBase.y) == 0))
	{
		return false;
	}

	
	//for (int y = spriteHeight / 2 - 1; y > -spriteHeight / 2; --y) // Y축은 바닥부터 충돌체크하면 더 좋을것 같아서 반대로 뒤집어서 충돌체크
	//{
	//	for (int x = -spriteWidth / 2; x < spriteWidth / 2; ++x)
	//	{
	//		Vector lemingCollisionPos = Vector(lemingTexturePos.x + x, lemingTexturePos.y + y);

	//		// 레밍스 원본 텍스처의 픽셀을 구하는 좌표계
	//		if (_sprite->getTexture()->getPixelData()[lemingCollisionPos.y * textureWidth + lemingCollisionPos.x] != 0)
	//		{
	//			Vector mapCollisionPos = Vector(nextPos.x + (x*3), nextPos.y + (y*3));
	//			if (gameScene->GetTerrain()->isSolid(mapCollisionPos.x, mapCollisionPos.y))
	//			{
	//				return true; 
	//			}
	//		}
	//	}
	//}


	return true;
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

