#pragma once
#include "Actor.h"
#include "ImageRenderer.h"
#include "Texture.h"

class Terrain : public Actor
{
    using Super = Actor;
public:
    Terrain(Vector pos);
    
    /*void update(float deltaTime) override;*/

    Vector worldToLocal(float worldX, float worldY) const;
    bool isSolid(int32 x, int32 y) const;

    // Collider를 통해 Lemming 충돌 체크에 사용 가능
    // Collider* getCollider() { return _collider.get(); }

private:
    int32 _width = 0;                  // 맵 가로
    int32 _height = 0;                 // 맵 세로
    ImageRenderer* _levelTexture = nullptr;
    vector<COLORREF> _pixelData;// 0: 통과, 1: 충돌
};
