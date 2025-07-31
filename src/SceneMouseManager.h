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
		SCROOL_AREA_LEFT,
		SCROOL_AREA_RIGHT,
		LEVEL,
		NONE_AREA
	};

	enum MouseStates {
		NONE,
		LEFT_MOUSE_PRESSED,
		RIGHT_MOUSE_PRESSED
	};

	void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton);
	void update();

private:
	ScreenClickedArea getClickedScreenArea(int mouseX, int mouseY);
	ScreenMovedArea getMovedScreenArea(int mouseX, int mouseY);

	void leftClickOnUI(int posX, int posY);
	void leftClickOnMap(int posX, int posY);

	void updateCursorPosition();

private:
	int posX, posY;

	MouseStates mouseState = MouseStates::NONE;
	ScreenMovedArea screenMovedArea;
};

