#pragma once
#include "Component.h"

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

	void setFrameRange(int32 startX, int32 startY, int32 countX, int32 countY);
	void setRenderSize(int32 sizeX, int32 sizeY) { _renderSizeX = sizeX, _renderSizeY = sizeY; }

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



		
	// �� �����Ӵ� ������
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