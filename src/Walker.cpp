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
//	// "lemming" 텍스처는 ResourceManager::init()에서 이미 등록되어 있어야 함
//
//	auto spriteRenderer = lemming->addComponent<SpriteRenderer>("lemming", 1.0f);
//	spriteRenderer = new SpriteRenderer("lemming", 0.666f); // 0.666초 동안 애니메이션 루프 (총 8프레임 기준)
//
//	// 오른쪽 걷기 (텍스처 시트에서 0번 ~ 7번 프레임)
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