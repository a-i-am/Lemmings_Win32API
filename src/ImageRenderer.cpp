#include "pch.h"
#include "ImageRenderer.h"
#include "ResourceManager.h"
#include "Texture.h"

ImageRenderer::ImageRenderer(string textureKey, int32 width, int32 height)
{
	_texture = ResourceManager::getInstance()->getTexture(textureKey);
}

void ImageRenderer::InitComponent()
{
	Super::InitComponent();
}

void ImageRenderer::UpdateComponent(float deltaTime)
{
	Super::UpdateComponent(deltaTime);
}

void ImageRenderer::RenderComponent(HDC hdc, Vector pos)
{
	Super::RenderComponent(hdc, pos);

	if (_texture == nullptr)
		return;

	_texture->Render(hdc, pos, Vector(0, 0), Vector(_texture->GetTextureWidth(), _texture->GetTextureHeight()));
}