#pragma once
#include "Component.h"

class Texture;

class ImageRenderer : public Component
{
	using Super = Component;
public:
	ImageRenderer(string textureKey);

	virtual void initComponent() override;
	virtual void updateComponent(float deltaTime) override;
	virtual void renderComponent(HDC hdc, Vector pos) override;

	Texture* getTexture() { return _texture; }
	void setApplyCameraPos(bool apply) { _applyCameraPos = apply; }

private:
	Texture* _texture = nullptr;	// ���ҽ� �Ŵ����� ���ؼ� ������ ���� : ���� �ڻ�
	bool _applyCameraPos = true;
};

