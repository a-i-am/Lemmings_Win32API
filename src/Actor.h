#pragma once

#include "Component.h"

class Actor
{
public:
    Actor(Vector pos);
    virtual ~Actor();

    virtual void init();
    virtual void update(float deltaTime);
    virtual void Render(HDC hdc);

    void setPosition(Vector pos);
    Vector getPosition() const;


    // 구현 포함된 템플릿 함수들
    //template <typename T, typename... Args>
    //T* addComponent(Args&&... args)
    //{
    //    T* component = new T(std::forward<Args>(args)...);
    //    component->setOwner(this);
    //    _components.push_back(component);
    //    return component;
    //}

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

//protected:
    class SpriteRenderer* CreateSpriteComponent(string spriteInfo, int32 dur, int32 width = 0, int32 height = 0);
    class ImageRenderer* CreateTextureComponent(string bitmapKey, int32 width = 0, int32 height = 0);
    
    // 충돌은 Actor가 거의 레밍 혹은 레벨 뿐이고 레벨도 통 이미지니까 픽셀 충돌로 처리

protected:
    Vector _pos = {};
	vector<Component*> _components;
};
