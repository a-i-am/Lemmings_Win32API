#include "pch.h"
#include "common_defs.h"
#include "SceneKeyboardManager.h"

// �������� ���콺�� ��. Ű����� ���� ���� �޴� ���ÿ����θ� ���. (StateManager::changeMenu())
// Ű �Է� ���� ó���� GameState���� ���.

void SceneKeyboardManager::keyPressed(int key)
{
	if (key == 27)
	{
//		LevelManager::getInstance().endMusic();
//		StateManager::instance().changeMenu();

	}
}

void SceneKeyboardManager::keyReleased(int key) {
}

void SceneKeyboardManager::specialKeyPressed(int key) {

}

void SceneKeyboardManager::specialKeyReleased(int key) {

}