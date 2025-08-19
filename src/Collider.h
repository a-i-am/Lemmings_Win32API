#pragma once
#include "Texture.h"
#include "Terrain.h"
class Collider
{
public:
	explicit Collider(Texture* texture);

	// 월드 좌표를 받아서 충돌 여부 반환
	bool isColliding(const Vector& worldPos) const;

	// Texture 좌표 변환 함수
	Vector worldToTextureCoords(const Vector& worldPos) const;

private:
	Texture* _texture;

};