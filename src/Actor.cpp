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
        comp->setOwner(nullptr); // 이 줄 추가 권장
        delete comp;
    }
    _components.clear();
}
void Actor::Init()
{
    for (Component* comp : _components)
        comp->initComponent();
}

void Actor::Update(float deltaTime)
{
    for (Component* comp : _components)
        comp->updateComponent(deltaTime);
}

void Actor::Render(HDC hdc)
{
    for (Component* comp : _components)
        comp->renderComponent(hdc, _pos);
}

void Actor::setPosition(Vector pos)
{
    _pos = pos;
}

Vector Actor::getPosition() const
{
    return _pos;
}





SpriteRenderer* Actor::CreateSpriteComponent(string spriteInfo, int32 dur, int32 width, int32 height)
{
    SpriteRenderer* sprite = new SpriteRenderer(spriteInfo, dur);
    sprite->setFrameSize(width, height, 1.0f, 1.0f);
    _components.emplace_back(sprite);
    return sprite;
}

ImageRenderer* Actor::CreateTextureComponent(string bitmapKey, int32 width, int32 height)
{
    ImageRenderer* sprite = new ImageRenderer(bitmapKey, width, height);
    sprite->getTexture()->SetTextureWidth(width);
    sprite->getTexture()->SetTextureHeight(height);
    _components.emplace_back(sprite);
    return sprite;
}
