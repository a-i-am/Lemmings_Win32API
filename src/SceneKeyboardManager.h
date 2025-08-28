#pragma once

#include "KeyboardManager.h"

// virtual �Լ� ����(�������̵�)
class SceneKeyboardManager : public KeyboardManager
{
public:
	static SceneKeyboardManager& getInstance()
	{
		static SceneKeyboardManager instance;

		return instance;
	};

	void keyPressed(int32 key);
	void keyReleased(int32 key);
	void specialKeyPressed(int32 key);
	void specialKeyReleased(int32 key);

private:
};

