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
	
	// getter/setter Texture Info
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


	int rowStride = ((bit.bmWidth * _bitmapInfo.bmiHeader.biBitCount + 31) / 32) * 4;
	int dwBmpSize = rowStride * bit.bmHeight;


	_rawData = new BYTE[dwBmpSize];
	

	int ret = GetDIBits(hdc, bitmap, 0, bit.bmHeight, _rawData, &_bitmapInfo, DIB_RGB_COLORS);

	float scaleX = (float)bit.bmWidth / GWinSizeX;
	float scaleY = (float)bit.bmHeight / GWinSizeY;
	
	// BGR(A) �� COLORREF ��ȯ (�ȼ� �浹)
	for (int y = 0; y < GWinSizeY; ++y)
	{
		int srcY = (int)(y * scaleY);
		for (int x = 0; x < GWinSizeX; ++x) 
		{
			int srcX = (int)(x * scaleX);
			int rawDataIndex = (bit.bmHeight - 1 - srcY) * rowStride + srcX * 4;

			BYTE blue = _rawData[rawDataIndex + 0];
			BYTE green = _rawData[rawDataIndex + 1];
			BYTE red = _rawData[rawDataIndex + 2];

			// ��� -> ������ ���� ����
			if (RGB(red, green, blue) == RGB(255, 255, 255))
			{
				_rawData[rawDataIndex + 2] = 0;
				_rawData[rawDataIndex + 1] = 0;
				_rawData[rawDataIndex + 0] = 0;
			}
		}
	}

	ReleaseDC(Game::getInstance().getHwnd(), hdc);
}

void Texture::render(HDC hdc, Vector pos, Vector srcPos, Vector frameSize, Vector ratio)
{
	// ������ǥ�� ī�޶� ��ǥ�� ��ȯ
	Vector screenPos = _centerAlign ? Vector(pos.x - frameSize.x * 0.5f, pos.y - frameSize.y * 0.5f) : pos;

		// ������ ó��(�� �̹��� ������ �������� ��ȯ�� ���)
		if (_transparent == -1) //  ������ �� ���� �� �� �̹��� �⺻ ����(Black)�� ������ �̹������� Ȯ��
		{
			// 2. ��ü �̹��� ���
			//�ȼ� ���۸� ��°�� HDC�� �� ���� �׷���(SetPixel���� ����
			StretchDIBits(hdc,
				(int32)screenPos.x,
				(int32)screenPos.y,
				frameSize.x,
				frameSize.y,
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
					(int32)screenPos.x,	// �ؽ�ó�� �߽���ǥ�� �׸������� size�� ���ݸ�ŭ ���ش�.
					(int32)screenPos.y,
					
					// �ؽ��İ� ȭ�鿡 ������ ũ��
					frameSize.x * ratio.x,
					frameSize.y * ratio.y,
					_hdc,										// �ؽ�ó�� ����
					(int32)srcPos.x,								// ���� �ؽ����� X						// 0~15���� �ε����� ���ư��鼭 �׷����Ѵ�.
					(int32)srcPos.y,								// ���� �ؽ����� Y	
					// �߶�� ���� ũ��
					_frameWidth,
					_frameHeight,
					_transparent);								// ������� �����ϰ� �׸���
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
