#include "pch.h"
#include "Lemming.h"
#include "Collider.h"
#include "ResourceManager.h"
Lemming::Lemming(Vector pos) : Super(pos) 
{

	_sprite = CreateSpriteComponent("lemming", 1.0f, 16 * 3.f, 14 * 3.f);
	_sprite->setAnimationClip(0, 8);
}

void Lemming::update(float deltaTime)
{
	Vector nextPos = _pos;
	float moveAmount = _speed * deltaTime;
	_pos.x += moveAmount;
	// �̵� ���⿡ ���� ��ġ ���
	if (_walkingRight)
		nextPos.x += moveAmount;
	else
		nextPos.x -= moveAmount;

	// �Ʒ� ���� �߷�/���� ó�� (������ 1�ȼ��� �������鼭 �浹 Ȯ��
	Vector checkPos = nextPos;
	checkPos.y += 1;

	//if (_collider->isColliding(checkPos))
	//{
	//	// �浹�� ������ ���� ���� ����
	//	_position = nextPos;
	//}
	//else
	//{
	//	// �浹 ������ ������
	//	_position.y += moveAmount;
	//}

	// ȭ�� ��� üũ
	if (_pos.x < 0) { _pos.x = 0; _walkingRight = true; }
	if (_pos.x > 800) { _pos.x = 800; _walkingRight = false; }

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

