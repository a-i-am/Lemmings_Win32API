#pragma once

#include "MouseManager.h"
#include "KeyboardManager.h"


class GameState
{
public:
	virtual ~GameState() {}

	// Input �ݹ� �޼���
	void keyPressed(int32 key);
	void keyReleased(int32 key);
	void specialKeyPressed(int32 key);
	void specialKeyReleased(int32 key);
	void mouseMove(int32 x, int32 y, HWND hWnd);
	void mousePress(int32 button);
	void mouseRelease(int32 button);

	bool getKey(int32 key) const;
	bool getSpecialKey(int32 key) const;

protected:
	MouseManager *mouseManager;
	KeyboardManager *keyboardManager;
	float currentTime;

private:

	bool keys[256], specialKeys[256]; // Ű ���¸� ����

	int32 mouseX, mouseY;
	bool bLeftMouse, bRightMouse;

};


