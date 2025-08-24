#include "pch.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Texture.h"

SpriteRenderer::SpriteRenderer(string textureKey, float dur)
{
	_texture = ResourceManager::getInstance()->getTexture(textureKey);
	_duration = dur;

	// 한 프레임의 사이즈를 미리 계산
	// TextureInfo에 추가하는 걸 고려 : 공용 자산. 객체마다 다르게 적용할 일이 없게
	if (_texture)
	{
		int32 frameSizeX = _texture->GetFrameCountX() != 0 ? (_texture->GetTextureWidth() / _texture->GetFrameCountX()) : _texture->GetTextureWidth();
		int32 frameSizeY = _texture->GetFrameCountY() != 0 ? (_texture->GetTextureHeight() / _texture->GetFrameCountY()) : _texture->GetTextureHeight();
	
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

			_isEnd = false; // 루프하려면 false로 수정
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

	// 원본텍스처의 시작 위치를 계산한다.
	// 텍스처의 특정 frame 으로 그려야 해서
	srcX = frameX * _texture->GetFrameWidth();
	srcY = frameY * _texture->GetFrameHeight();



	_texture->Render(hdc, pos, Vector(srcX, srcY), Vector(_frameSizeX, _frameSizeY));
}

void SpriteRenderer::setAnimationClip(int32 startIndex, int32 totalCount)
{
	_startFrameIndex = startIndex;
	_totalFrameCount = totalCount;
	_framePerRow = _texture->GetFrameCountX(); // 자동 계산
	_framePerCol = _texture->GetFrameCountY();
 	_currentFrameIndex = 0;
	_isEnd = false;
	_sumTime = 0.f;
}