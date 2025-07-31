#include "pch.h"
#include "GameState.h"
#include "common_defs.h"

void GameState::keyPressed(int key)
{
	// InputState에서 선언한 키보드매니저 참조로 키 입력을 받는다
	keyboardManager->KeyPressed(key);
	keys[key] = true;
}
void GameState::keyReleased(int key)
{
	keys[key] = false;
}
void GameState::specialKeyPressed(int key)
{
	keyboardManager->specialKeyPressed(key);
	specialKeys[key] = true;
}
void GameState::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void GameState::mouseMove(int x, int y)
{
	int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

	// 마우스는 카메라 범위 내에서만 움직이면 된다.
	float aspectRatioX = (float(CAMERA_WIDTH) / windowWidth);
	float aspectRatioy = (float(CAMERA_HEIGHT) / windowHeight);
	mouseX = x * aspectRatioX;
	mouseY = y * aspectRatioy;

	mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
}

void GameState::mousePress(int button)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		bLeftMouse = true;
		mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		bRightMouse = true;
		mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
}

void GameState::mouseRelease(int button)
{
	if (button == GLUT_LEFT_BUTTON) {
		bLeftMouse = false;
		mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}

	else if (button == GLUT_RIGHT_BUTTON) {
		bRightMouse = false;
		mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
}

bool GameState::getKey(int key) const
{
	return keys[key];
}

bool GameState::getSpecialKey(int key) const
{
	return specialKeys[key];
}
