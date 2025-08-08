#include "pch.h"
#include "Texture.h"
#include "Game.h"
#include "ResourceManager.h"

Texture::Texture()
{

}

void Texture::load(string key, string texturePath, int32 transparent, int32 xFrameCount, int32 yFrameCount)
{
	// BMP Texture Load 
	
	// 1. WinAPI �ؽ�ó �ε�
	fs::path fullPath = fs::current_path() / L"../Resources/images/" / texturePath;
	HDC hdc = GetDC(Game::getInstance().getHwnd());
	
	HDC textureHdc = ::CreateCompatibleDC(hdc);
	HBITMAP bitmap = (HBITMAP)::LoadImageW(nullptr, fullPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (bitmap == 0)
	{
		::MessageBox(Game::getInstance().getHwnd(), fullPath.c_str(), L"Invalid Texture Load", MB_OK);
		return;
	}
	
	HBITMAP prev = (HBITMAP)::SelectObject(textureHdc, bitmap);
	::DeleteObject(prev);

	BITMAP bit = {};
	::GetObject(bitmap, sizeof(BITMAP), &bit);


	// 2. TextureInfo ����

	_hBitmap = bitmap;
	_hdc = textureHdc;
	_transparent = transparent;
	_originTexSizeX = bit.bmWidth;
	_originTexSizeY = bit.bmHeight;
	_frameCountX = xFrameCount;
	_frameCountY = yFrameCount;
	_frameWidth = bit.bmWidth / xFrameCount;
	_frameHeight = bit.bmHeight / yFrameCount;
	_width = _originTexSizeX;
	_height = _originTexSizeY;

	// bitmap info
	_bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	_bitmapInfo.bmiHeader.biWidth = bit.bmWidth;
	_bitmapInfo.bmiHeader.biHeight = bit.bmHeight;
	_bitmapInfo.bmiHeader.biPlanes = 1;
	_bitmapInfo.bmiHeader.biBitCount = 32;
	_bitmapInfo.bmiHeader.biCompression = BI_RGB;
	_bitmapInfo.bmiHeader.biSizeImage = 0;
	_bitmapInfo.bmiHeader.biXPelsPerMeter = 0;
	_bitmapInfo.bmiHeader.biYPelsPerMeter = 0;
	_bitmapInfo.bmiHeader.biClrUsed = 0;
	_bitmapInfo.bmiHeader.biClrImportant = 0;

	int dwBmpSize = ((bit.bmWidth * _bitmapInfo.bmiHeader.biBitCount + 31) / 32) * 4 * bit.bmHeight;
	_rawData = new BYTE[dwBmpSize];

	GetDIBits(hdc, bitmap, 0, bit.bmHeight, _rawData, &_bitmapInfo, DIB_RGB_COLORS);


	// 3. ���� ����ũ ó��
	
	int width = _originTexSizeX;
	int height = _originTexSizeY;
	int rowSize = width * 4; // 32bit �� 4����Ʈ per �ȼ�
	
	// ����ũ ��Ʈ�� �ε� (ex: ��)

		for (int y = 0; y < height; ++y)
		{
			int invertedY = height - 1 - y; // ��Ʈ���� bottom-up ����
	
			for (int x = 0; x < width; ++x)
			{
				int index = invertedY * rowSize + x * 4;
	
				BYTE red = _rawData[index + 2];
				BYTE green = _rawData[index + 1];
				BYTE blue = _rawData[index + 0];
				//BYTE alpha = _rawData[index + 3]; // ������� �ʾƵ� ����
	
				if (RGB(red, green, blue) == RGB(255, 255, 255))
				{
					_rawData[index + 2] = 0;
					_rawData[index + 1] = 0;
					_rawData[index + 0] = 0;
				}
			}
		}

ReleaseDC(Game::getInstance().getHwnd(), hdc);
}

void Texture::render(HDC hdc, Vector pos, Vector src, Vector renderSize, bool applyCameraPos)
{
	// ������ǥ�� ī�޶� ��ǥ�� ��ȯ
	Vector screenPos = _centerAlign ? Vector(pos.x - renderSize.x * 0.5f, pos.y - renderSize.y * 0.5f) : pos;

		// ������ ó��(�� �̹��� ������ �������� ��ȯ�� ���)
		if (_transparent == -1) //  ������ �� ���� �� �� �̹��� �⺻ ����(Black)�� ������ �̹������� Ȯ��
		{
			// 2. ��ü �̹��� ���
			//�ȼ� ���۸� ��°�� HDC�� �� ���� �׷���(SetPixel���� ����
			StretchDIBits(hdc,
				(int32)screenPos.x,
				(int32)screenPos.y,
				renderSize.x,
				renderSize.y,
				0, 0, // DIB ���� �»�� X, Y ��ǥ
				_originTexSizeX, _originTexSizeY, // ù��° ��ĵ ����, ����� ��ĵ ���� ����
				_rawData,
				&_bitmapInfo,
				DIB_RGB_COLORS,
				SRCCOPY
			);
		}
		else // ���� ó��
		{
			// �ؽ�ó�� ��ü ũ�⸦ ���ϰ�, �ִϸ��̼� �Ǿ�� �ϴ� ������ �����⸦ �ϸ�, ������ Sprite ũ�⸦ ���Ҽ� �ִ�.
			::TransparentBlt(hdc,
					(int32)screenPos.x - (renderSize.x / 2),	// �ؽ�ó�� �߽���ǥ�� �׸������� size�� ���ݸ�ŭ ���ش�.
					(int32)screenPos.y - (renderSize.y / 2),
					renderSize.x,
					renderSize.y,						// �ؽ��İ� �׷������ϴ� ũ�� height	// 64
					_hdc,							// �ؽ�ó�� ����
					src.x,								// ���� �ؽ����� X						// 0~15���� �ε����� ���ư��鼭 �׷����Ѵ�.
					src.y,								// ���� �ؽ����� Y	
					renderSize.x,						// ���� �ؽ����� width					// 64
					renderSize.y,						// ���� �ؽ����� height					// 64
					_transparent);				// ������� �����ϰ� �׸���
		}
}




/*
// (����)����� �ش� �ȼ��� �����. // rawData ���� �����ؾ��Ѵ�.
//int randValue = rand() % 100;
//if (randValue < 2)
//{
//	// ���� ���� (���������� ����)
//	rawData[index + 0] = 0; // Blue
//	rawData[index + 1] = 0; // Green
//	rawData[index + 2] = 0; // Red
//	rawData[index + 3] = 255; // Alpha (������ ����)
//}

//SetPixel(hdc, static_cast<int>(pos.x) + x, static_cast<int>(pos.y) + y, RGB(red, green, blue));

*/
