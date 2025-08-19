#pragma once
#include "Texture.h"
#include "Terrain.h"
class Collider
{
public:
	explicit Collider(Texture* texture);

	// ���� ��ǥ�� �޾Ƽ� �浹 ���� ��ȯ
	bool isColliding(const Vector& worldPos) const;

	// Texture ��ǥ ��ȯ �Լ�
	Vector worldToTextureCoords(const Vector& worldPos) const;

private:
	Texture* _texture;

};