#pragma once


#include "GameScene.h"
#include "GameState.h"
#include "Texture.h"
#include "TimeManager.h"
#include "MouseManager.h"
#include "KeyboardManager.h"

class Game
{

private:

public:
	Game() {}

	static Game &getInstance() {
		static Game G;

		return G;
	}

	// 초기화, 삭제, 업데이트, 렌더링
	void Init(HWND hwnd);
	void destroy();

	bool Update(float deltaTime);
	void Render();

	HWND getHwnd() { return _hwnd; }

	void changeBplay();
	bool isHardMode();
	void swapDifficultyMode();

	GameState* getGameState();
	void setGameState(GameState* state);

	static class GameScene* getGameScene();
	

private:
	//SoundManager soundManager;
	bool bPlay; // "Continue to play game?"
	bool hardMode;
	GameState* gameState;
	//Sprite *hardModeIndicator;


	HWND	_hwnd;	// 윈도우 핸들
	HDC		_hdc;	// 기본 도화지 정보 (프론트 버퍼)

	// Double Buffering
	RECT	_rect;              // 버퍼의 영역
	HDC		_hdcBack = {};	// 여분의 도화지 준비
	HBITMAP _bmpBack = {};	// Bitmap 에다가 써야한다.

	// GDI+
	ULONG_PTR _gdiplusToken;
	GdiplusStartupInput  _gdiplusStartupInput;

	class GameScene* _currScene = nullptr;	// 현재 활성화된 씬만 업데이트/그려준다.
	class GameScene* _nextScene = nullptr;	// 현재 씬이 모두 끝나고 다음 틱에 변경

	

};

