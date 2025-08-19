#include "pch.h"
#include "Terrain.h"
#include "Collider.h"

Terrain::Terrain(Vector pos) : Super(pos)
{
}

void Terrain::load()
{
	// 텍스처, 콜라이더 로드
	_levelTexture = CreateTextureComponent("map", GWinSizeX, GWinSizeY);
	_width = GWinSizeX;
	_height = GWinSizeY;
	
	Texture* mapTexture = _levelTexture->getTexture();
	BYTE* mapRawData = mapTexture->getRawData();


	_pixelData.resize(_width * _height);


	int rowSize = _width * 4; // 32bit → 4바이트 per 픽셀
	
	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
			int rawDataIndex = (_height - 1 - y) * (_width * 4) + x * 4;
			BYTE red = mapRawData[rawDataIndex + 2];
			BYTE green = mapRawData[rawDataIndex + 1];
			BYTE blue = mapRawData[rawDataIndex + 0];
			//BYTE alpha = _rawData[index + 3]; // 사용하지 않아도 무방

			if (RGB(red, green, blue) == RGB(255, 255, 255)) 
			{
				_pixelData[y * _width + x] = 0;

				// 알파 마스크 처리
				_pixelData[rawDataIndex + 2] = 0; 
				_pixelData[rawDataIndex + 1] = 0;
				_pixelData[rawDataIndex + 0] = 0;

				_pixelData[y * _width + x] = 0;
			}
			else
			{
				_pixelData[y * _width + x] = 1; // 충돌 가능
			}
		}
	}
}

Vector Terrain::worldToLocal(float worldX, float worldY) const
{
	const Vector& terrainPos = getPosition();
	float mapLeft = terrainPos.x - (_width * 0.5f);
	float mapTop = terrainPos.y - (_height * 0.5f);
	return Vector{ worldX - mapLeft, worldY - mapTop };
}

// 특정 좌표가 충돌 영역인지 판정
bool Terrain::isSolid(int x, int y) const
{
	if (x < 0 || x >= _width || y < 0 || y >= _height)
		return false;
	return _pixelData[y * _width + x] != 0;
}

