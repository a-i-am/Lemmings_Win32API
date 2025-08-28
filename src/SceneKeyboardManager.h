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

	void keyPressed(int32 key);
	void keyReleased(int32 key);
	void specialKeyPressed(int32 key);
	void specialKeyReleased(int32 key);

private:
};

