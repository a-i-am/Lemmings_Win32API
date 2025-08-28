#include "pch.h"

#include "common_defs.h"
#include "GameState.h"


void GameState::keyPressed(int32 key)
{
	// InputState에서 선언한 키보드매니저 참조로 키 입력을 받는다
	keyboardManager->keyPressed(key);
	keys[key] = true;
}
void GameState::keyReleased(int32 key)
{
	keys[key] = false;
}
void GameState::specialKeyPressed(int32 key)
{
	keyboardManager->specialKeyPressed(key);
	specialKeys[key] = true;
}
void GameState::specialKeyReleased(int32 key)
{
	specialKeys[key] = false;
}

void GameState::mouseMove(int32 x, int32 y, HWND hWnd)
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect); // hWnd는 현재 윈도우 핸들

	int32 windowWidth = clientRect.right - clientRect.left;
	int32 windowHeight = clientRect.bottom - clientRect.top;

	// 마우스는 카메라 범위 내에서만 움직이면 된다.
	float aspectRatioX = (float(CAMERA_WIDTH) / windowWidth);
	float aspectRatioy = (float(CAMERA_HEIGHT) / windowHeight);

	mouseX = x * aspectRatioX;
	mouseY = y * aspectRatioy;

	mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
}

void GameState::mousePress(int32 button)
{
	if (button == VK_LBUTTON)
	{
		bLeftMouse = true;
		mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
	else if (button == VK_RBUTTON)
	{
		bRightMouse = true;
		mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
}

void GameState::mouseRelease(int32 button)
{
	if (button == VK_LBUTTON) {
		bLeftMouse = false;
		mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}

	else if (button == VK_RBUTTON) {
		bRightMouse = false;
		mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
}

bool GameState::getKey(int32 key) const
{
	return keys[key];
}

bool GameState::getSpecialKey(int32 key) const
{
	return specialKeys[key];
}
