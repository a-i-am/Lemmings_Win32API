#include "pch.h"

#include "common_defs.h"
#include "GameState.h"


void GameState::keyPressed(int key)
{
	// InputState���� ������ Ű����Ŵ��� ������ Ű �Է��� �޴´�
	keyboardManager->keyPressed(key);
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

void GameState::mouseMove(int x, int y, HWND hWnd)
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect); // hWnd�� ���� ������ �ڵ�

	int windowWidth = clientRect.right - clientRect.left;
	int windowHeight = clientRect.bottom - clientRect.top;

	// ���콺�� ī�޶� ���� �������� �����̸� �ȴ�.
	float aspectRatioX = (float(CAMERA_WIDTH) / windowWidth);
	float aspectRatioy = (float(CAMERA_HEIGHT) / windowHeight);

	mouseX = x * aspectRatioX;
	mouseY = y * aspectRatioy;

	mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
}

void GameState::mousePress(int button)
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

void GameState::mouseRelease(int button)
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

bool GameState::getKey(int key) const
{
	return keys[key];
}

bool GameState::getSpecialKey(int key) const
{
	return specialKeys[key];
}
