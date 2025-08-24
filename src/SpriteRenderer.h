#pragma once
#include "Component.h"
#include "common_defs.h"

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

	void setAnimationClip(int32 startIndex, int32 totalCount);
	void setFrameSize(int32 sizeX, int32 sizeY, float xRatio, float yRatio)
	{
		_frameSizeX = sizeX, _frameSizeY = sizeY;
		_frameRatioX = xRatio, _frameRatioY = yRatio;
	}

	int32 getSpriteWidth()  const { return  _spriteWidth; }
	int32 getSpriteHeight() const { return _spriteHeight; }

	Texture* getTexture() { return _texture; }

	int32 srcX = 0;
	int32 srcY = 0;






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


	int32 _spriteWidth = 16;
	int32 _spriteHeight = 16;
	float _scale = 3.f;

	// 프레임 수 기반 애니메이션 재생
	int32 _startFrameIndex = 0;
	int32 _totalFrameCount = 0;
	int32 _framePerRow = 0;
	int32 _framePerCol = 0;

	int32 _currentFrameIndex = 0;

	// 한 프레임당 사이즈
	int32 _frameSizeX = 0;
	int32 _frameSizeY = 0;

	float _frameRatioX = 0.f;
	float _frameRatioY = 0.f;


	bool  _isEnd = false;

	float _sumTime = 0.0f;
	float _duration = 0.1f; // 한 프레임 당 0.1초(10fps)
};