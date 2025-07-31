#pragma once

#include "KeyboardManager.h"

// virtual 함수 재사용(오버라이딩)
class SceneKeyboardManager : public KeyboardManager
{
public:
	static SceneKeyboardManager& getInstance()
	{
		static SceneKeyboardManager instance;

		return instance;
	};

	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);

private:
};

