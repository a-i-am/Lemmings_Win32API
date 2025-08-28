#include "pch.h"
#include "common_defs.h"
#include "SceneKeyboardManager.h"

// 레벨에선 마우스만 씀. 키보드는 레벨 전에 메뉴 선택용으로만 사용. (StateManager::changeMenu())
// 키 입력 상태 처리는 GameState에서 담당.

void SceneKeyboardManager::keyPressed(int32 key)
{
	if (key == 27)
	{
//		LevelManager::getInstance().endMusic();
//		StateManager::instance().changeMenu();

	}
}

void SceneKeyboardManager::keyReleased(int32 key) {
}

void SceneKeyboardManager::specialKeyPressed(int32 key) {

}

void SceneKeyboardManager::specialKeyReleased(int32 key) {

}