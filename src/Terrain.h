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


    // Collider�� ���� Lemming �浹 üũ�� ��� ����
    // Collider* getCollider() { return _collider.get(); }

private:
    int _width = 0;                  // �� ����
    int _height = 0;                 // �� ����
    vector<BYTE> _pixelData;// 0: ���, 1: �浹
    ImageRenderer* _levelTexture;
};
