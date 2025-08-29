#include "pch.h"
#include "Actor.h"
#include "Scene.h"
#include "Game.h"
#include "GameScene.h"
#include "ResourceManager.h"
#include "Component.h"
#include "SpriteRenderer.h"
#include "ImageRenderer.h"

Actor::Actor(Vector pos)
{
    _pos = pos;
}
Actor::~Actor()
{
    for (Component* comp : _components)
    {
        comp->setOwner(nullptr);
        delete comp;
    }
    _components.clear();
}
void Actor::Init()
{
    for (Component* comp : _components)
        comp->InitComponent();
}

void Actor::Update(float deltaTime)
{
    for (Component* comp : _components)
        comp->UpdateComponent(deltaTime);
}

void Actor::Render(HDC hdc)
{
    for (Component* comp : _components)
        comp->RenderComponent(hdc, _pos);
}

void Actor::SetPosition(Vector pos)
{
    _pos = pos;
}

Vector Actor::GetPosition() const
{
    return _pos;
}

SpriteRenderer* Actor::CreateSpriteComponent(string spriteInfo, float dur, int32 width, int32 height)
{
    SpriteRenderer* sprite = new SpriteRenderer(spriteInfo, dur);
    sprite->InitComponent();

    sprite->SetFrameSize(width, height);
    _components.emplace_back(sprite);
    return sprite;
}

ImageRenderer* Actor::CreateTextureComponent(string bitmapKey, int32 width, int32 height)
{
    ImageRenderer* sprite = new ImageRenderer(bitmapKey, width, height);
    sprite->InitComponent();

    sprite->getTexture()->SetTextureWidth(width);
    sprite->getTexture()->SetTextureHeight(height);
    _components.emplace_back(sprite);
    return sprite;
}
