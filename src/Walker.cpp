#include "pch.h"
//#include "Walker.h"
//
//enum WalkerAnims
//{
//	WALKING_LEFT, WALKING_RIGHT
//};
//
//void Walker::initAnims()
//{
//	// "lemming" �ؽ�ó�� ResourceManager::init()���� �̹� ��ϵǾ� �־�� ��
//
//	auto spriteRenderer = lemming->addComponent<SpriteRenderer>("lemming", 1.0f);
//	spriteRenderer = new SpriteRenderer("lemming", 0.666f); // 0.666�� ���� �ִϸ��̼� ���� (�� 8������ ����)
//
//	// ������ �ȱ� (�ؽ�ó ��Ʈ���� 0�� ~ 7�� ������)
//	spriteRenderer->setAnimationClip(0, 8);
//	//// WALKING
//	//jobSprite->setAnimationSpeed(WALKING_RIGHT, 12);
//	//for (int i = 0; i < 8; i++) {
//	//	jobSprite->addKeyframe(WALKING_RIGHT, glm::vec2(float(i) / 16, 0.0f));
//	//}
//
//	//jobSprite->setAnimationSpeed(WALKING_LEFT, 12);
//	//for (int i = 0; i < 8; i++) {
//	//	jobSprite->addKeyframe(WALKING_LEFT, glm::vec2((15 - float(i)) / 16, 0.0f), true);
//	//}
//}
//
//void Walker::setWalkingRight(bool value)
//{
//	walkingRight = value;
//
//	if (walkingRight) {
//		//jobSprite->changeAnimation(WALKING_RIGHT);
//		state = WALKING_RIGHT_STATE;
//	}
//	else {
//		//jobSprite->changeAnimation(WALKING_LEFT);
//		state = WALKING_LEFT_STATE;
//	}
//}
//
//void Walker::updateStateMachine(int deltaTime)
//{
//	int fall;
//
//}
//
//string Walker::getName()
//{
//	return "WALKER";
//}