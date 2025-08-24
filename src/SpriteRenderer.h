#pragma once
#include "Component.h"
#include "common_defs.h"

class Texture;

// �� �ؽ�ó �׸��Ⱑ �ƴ϶�, �ϳ��� �����Ӵ����� �׸��� ��ü
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
	Texture* _texture = nullptr; // ���ҽ� �Ŵ����� ���� ������ ���� : ���� �ڻ�

	// ���� �ؽ�ó�� ���� � �������� �׸��� �ִ���

	int32 _startFrameX = 0;
	int32 _startFrameY = 0;

	// ������ ������ ��
	int32 _frameCountX = 0;
	int32 _frameCountY = 0;
	// ���� ��ġ�� �����ϴ� ����
	int32 _currFrameX = 0;
	int32 _currFrameY = 0;


	int32 _spriteWidth = 16;
	int32 _spriteHeight = 16;
	float _scale = 3.f;

	// ������ �� ��� �ִϸ��̼� ���
	int32 _startFrameIndex = 0;
	int32 _totalFrameCount = 0;
	int32 _framePerRow = 0;
	int32 _framePerCol = 0;

	int32 _currentFrameIndex = 0;

	// �� �����Ӵ� ������
	int32 _frameSizeX = 0;
	int32 _frameSizeY = 0;

	float _frameRatioX = 0.f;
	float _frameRatioY = 0.f;


	bool  _isEnd = false;

	float _sumTime = 0.0f;
	float _duration = 0.1f; // �� ������ �� 0.1��(10fps)
};