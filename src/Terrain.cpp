#include "pch.h"
#include "Terrain.h"
#include "Collider.h"

Terrain::Terrain(Vector pos) : Super(pos)
{
}

void Terrain::load()
{
	// �ؽ�ó, �ݶ��̴� �ε�
	_levelTexture = CreateTextureComponent("map", GWinSizeX, GWinSizeY);
	_width = GWinSizeX;
	_height = GWinSizeY;
	
	Texture* mapTexture = _levelTexture->getTexture();
	BYTE* mapRawData = mapTexture->getRawData();


	_pixelData.resize(_width * _height);


	int rowSize = _width * 4; // 32bit �� 4����Ʈ per �ȼ�
	
	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
			int rawDataIndex = (_height - 1 - y) * (_width * 4) + x * 4;
			BYTE red = mapRawData[rawDataIndex + 2];
			BYTE green = mapRawData[rawDataIndex + 1];
			BYTE blue = mapRawData[rawDataIndex + 0];
			//BYTE alpha = _rawData[index + 3]; // ������� �ʾƵ� ����

			if (RGB(red, green, blue) == RGB(255, 255, 255)) 
			{
				_pixelData[y * _width + x] = 0;

				// ���� ����ũ ó��
				_pixelData[rawDataIndex + 2] = 0; 
				_pixelData[rawDataIndex + 1] = 0;
				_pixelData[rawDataIndex + 0] = 0;

				_pixelData[y * _width + x] = 0;
			}
			else
			{
				_pixelData[y * _width + x] = 1; // �浹 ����
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

// Ư�� ��ǥ�� �浹 �������� ����
bool Terrain::isSolid(int x, int y) const
{
	if (x < 0 || x >= _width || y < 0 || y >= _height)
		return false;
	return _pixelData[y * _width + x] != 0;
}

