#pragma once
#include "Actor.h"
#include "Collider.h"
#include "ImageRenderer.h"

class Terrain : public Actor
{
    using Super = Actor;
public:
    Terrain(Vector pos);
    void load();
    Vector worldToLocal(float worldX, float worldY) const;
    bool isSolid(int x, int y) const;


    // Collider를 통해 Lemming 충돌 체크에 사용 가능
    // Collider* getCollider() { return _collider.get(); }

private:
    int _width = 0;                  // 맵 가로
    int _height = 0;                 // 맵 세로
    vector<BYTE> _pixelData;// 0: 통과, 1: 충돌
    ImageRenderer* _levelTexture;
};
