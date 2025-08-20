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


	// ���Ĵ� ���
	//_spriteDig = CreateSpriteComponent("lemming", 1.0f, 16 * 3.f, 14 * 3.f);
	//_spriteDig->setAnimationClip(0, 8);

	_sprite = _spriteMoveRight;
}

void Lemming::update(float deltaTime)
{

	Vector nextPos = _pos;	 // 10, 10
	float moveAmount = _speed * deltaTime;
	
	// �̵� ���⿡ ���� ��ġ ���
	//if (_walkingRight)
	//	nextPos.x += moveAmount;	// 11, 10
	//else
	//	nextPos.x -= moveAmount;

	// �Ʒ� ���� �߷�/���� ó�� (������ 1�ȼ��� �������鼭 �浹 Ȯ��
	nextPos.y += 20.0f * deltaTime;

	const int spriteWidth = 16;
	const int spriteHeight = 16;

	// srcX, srcY ���� �����ؼ� 16������ ��ĭ ũ�⸸ŭ
// �浹üũ
// for( y 16 )
//		for( x 16)
//{
		// ������ ��ü�� ������ �ֱ⶧����, 
		//�ش� x, y �ȼ��� ������ ��ü �浹üũ�� �ȼ� �����Ϳ� ���ؼ�
		// 0�� �ƴѰ�츸, Terrain�̶� �浹üũ ����
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

	// ȭ�� ��� üũ
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

