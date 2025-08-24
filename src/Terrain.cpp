#include "pch.h"
#include "Terrain.h"

Terrain::Terrain(Vector pos) : Super(pos)
{
	// TODO : 레벨1 완성 후 리팩토링. 지금은 일단 기능 구현부터 하자.
	// 1. _width와 _height = GetTexture()로 원본 사이즈 가지고 오기
	// CreateTextureComponent("map", _width, _height); 를 key만 만들 수 있게 매개변수 제거
	// CreateSpriteComponent도 마찬가지. 현재 GameScene에서 하드코딩 되어있는 상태.
	// 2. SetTexture() * scale 로 실제 출력 사이즈 설정 
	// ex) terrain->_levelTexture->getTexture()->SetTextureWidth(1024) * scale;
	
	// 레벨1 맵 원본 사이즈 : 512 * 256
	//int32 scale = 3;
	_width = GWinSizeX;
	_height = GWinSizeY;

	_levelTexture = CreateTextureComponent("map", _width, _height);
	// 레벨 텍스처가 제대로 초기화 되어야 충돌 데이터를 생성할 수 있다. 
	_levelTexture->getTexture()->GenerateCollisionData(_width, _height);

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
	return _levelTexture->getTexture()->GetPixelData()[y * _width + x] != 0;
}

