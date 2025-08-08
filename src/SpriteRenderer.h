#pragma once
#include "Component.h"

class Texture;

// 통 텍스처 그리기가 아니라, 하나의 프레임단위로 그리는 객체
class SpriteRenderer : public Component
{
	using Super = Component;
public:
	SpriteRenderer(string textureKey, float dur);

	virtual void initComponent() override;
	virtual void updateComponent(float deltaTime) override;
	virtual void renderComponent(HDC hdc, Vector pos) override;
	bool IsEnd() { return _isEnd; }

	void setFrameRange(int32 startX, int32 startY, int32 countX, int32 countY);
	void setRenderSize(int32 sizeX, int32 sizeY) { _renderSizeX = sizeX, _renderSizeY = sizeY; }

private:

	Texture* _texture = nullptr; // 리소스 매니저를 통해 가져온 정보 : 공용 자산

	// 개별 텍스처가 현재 어떤 프레임을 그리고 있는지

	int32 _startFrameX = 0;
	int32 _startFrameY = 0;
	// 고정된 프레임 수
	int32 _frameCountX = 0;
	int32 _frameCountY = 0;
	// 현재 위치를 추적하는 변수
	int32 _currFrameX = 0;
	int32 _currFrameY = 0;



		
	// 한 프레임당 사이즈
	int32 _renderSizeX = 0;
	int32 _renderSizeY = 0;

	bool  _isEnd = false;

	float _duration = 0;
	float _sumTime = 0;

	bool _applyCameraPos = true;
};

/*
	void SetFrameX(int32 x) { _frameX = x; }
	void SetFrameY(int32 y) { _frameY = y; }
	void SetApplyCameraPos(bool apply) { _applyCameraPos = apply; }
*/