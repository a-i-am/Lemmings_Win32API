#pragma once
#include "Component.h"

class Texture;

class ImageRenderer : public Component
{
	using Super = Component;
public:
	ImageRenderer(string textureKey, int32 width, int32 height);

	virtual void InitComponent() override;
	virtual void UpdateComponent(float deltaTime) override;
	virtual void RenderComponent(HDC hdc, Vector pos) override;

	Texture* getTexture() { return _texture; }

private:
	Texture* _texture = nullptr;	// 리소스 매니저를 통해서 가져온 정보 : 공용 자산
};

