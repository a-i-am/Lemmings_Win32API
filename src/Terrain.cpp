#include "pch.h"
#include "Terrain.h"

Terrain::Terrain(Vector pos) : Super(pos)
{
}

void Terrain::load()
{
	_width = GWinSizeX;
	_height = GWinSizeY;
	
	_levelTexture = CreateTextureComponent("map", _width, _height);
	_levelTexture->getTexture()->generateCollisionData(_width, _height);

}
//
//void Terrain::update(float deltaTime)
//{
//	_levelTexture->updateComponent(deltaTime);
//}

Vector Terrain::worldToLocal(float worldX, float worldY) const
{
	const Vector& terrainPos = getPosition();
	float mapLeft = terrainPos.x - (_width * 0.5f);
	float mapTop = terrainPos.y - (_height * 0.5f);
	return Vector{ worldX - mapLeft, worldY - mapTop };
}

// 특정 좌표가 충돌 영역인지 판정
bool Terrain::isSolid(int32 x, int32 y) const
{
	if (x < 0 || x >= _width || y < 0 || y >= _height)
		return false;
	return _levelTexture->getTexture()->getPixelData()[y * _width + x] != 0;
}

int Terrain::getGroundY(float x, float startY, float maxCheckDist)
{
	for (int dy = 0; dy < maxCheckDist; ++dy)
	{
		int checkY = static_cast<int>(startY + dy);
		if (isSolid(x, checkY))
		{
			return checkY; // 제일 먼저 닿은 픽셀의 Y 좌표
		}
	}
	return -1; // 못 찾음
}
