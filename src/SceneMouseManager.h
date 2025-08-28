#pragma once

#include "MouseManager.h"

// virtual 함수 재사용(오버라이딩)
class SceneMouseManager : public MouseManager
{

public:
	static SceneMouseManager& getInstance()
	{
		static SceneMouseManager instance;

		return instance;
	};

	enum ScreenClickedArea {
		MAP,
		UI,
		INFO
	};

	enum ScreenMovedArea {
		SCROLL_AREA_LEFT,
		SCROLL_AREA_RIGHT,
		LEVEL,
		NONE_AREA
	};

	enum MouseStates {
		NONE,
		LEFT_MOUSE_PRESSED,
		RIGHT_MOUSE_PRESSED
	};

	void mouseMoved(int32 mouseX, int32 mouseY, bool bLeftButton, bool bRightButton);
	void Update();

private:
	ScreenClickedArea getClickedScreenArea(int32 mouseX, int32 mouseY);
	ScreenMovedArea getMovedScreenArea(int32 mouseX, int32 mouseY);

	void leftClickOnUI(int32 posX, int32 posY);
	void leftClickOnMap(int32 posX, int32 posY);

	void updateCursorPosition();

private:
	int32 posX, posY;

	MouseStates mouseState = MouseStates::NONE;
	ScreenMovedArea screenMovedArea;
};

