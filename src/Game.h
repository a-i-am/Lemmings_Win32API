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

	// �ʱ�ȭ, ����, ������Ʈ, ������
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


	HWND	_hwnd;	// ������ �ڵ�
	HDC		_hdc;	// �⺻ ��ȭ�� ���� (����Ʈ ����)

	// Double Buffering
	RECT	_rect;              // ������ ����
	HDC		_hdcBack = {};	// ������ ��ȭ�� �غ�
	HBITMAP _bmpBack = {};	// Bitmap ���ٰ� ����Ѵ�.

	// GDI+
	ULONG_PTR _gdiplusToken;
	GdiplusStartupInput  _gdiplusStartupInput;

	class GameScene* _currScene = nullptr;	// ���� Ȱ��ȭ�� ���� ������Ʈ/�׷��ش�.
	class GameScene* _nextScene = nullptr;	// ���� ���� ��� ������ ���� ƽ�� ����

	

};

