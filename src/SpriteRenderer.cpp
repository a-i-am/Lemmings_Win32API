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
void SpriteRenderer::SetAllDoorsAnimationData(int32 startIndex, int32 totalCount, bool isLoop, bool isEnd)
{
	_startFrameIndex = startIndex;
	_totalFrameCount = totalCount;
	_framePerRow = _spriteSheet->GetFrameCountX(); // 자동 계산
	_framePerCol = _spriteSheet->GetFrameCountY();
	_currentFrameIndex = 0;
	_isLoop = isLoop;
	_isEnd = isEnd;
	_sumTime = 0.f;
}

void SpriteRenderer::SetLemmingAnimationData(int32 animId, int32 startIndex, int32 totalCount, bool isFlipX, bool isLoop)
{
	if (animId < 0)
		return;

	if (animId >= int32(_animations.size()))
		_animations.resize(animId + 1);

	// AnimData 초기화
	_animations[animId].startIndex = startIndex;
	_animations[animId].totalCount = totalCount;
	_animations[animId].isFlipX = isFlipX;
	_animations[animId].isLoop = isLoop;
	_animations[animId].isEnd = false;

	_currentFrameIndex = 0;
}

void SpriteRenderer::PlayLemmingAnimation(int32 animId)
{
	if (animId >= int32(_animations.size())) return;

	// 만약 이미 같은 애니메이션이 재생 중이라면, 아무것도 하지 않음.
		// (또는 필요에 따라 같은 애니메이션을 다시 재생하도록 허용할 수 있습니다)
	if (_currentAnimation == animId) return;

	_currentAnimation = animId;

	// 새로운 애니메이션이 재생될 때 프레임 인덱스와 시간을 초기화합니다.
	_currentFrameIndex = 0;
	_sumTime = 0.f;
	_isEnd = false;
	_isLoop = _animations[animId].isLoop;
}

void SpriteRenderer::InitComponent()
{
	Super::InitComponent();
}
void SpriteRenderer::UpdateComponent(float deltaTime)
{
	Super::UpdateComponent(deltaTime);

	if (_duration == 0 || _isEnd || _spriteSheet == nullptr)
		return;

	_sumTime += deltaTime;

	int32 myTotalAnimIndexCount = 0;
	float myDelta = 0.f;
	bool lemmingFlipX = false;

	if (_currentAnimation >= 0 && _currentAnimation < (int32)_animations.size())
	{	// 레밍 애니메이션 전용(상태에 따라 전환이 필요해서 AnimData로 따로 관리)
		myTotalAnimIndexCount = _animations[_currentAnimation].totalCount;
		lemmingFlipX = _animations[_currentAnimation].isFlipX;

		float delta = _duration / myTotalAnimIndexCount;
		myDelta = delta;
	}
	else
	{
		// 레밍 외 다른 액터들 애니메이션 전용
		myTotalAnimIndexCount = _totalFrameCount;
		float delta = _duration / _totalFrameCount;
		myDelta = delta;
	}

		while (_sumTime >= myDelta)
		{
			if (lemmingFlipX)
			{
				_currentFrameIndex = _animations[_currentAnimation].startIndex;
				_currentFrameIndex--;
				_sumTime -= myDelta;

				if (_currentFrameIndex <= myTotalAnimIndexCount)
				{
					if (_isLoop)
					{
						_currentFrameIndex = _animations[_currentAnimation].startIndex;
					}
					else
					{
						_currentFrameIndex = myTotalAnimIndexCount - 1;
						_isEnd = true;
					}
				}
			}
			else
			{
				_currentFrameIndex++;
				_sumTime -= myDelta;
				if (_currentFrameIndex >= myTotalAnimIndexCount)
				{
					if (_isLoop)
					{
						_currentFrameIndex = 0;
					}
					else
					{
						_currentFrameIndex = myTotalAnimIndexCount - 1;
						_isEnd = true;
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
	
	int32 lemmingFrameIndex = 0;
	int32 frameIndex = 0;

	int32 frameX = 0;
	int32 frameY = 0;


	if (_currentAnimation >= 0 && _currentAnimation < (int32)_animations.size())
	{
		lemmingFrameIndex = _animations[_currentAnimation].startIndex + _currentFrameIndex;
		frameX = lemmingFrameIndex % _spriteSheet->GetFrameCountX();
		frameY = lemmingFrameIndex / _spriteSheet->GetFrameCountX();
	}
	else
	{
		frameIndex = _startFrameIndex + _currentFrameIndex;
		frameX = frameIndex % _spriteSheet->GetFrameCountX();
		frameY = frameIndex / _spriteSheet->GetFrameCountX();
	}

	// 원본텍스처의 시작 위치를 계산한다.
	// 텍스처의 특정 frame 으로 그려야 해서
	int32 srcX = frameX * _spriteSheet->GetFrameWidth();
	int32 srcY = frameY * _spriteSheet->GetFrameHeight();


	_spriteSheet->Render(hdc, pos, Vector(srcX, srcY), Vector(_frameSizeX, _frameSizeY), _isFlipX);
	
}
