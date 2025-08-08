#pragma once

#include "Component.h"
#include <vector>

class Actor
{
public:
    virtual ~Actor();

    void init();
    void update(float deltaTime);
    void render(HDC hdc);

    void setPosition(Vector pos);
    Vector getPosition() const;

    // 구현 포함된 템플릿 함수들
    template <typename T, typename... Args>
    T* addComponent(Args&&... args)
    {
        T* component = new T(std::forward<Args>(args)...);
        component->setOwner(this);
        _components.push_back(component);
        return component;
    }

    template <typename T>
    T* getComponent()
    {
        for (Component* comp : _components)
        {
            if (T* casted = dynamic_cast<T*>(comp))
                return casted;
        }
        return nullptr;
    }

    template <typename T>
    void removeComponent()
    {
        for (auto it = _components.begin(); it != _components.end(); ++it)
        {
            if (dynamic_cast<T*>(*it))
            {
                delete* it;
                _components.erase(it);
                return;
            }
        }
    }

protected:
    Vector _position = { 0, 0 };
    std::vector<Component*> _components;
};
