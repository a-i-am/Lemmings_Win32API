#include "pch.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Texture.h"

SpriteRenderer::SpriteRenderer(string textureKey, float dur)
{
	_animations.clear();
	_spriteSheet = ResourceManager::getInstance()->getTexture(textureKey);
	_duration = dur;

	// 한 프레임의 사이즈를 미리 계산
	// TextureInfo에 추가하는 걸 고려 : 공용 자산. 객체마다 다르게 적용할 일이 없게
	if (_spriteSheet)
	{
		_frameSizeX = _spriteSheet->GetFrameCountX() != 0 ?
			(_spriteSheet->GetTextureWidth() / _spriteSheet->GetFrameCountX()) : _spriteSheet->GetTextureWidth();
		_frameSizeY = _spriteSheet->GetFrameCountY() != 0 ?
			(_spriteSheet->GetTextureHeight() / _spriteSheet->GetFrameCountY()) : _spriteSheet->GetTextureHeight();
	}
	_currentAnimation = 0;
	_currentFrameIndex = 0;
	_sumTime = 0.f;
	_isFlipX = false;
}

void SpriteRenderer::SetLemmingAnimationData(int32 animId, int32 startIndex, int32 totalCount, bool isFlipX, bool isLoop)
{
	if (animId < 0)
		return;

	if (animId >= int32(_animations.size()))
		_animations.resize(animId + 1);

	// 먼저 AnimData를 초기화
	_animations[animId].startIndex = startIndex;
	_animations[animId].totalCount = totalCount;
	_animations[animId].isFlipX = isFlipX;
	_animations[animId].isLoop = isLoop;
	_animations[animId].isEnd = false;

	// 그 다음에 현재 애니메이션으로 지정
	_currentAnimation = animId;
	_currentFrameIndex = startIndex;
	_startFrameIndex = startIndex;
	_totalFrameCount = totalCount;
	_isFlipX = isFlipX;
	_isLoop = isLoop;
	_isEnd = false;
}

void SpriteRenderer::SetAllDoorsAnimationData(int32 startIndex, int32 totalCount, bool isLoop, bool isEnd)
{
	_startFrameIndex = startIndex;
	_totalFrameCount = totalCount;
	_isLoop = isLoop;
	_isEnd = isEnd;
}

void SpriteRenderer::ChangeAnimation(int32 animId)
{
	if (animId >= int32(_animations.size())) return;
	
	_currentAnimation = animId;
	_isFlipX = _animations[_currentAnimation].isFlipX;
	_isLoop = _animations[_currentAnimation].isLoop;
	_isEnd = _animations[_currentAnimation].isEnd;
	
	_currentFrameIndex = 0;
	_sumTime = 0.f;

	_animations[_currentAnimation].isEnd = false;
}


void SpriteRenderer::InitComponent()
{
	Super::InitComponent();
}

void SpriteRenderer::UpdateComponent(float deltaTime)
{
	Super::UpdateComponent(deltaTime);

	if (_duration == 0 || _spriteSheet == nullptr || _totalFrameCount <= 0)
		return;

	_sumTime += deltaTime;

	if (_currentAnimation >= 0 && _currentAnimation < (int32)_animations.size())
	{
		float delta = _duration / _animations[_currentAnimation].totalCount;

		while (_sumTime >= delta)
		{
			_currentFrameIndex++;
			_sumTime -= delta;

			if (_currentFrameIndex >= _animations[_currentAnimation].totalCount)
			{
				if (_isLoop)
				{
					_currentFrameIndex = 0;
				}
				else
				{
					_currentFrameIndex = _animations[_currentAnimation].totalCount - 1;
					_isEnd = true;
				}
			}
		}
	}
	else
	{
		float delta = _duration / _totalFrameCount;

		while (_sumTime >= delta)
		{
			_currentFrameIndex++;
			_sumTime -= delta;

			if (_currentFrameIndex >= _totalFrameCount)
			{
				if (_isLoop)
				{
					_currentFrameIndex = 0;
				}
				else
				{
					_currentFrameIndex = _totalFrameCount - 1;
				}
			}
		}
	}

	

}

void SpriteRenderer::RenderComponent(HDC hdc, Vector pos)
{
	if (_spriteSheet == nullptr)
		return;

	Super::RenderComponent(hdc, pos);

	int32 frameIndex = _startFrameIndex + _currentFrameIndex;

	int32 frameX = frameIndex % _spriteSheet->GetFrameCountX();
	int32 frameY = frameIndex / _spriteSheet->GetFrameCountX();

	// 원본텍스처의 시작 위치를 계산한다.
	// 텍스처의 특정 frame 으로 그려야 해서
	int32 srcX = frameX * _spriteSheet->GetFrameWidth();
	int32 srcY = frameY * _spriteSheet->GetFrameHeight();

	_spriteSheet->Render(hdc, pos, Vector(srcX, srcY), Vector(_frameSizeX, _frameSizeY), _isFlipX);
}

