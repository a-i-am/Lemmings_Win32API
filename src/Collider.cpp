#include "pch.h"
#include "Collider.h"

Collider::Collider(Texture* texture)
	: _texture(texture)
{

}

// ���� ��ǥ -> Texture ��ǥ ��ȯ
Vector Collider::worldToTextureCoords(const Vector& worldPos) const
{
	// Texture�� ȭ�� �߾� �����̸� ��ǥ ����
	Vector texPos = worldPos;
	if (_texture->isCenterAligned())
	{
		texPos.x += _texture->getTextureWidth() / 2;
		texPos.y += _texture->getTextureHeight() / 2;
	}

	// �ȼ� ��ǥ�� ��ȯ (������)
	return Vector((int32)texPos.x, (int32)texPos.y);
}

// �浹 ���� üũ
bool Collider::isColliding(const Vector& worldPos) const
{
	Vector texPos = worldToTextureCoords(worldPos);

	// Texture ���� ����� �浹�� ó��
	if (texPos.x < 0 || texPos.y < 0 ||
		texPos.x >= _texture->getTextureWidth() ||
		texPos.y >= _texture->getTextureHeight())
		return true;

	int32 width = _texture->getTextureWidth();
	int32 height = _texture->getFrameHeight();
	int32 rowSize = width * 4;
	int invertedY = height - 1 - (int32)texPos.y; // BMP bottom-up ����
	int index = invertedY * rowSize + (int32)texPos.x * 4;

	BYTE* data = _texture->getRawData();

	BYTE red = data[index + 2];
	BYTE green = data[index + 1];
	BYTE blue = data[index + 0];

	if (red != 0 || green != 0 || blue != 0)
		return true;

	return false;
}