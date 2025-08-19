#pragma once

#include "MouseManager.h"
#include "KeyboardManager.h"


class GameState
{
public:
	virtual ~GameState() {}

	// Input �ݹ� �޼���
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y, HWND hWnd);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

protected:
	MouseManager *mouseManager;
	KeyboardManager *keyboardManager;
	float currentTime;

private:

	bool keys[256], specialKeys[256]; // Ű ���¸� ����

	int mouseX, mouseY;
	bool bLeftMouse, bRightMouse;

};


