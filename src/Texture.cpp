#include "pch.h"
#include "Texture.h"
#include "Game.h"
#include "ResourceManager.h"

Texture::Texture()
{

}

void Texture::Load(string key, string texturePath, int32 transparent, int32 xFrameCount, int32 yFrameCount)
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


	ReleaseDC(Game::getInstance().getHwnd(), hdc);
}

void Texture::GenerateCollisionData(int32 targetWidth, int32 targetHeight)
{
	if (_isCollisionGenerated) return;  // �̹� ���������� �ٷ� return

	_pixelData.resize(targetWidth * targetHeight);

	float scaleX = (float)_originTexSizeX / targetWidth;
	float scaleY = (float)_originTexSizeY / targetHeight;

	int32 rowStride = ((_originTexSizeX * _bitmapInfo.bmiHeader.biBitCount + 31) / 32) * 4;

	int32 dwBmpSize = rowStride * _originTexSizeY;
	_rawData = new BYTE[dwBmpSize];

	GetDIBits(_hdc, _hBitmap, 0, _bitmapInfo.bmiHeader.biHeight, _rawData, &_bitmapInfo, DIB_RGB_COLORS);

	// BGR(A) �� COLORREF ��ȯ (�ȼ� �浹)
	for (int32 y = 0; y < targetHeight; ++y)
	{
		int32 srcY = (int32)(y * scaleY);
		for (int32 x = 0; x < targetWidth; ++x)
		{
			int32 srcX = (int32)(x * scaleX);
			int32 rawDataIndex = (_originTexSizeY - 1 - srcY) * rowStride + srcX * 4;

			BYTE blue = _rawData[rawDataIndex + 0];
			BYTE green = _rawData[rawDataIndex + 1];
			BYTE red = _rawData[rawDataIndex + 2];

			COLORREF color = RGB(red, green, blue);

			if (color == RGB(255, 255, 255))
			{
				color = RGB(0, 0, 0);
				_rawData[rawDataIndex + 0] = 0;
				_rawData[rawDataIndex + 1] = 0;
				_rawData[rawDataIndex + 2] = 0;
			}

			_pixelData[y * targetWidth + x] = color;
		}
	}

	_isCollisionGenerated = true;
}


void Texture::Render(HDC hdc, Vector pos, Vector srcPos, Vector frameSize, bool isFlipX)
{
	// ������ǥ�� ī�޶� ��ǥ�� ��ȯ
	Vector screenPos = _centerAlign ? Vector(pos.x - frameSize.x * 0.5f, pos.y - frameSize.y * 0.5f) : pos;

	int32 destX = screenPos.x;
	int32 destY = screenPos.y;
	int32 destW = frameSize.x;
	int32 destH = frameSize.y;

	// flipX ó��: StretchBlt/TransparentBlt���� width ������ �¿� ����
	if (isFlipX)
	{
		destX += destW;   // �����ʺ��� ����
		destW = -destW;   // width ������ �¿� ����
	}

		// ������ ó��(�� �̹��� ������ �������� ��ȯ�� ���)
		if (_transparent == -1) //  ������ �� ���� �� �� �̹��� �⺻ ����(Black)�� ������ �̹������� Ȯ��
		{
			// 2. ��ü �̹��� ���
			//�ȼ� ���۸� ��°�� HDC�� �� ���� �׷���(SetPixel���� ����
			StretchDIBits(hdc,
				destX,
				destY,
				destW,
				destH,
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
				destX,
				destY,
				destW,
				destH,
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
//int32 randValue = rand() % 100;
//if (randValue < 2)
//{
//	// ���� ���� (���������� ����)
//	rawData[index + 0] = 0; // Blue
//	rawData[index + 1] = 0; // Green
//	rawData[index + 2] = 0; // Red
//	rawData[index + 3] = 255; // Alpha (������ ����)
//}

//SetPixel(hdc, static_cast<int32>(pos.x) + x, static_cast<int32>(pos.y) + y, RGB(red, green, blue));

*/
