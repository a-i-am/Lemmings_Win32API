#include "pch.h"
#include "common_defs.h"
#include "SceneKeyboardManager.h"

// �������� ���콺�� ��. Ű����� ���� ���� �޴� ���ÿ����θ� ���. (StateManager::changeMenu())
// Ű �Է� ���� ó���� GameState���� ���.

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