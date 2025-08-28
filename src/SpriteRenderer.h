#pragma once
#include "common_defs.h"
#include "Component.h"
#include "AnimData.h"

class Texture;

// �� �ؽ�ó �׸��Ⱑ �ƴ϶�, �ϳ��� �����Ӵ����� �׸��� ��ü
class SpriteRenderer : public Component
{
	using Super = Component;
public:
	SpriteRenderer(string textureKey, float dur);

	virtual void InitComponent() override;
	virtual void UpdateComponent(float deltaTime) override;
	virtual void RenderComponent(HDC hdc, Vector pos) override;
	bool IsEnd() { return _isEnd; }
	void ChangeAnimation(int32 animId);

	void SetLemmingAnimationData(int32 animId, int32 startIndex, int32 totalCount, bool flipX, bool loop);
	void SetAllDoorsAnimationData(int32 startIndex, int32 totalCount, bool isLoop, bool isEnd);
	void SetFrameSize(int32 sizeX, int32 sizeY)
	{
		_frameSizeX = sizeX, _frameSizeY = sizeY;
	}

	int32 GetSpriteWidth()  const { return  _spriteWidth; }
	int32 GetSpriteHeight() const { return _spriteHeight; }

	Texture* getTexture() { return _spriteSheet; }


private:
	vector<AnimData> _animations;
	Texture* _spriteSheet = nullptr; // ���ҽ� �Ŵ����� ���� ������ ���� : ���� �ڻ�

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

	int32 _currentAnimation = 0;
	int32 _currentFrameIndex = 0;

	// �� �����Ӵ� ������
	int32 _frameSizeX = 0;
	int32 _frameSizeY = 0;

	bool  _isEnd = false;
	bool _isFlipX = false;
	bool _isLoop = false;

	float _sumTime = 0.0f;
	float _duration = 0.1f; // �� ������ �� 0.1��(10fps)

};