#include "pch.h"
#include "ImageRenderer.h"
#include "ResourceManager.h"
#include "Texture.h"

ImageRenderer::ImageRenderer(string textureKey, int32 width, int32 height)
{
	_texture = ResourceManager::GetInstance()->GetTexture(textureKey);
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

	// ÀÌ¹ÌÁö ·»´õ·¯ = ¸Ê = FlipX false
	_texture->Render(hdc, pos, Vector(0, 0), Vector(_texture->GetTextureWidth(), _texture->GetTextureHeight()), false);
}