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

    // Collider�� ���� Lemming �浹 üũ�� ��� ����
    // Collider* getCollider() { return _collider.get(); }

private:
    int32 _width = 0;                  // �� ����
    int32 _height = 0;                 // �� ����
    ImageRenderer* _levelTexture = nullptr;
    vector<COLORREF> _pixelData;// 0: ���, 1: �浹
};
