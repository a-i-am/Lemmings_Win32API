#include "pch.h"
#include "Terrain.h"

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

	// �ȼ� �浹üũ�� ������ �����
	_pixelData.resize(_width * _height);

	float scaleX = (float)mapTexture->getoriginTextureWidth() / _width;
	float scaleY = (float)mapTexture->getoriginTextureHeight() / _height;

	// _bitmapInfo.bmiHeader.biBitCount : 32
	int biBitCount = 32;
	int rowStride = ((mapTexture->getoriginTextureWidth() * biBitCount + 31) / 32) * 4;

	// BGR(A) �� COLORREF ��ȯ (�ȼ� �浹)
	for (int y = 0; y < _height; ++y)
	{
		int srcY = (int)(y * scaleY);
		for (int x = 0; x < _width; ++x)
		{
			int srcX = (int)(x * scaleX);
			int rawDataIndex = (mapTexture->getoriginTextureHeight() - 1 - srcY) * rowStride + srcX * 4;

			BYTE blue = mapRawData[rawDataIndex + 0];
			BYTE green = mapRawData[rawDataIndex + 1];
			BYTE red = mapRawData[rawDataIndex + 2];

			_pixelData[y * _width + x] = RGB(red, green, blue);
		}
	}

	//}

	//	for (int y = 1; y < _height - 1; ++y)
	//{
	//	for (int x = 1; x < _width - 1; ++x)
	//	{
	//		COLORREF currentPixelColor = mapTexture->getPixelColor(x, y);
	//		
	//		// ���� �ȼ��� �������� �ƴϰ� ����� �ƴ� ��쿡�� �˻�
	//		// ����� ���� ����̹Ƿ� �浹 �������� ����
	//		if (currentPixelColor != RGB(0, 0, 0) && currentPixelColor != RGB(255, 255, 255))
	//		{
	//			bool isEdge = false;
	//			// (�ֺ� 8���� �˻� ����)
	//			// ...
	//			for (int dy = -1; dy <= 1; ++dy) {
	//				for (int dx = -1; dx <= 1; ++dx) {
	//					if (dx == 0 && dy == 0) continue;
	//					COLORREF neighborColor = mapTexture->getPixelColor(x + dx, y + dy);
	//					if (neighborColor == RGB(0, 0, 0))
	//					{
	//						isEdge = true;
	//						break;
	//					}
	//				}
	//				if (isEdge) break;
	//			}

	//			if (isEdge)
	//			{
	//				_pixelData[y * _width + x] = 1;
	//			}
	//		}
	//	}
	//}

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