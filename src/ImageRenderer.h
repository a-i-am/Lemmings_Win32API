#pragma once

#include "Component.h"
class Texture;

class ImageRenderer : public Component
{
	using Super = Component;
public:
	ImageRenderer(string textureKey);

	virtual void initCompoent() override;
	virtual void updateComponent(float deltaTime) override;
	virtual void renderComponent(HDC hdc, Vector pos) override;

	int32 getTextureWidth();
	Texture* getTexture() { return _textureInfo; }
	void setApplyCameraPos(bool apply) { _applyCameraPos = apply; }

private:
	Texture* _textureInfo = nullptr;	// ���ҽ� �Ŵ����� ���ؼ� ������ ���� : ���� �ڻ�
	bool _applyCameraPos = true;
};


