#include "pch.h"
#include "Game.h"
#include "GameScene.h"

void Game::init(HWND hwnd)
{
	bPlay = true;
	hardMode = false;

	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);	// �⺻ ��ȭ�� �Ѱܹޱ�

	// ���� ���۸� ���� �߰�
	::GetClientRect(hwnd, &_rect);

	_hdcBack = ::CreateCompatibleDC(_hdc); // �⺻ hdc�� ȣȯ�Ǵ� DC�� ����

	// �̰� �߰��� �ʿ��� ������ ������ ȣȯ hdc�� �츮�� ���ϴ� ũ���� ���۰� �ƴ϶� ���� ����
	// �����̴�. �츮�� �츮 ������ ��ü ������ �׸� ��ȭ���� �ʿ��ѰŶ�
	// ������ ��Ʈ���� ����, ����ٰ� ������ �׸����̴�.
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom); // hdc�� ȣȯ�Ǵ� ��Ʈ�� ����

	// ����ٰ� ������ ����� HDC�� ���ӻ���� �´� �ؽ��ĸ� �����Ѵ�.
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack); // DC�� BMP�� ����
	::DeleteObject(prev);

	// GDI+
	Gdiplus::GdiplusStartup(&_gdiplusToken, &_gdiplusStartupInput, NULL);

	// ���Ӱ� ���õ� �ʱ�ȭ�� �ʿ��� �׸���� ���⼭
	//InputManager::GetInstance()->Init(hwnd);	// ��ü�� ����
	TimeManager::getInstance()->init();
	ResourceManager::getInstance()->init();	// ��� ���ҽ� �ε�

	//// ���۾��� �������� ����
	_currScene = new GameScene();
	this->setGameState(_currScene);
	_currScene->init();
}

void Game::destroy()
{
	// ���Ӱ� ���õ� ������ �ʿ��� �׸���� ���⼭
	//InputManager::DestroyInstance();	// ��ü�� ����
	TimeManager::destroyInstance();

	//ResourceManager::GetInstance()->Destroy();

	//if (_currScene)
	//{
	//	_currScene->Destroy();
	//}
	SAFE_DELETE(_currScene);

	GdiplusShutdown(_gdiplusToken);
}

bool Game::update(float deltaTime)
{
	_currScene->update(deltaTime);
	return bPlay;

}
	// CurScene ���� ��û�� ������, ���� ���� ������� �ϰ�, �ش� �� ������Ʈ�� �����Ѵ�.
	//if (_nextScene)
	//{
	//	if (_currScene)
	//	{
	//		_currScene->Destroy();
	//		delete _currScene;
	//		_currScene = nullptr;
	//	}
	//	_currScene = _nextScene;
	//	_currScene->Init();

	//	_nextScene = nullptr;
	//}
	//InputManager::GetInstance()->Update();
	//if (_currScene)
	//{
	//	_currScene->Update(TimeManager::GetInstance()->GetDeltaTime());
	//	_currScene->PostUpdate(TimeManager::GetInstance()->GetDeltaTime());
	//}

void Game::Render()
{
	// ����Ʈ ���ۿ� ���簡 ��������, ����۴� �ʱ�ȭ
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, BLACKNESS);

	_currScene->Render(_hdcBack);

	// ���� ��ȭ���� ������ ��.
	// �ѹ� �׸��� �� �׷�����, ������ ����Ʈ ���ۿ� ����.
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY); // ��Ʈ �� : ��� ����

}

GameState* Game::getGameState()
{
	return gameState;
}

void Game::setGameState(GameState* state)
{
	gameState = state;
}
GameScene* Game::getGameScene()
{
	GameScene* gameScene = dynamic_cast<GameScene*>(Game::getInstance().getGameState());
	return gameScene;
}
void Game::changeBplay()
{
	bPlay = !bPlay;
}

bool Game::isHardMode()
{
	return hardMode;
}

void Game::swapDifficultyMode()
{
	hardMode = !hardMode;
}

//const SoundManager* Game::getSoundManager() const {
//	return &soundManager;
//}