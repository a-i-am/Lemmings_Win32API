#pragma once
#include "Component.h"

class Texture;

class ImageRenderer : public Component
{
	using Super = Component;
public:
	ImageRenderer(string textureKey, int32 width, int32 height);

	virtual void initComponent() override;
	virtual void updateComponent(float deltaTime) override;
	virtual void renderComponent(HDC hdc, Vector pos) override;

	Texture* getTexture() { return _texture; }
	void setApplyCameraPos(bool apply) { _applyCameraPos = apply; }

private:
	Texture* _texture = nullptr;	// 리소스 매니저를 통해서 가져온 정보 : 공용 자산
	bool _applyCameraPos = true;
};

