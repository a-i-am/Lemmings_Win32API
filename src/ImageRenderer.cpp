#include "pch.h"
#include "ImageRenderer.h"
#include "ResourceManager.h"
#include "Texture.h"

ImageRenderer::ImageRenderer(string textureKey, int32 width, int32 height)
{
	_texture = ResourceManager::getInstance()->getTexture(textureKey);
}

void ImageRenderer::initComponent()
{
	Super::initComponent();
}

void ImageRenderer::updateComponent(float deltaTime)
{
	Super::updateComponent(deltaTime);
}

void ImageRenderer::renderComponent(HDC hdc, Vector pos)
{
	Super::renderComponent(hdc, pos);

	if (_texture == nullptr)
		return;

	_texture->render(hdc, pos, Vector(0, 0), Vector(_texture->getTextureWidth(), _texture->getTextureHeight()), Vector(1.f, 1.f), _applyCameraPos);
}