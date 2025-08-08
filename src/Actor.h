#pragma once

#include "Component.h"

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
        auto it = std::remove_if(_components.begin(), _components.end(),
            [](Component* comp) {
                return dynamic_cast<T*>(comp) != nullptr;
            });

        for (auto iter = it; iter != _components.end(); ++iter)
        {
            delete* iter;
        }

        _components.erase(it, _components.end());
    }

protected:
    Vector _position = { 0, 0 };
    std::vector<Component*> _components;
};
