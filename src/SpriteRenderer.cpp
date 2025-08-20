#include "pch.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Texture.h"

SpriteRenderer::SpriteRenderer(string textureKey, float dur)
{
	_texture = ResourceManager::getInstance()->getTexture(textureKey);
	_duration = dur;

	// �� �������� ����� �̸� ���
	// TextureInfo�� �߰��ϴ� �� ��� : ���� �ڻ�. ��ü���� �ٸ��� ������ ���� ����
	if (_texture)
	{
		int32 frameSizeX = _texture->getFrameCountX() != 0 ? (_texture->getTextureWidth() / _texture->getFrameCountX()) : _texture->getTextureWidth();
		int32 frameSizeY = _texture->getFrameCountY() != 0 ? (_texture->getTextureHeight() / _texture->getFrameCountY()) : _texture->getTextureHeight();
	
		_frameSizeX = frameSizeX;
		_frameSizeY = frameSizeY;
	}

}

void SpriteRenderer::initComponent()
{
	Super::initComponent();
}

void SpriteRenderer::updateComponent(float deltaTime)
{
	Super::updateComponent(deltaTime);

	if (_duration == 0 || _isEnd || _texture == nullptr || _totalFrameCount <= 0)
		return;

	_sumTime += deltaTime;

	float delta = _duration / _totalFrameCount;

	while (_sumTime >= delta)
	{
		_currentFrameIndex++;
		_sumTime -= delta;

		if (_currentFrameIndex >= _totalFrameCount)
		{
			_currentFrameIndex = 0;

			_isEnd = false; // �����Ϸ��� false�� ����
		}
	}

}

void SpriteRenderer::renderComponent(HDC hdc, Vector pos)
{
	Super::renderComponent(hdc, pos);

	if (_texture == nullptr)
		return;

	int32 frameIndex = _startFrameIndex + _currentFrameIndex;

	int32 frameX = frameIndex % _framePerRow;
	int32 frameY = frameIndex / _framePerRow;

	// �����ؽ�ó�� ���� ��ġ�� ����Ѵ�.
	// �ؽ�ó�� Ư�� frame ���� �׷��� �ؼ�
	int32 srcX = frameX * _texture->getFrameWidth();
	int32 srcY = frameY * _texture->getFrameHeight();



	_texture->render(hdc, pos, Vector(srcX, srcY),
		Vector(_frameSizeX, _frameSizeY), Vector(_frameRatioX, _frameRatioY)
		);
}

void SpriteRenderer::setAnimationClip(int32 startIndex, int32 totalCount)
{
	_startFrameIndex = startIndex;
	_totalFrameCount = totalCount;
	_framePerRow = _texture->getFrameCountX(); // �ڵ� ���
	_framePerCol = _texture->getFrameCountY();
 	_currentFrameIndex = 0;
	_isEnd = false;
	_sumTime = 0.f;
}