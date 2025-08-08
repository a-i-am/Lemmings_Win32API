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
		int32 renderSizeX = _texture->getFrameCountX() != 0 ? (_texture->getTextureWidth() / _texture->getFrameCountX()) : _texture->getTextureWidth();
		int32 renderSizeY = _texture->getFrameCountY() != 0 ? (_texture->getTextureHeight() / _texture->getFrameCountY()) : _texture->getTextureHeight();
	
		_renderSizeX = renderSizeX;
		_renderSizeY = renderSizeY;
	}

}

void SpriteRenderer::initComponent()
{
	Super::initComponent();
}

void SpriteRenderer::updateComponent(float deltaTime)
{
	Super::updateComponent(deltaTime);


	if (_duration == 0 || _isEnd || _texture == nullptr)
		return;

	// 본인의 프레임을 계산하는 로직
	_sumTime += deltaTime;

	_frameCountX = _texture->getFrameCountX();
	_frameCountY = _texture->getFrameCountY();

	int32 totalCount = _frameCountX * _frameCountY;
	float delta = _duration / totalCount;

	// 일정 시간이 지나면 다음 프레임 이동
	if (_sumTime >= delta && _isEnd == false)
	{
		if (_currFrameX + 1 >= _frameCountX)
		{
			_currFrameX = 0;

			if (_currFrameY + 1 >= _frameCountY)
			{
				_currFrameY = 0;

				//if (bitmapInfo->loop == false)
				{
					_isEnd = true; // 루프 끊기. 반복하고 싶으면 여길 빼야 함
				}
			}
			else
			{
				++_currFrameY;
			}
		}
		else
		{
			++_currFrameX;
		}

		_sumTime -= delta;
	}
}

void SpriteRenderer::renderComponent(HDC hdc, Vector pos)
{
	Super::renderComponent(hdc, pos);

	if (_texture == nullptr)
		return;

	int32 frameX = _startFrameX + _currFrameX;
	int32 frameY = _startFrameY + _currFrameY;

	// 원본텍스처의 시작 위치를 계산한다.
	// 텍스처의 특정 frame 으로 그려야 해서
	int32 srcX = frameX * _renderSizeX;
	int32 srcY = frameY * _renderSizeY;

	_texture->render(hdc, pos, Vector(srcX, srcY), Vector(_renderSizeX, _renderSizeY), _applyCameraPos);
}

void SpriteRenderer::setFrameRange(int32 startX, int32 startY, int32 countX, int32 countY)
{
	_startFrameX = startX;
	_startFrameY = startY;
	_frameCountX = countX;
	_frameCountY = countY;

	_currFrameX = 0;
	_currFrameY = 0;
	_isEnd = false;
	_sumTime = 0.0f;
}