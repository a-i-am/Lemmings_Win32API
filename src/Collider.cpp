#include "pch.h"
#include "Collider.h"

Collider::Collider(Texture* texture)
	: _texture(texture)
{

}

// 월드 좌표 -> Texture 좌표 변환
Vector Collider::worldToTextureCoords(const Vector& worldPos) const
{
	// Texture가 화면 중앙 정렬이면 좌표 보정
	Vector texPos = worldPos;
	if (_texture->isCenterAligned())
	{
		texPos.x += _texture->getTextureWidth() / 2;
		texPos.y += _texture->getTextureHeight() / 2;
	}

	// 픽셀 좌표로 변환 (정수형)
	return Vector((int32)texPos.x, (int32)texPos.y);
}

// 충돌 여부 체크
bool Collider::isColliding(const Vector& worldPos) const
{
	Vector texPos = worldToTextureCoords(worldPos);

	// Texture 범위 벗어나면 충돌로 처리
	if (texPos.x < 0 || texPos.y < 0 ||
		texPos.x >= _texture->getTextureWidth() ||
		texPos.y >= _texture->getTextureHeight())
		return true;

	int32 width = _texture->getTextureWidth();
	int32 height = _texture->getFrameHeight();
	int32 rowSize = width * 4;
	int invertedY = height - 1 - (int32)texPos.y; // BMP bottom-up 보정
	int index = invertedY * rowSize + (int32)texPos.x * 4;

	BYTE* data = _texture->getRawData();

	BYTE red = data[index + 2];
	BYTE green = data[index + 1];
	BYTE blue = data[index + 0];

	if (red != 0 || green != 0 || blue != 0)
		return true;

	return false;
}