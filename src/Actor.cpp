#include "pch.h"
#include "Actor.h"

Actor::~Actor()
{
    for (Component* comp : _components)
        delete comp;
    _components.clear();
}
void Actor::init()
{
    for (Component* comp : _components)
        comp->initCompoent();
}

void Actor::update(float deltaTime)
{
    for (Component* comp : _components)
        comp->updateComponent(deltaTime);
}

void Actor::render(HDC hdc)
{
    for (Component* comp : _components)
        comp->renderComponent(hdc, _position);
}

void Actor::setPosition(Vector pos)
{
    _position = pos;
}

Vector Actor::getPosition() const
{
    return _position;
}

