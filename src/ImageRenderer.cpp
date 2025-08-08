#include "pch.h"
#include "ImageRenderer.h"
#include "ResourceManager.h"
#include "Texture.h"

ImageRenderer::ImageRenderer(string textureKey)
{
	_textureInfo = ResourceManager::getInstance()->getTextureInfo(textureKey);
}

void ImageRenderer::initCompoent()
{
	Super::initCompoent();
}

void ImageRenderer::updateComponent(float deltaTime)
{
	Super::updateComponent(deltaTime);
}

void ImageRenderer::renderComponent(HDC hdc, Vector pos)
{
	Super::renderComponent(hdc, pos);

	if (_textureInfo == nullptr)
		return;

	_textureInfo->render(hdc, pos, Vector(0, 0), Vector(_textureInfo->_sizeX, _textureInfo->_sizeY), _applyCameraPos);
}

int32 ImageRenderer::getTextureWidth()
{
	return _textureInfo->getTextureWidth();
}