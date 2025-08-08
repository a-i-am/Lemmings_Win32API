#include "pch.h"
#include "Texture.h"
#include "TextureInfo.h"
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

	_info = new TextureInfo();
	_info->hBitmap = bitmap;
	_info->hdc = textureHdc;
	_info->transparent = transparent;
	_info->originTexSizeX = bit.bmWidth;
	_info->originTexSizeY = bit.bmHeight;
	_info->frameCountX = xFrameCount;
	_info->frameCountY = yFrameCount;
	_info->frameWidth = bit.bmWidth / xFrameCount;
	_info->frameHeight = bit.bmHeight / yFrameCount;


	// bitmap info
	_info->bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	_info->bitmapInfo.bmiHeader.biWidth = bit.bmWidth;
	_info->bitmapInfo.bmiHeader.biHeight = bit.bmHeight;
	_info->bitmapInfo.bmiHeader.biPlanes = 1;
	_info->bitmapInfo.bmiHeader.biBitCount = 32;
	_info->bitmapInfo.bmiHeader.biCompression = BI_RGB;
	_info->bitmapInfo.bmiHeader.biSizeImage = 0;
	_info->bitmapInfo.bmiHeader.biXPelsPerMeter = 0;
	_info->bitmapInfo.bmiHeader.biYPelsPerMeter = 0;
	_info->bitmapInfo.bmiHeader.biClrUsed = 0;
	_info->bitmapInfo.bmiHeader.biClrImportant = 0;

	int dwBmpSize = ((bit.bmWidth * _info->bitmapInfo.bmiHeader.biBitCount + 31) / 32) * 4 * bit.bmHeight;
	_info->rawData = new BYTE[dwBmpSize];

	GetDIBits(hdc, bitmap, 0, bit.bmHeight, _info->rawData, &_info->bitmapInfo, DIB_RGB_COLORS);


	// 3. ���� ����ũ ó��
	
	int width = _info->originTexSizeX;
	int height = _info->originTexSizeY;
	int rowSize = width * 4; // 32bit �� 4����Ʈ per �ȼ�
	
	// ����ũ ��Ʈ�� �ε� (ex: ��)

		for (int y = 0; y < height; ++y)
		{
			int invertedY = height - 1 - y; // ��Ʈ���� bottom-up ����
	
			for (int x = 0; x < width; ++x)
			{
				int index = invertedY * rowSize + x * 4;
	
				BYTE red = _info->rawData[index + 2];
				BYTE green = _info->rawData[index + 1];
				BYTE blue = _info->rawData[index + 0];
				//BYTE alpha = _info->rawData[index + 3]; // ������� �ʾƵ� ����
	
				if (RGB(red, green, blue) == RGB(255, 255, 255))
				{
					_info->rawData[index + 2] = 0;
					_info->rawData[index + 1] = 0;
					_info->rawData[index + 0] = 0;
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
		if (_info->transparent == -1) //  ������ �� ���� �� �� �̹��� �⺻ ����(Black)�� ������ �̹������� Ȯ��
		{
			// 2. ��ü �̹��� ���
			//�ȼ� ���۸� ��°�� HDC�� �� ���� �׷���(SetPixel���� ����
			StretchDIBits(hdc,
				(int32)screenPos.x,
				(int32)screenPos.y,
				renderSize.x,
				renderSize.y,
				0, 0, // DIB ���� �»�� X, Y ��ǥ
				_info->originTexSizeX, _info->originTexSizeY, // ù��° ��ĵ ����, ����� ��ĵ ���� ����
				_info->rawData,
				&_info->bitmapInfo,
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
					_info->hdc,							// �ؽ�ó�� ����
					src.x,								// ���� �ؽ����� X						// 0~15���� �ε����� ���ư��鼭 �׷����Ѵ�.
					src.y,								// ���� �ؽ����� Y	
					renderSize.x,						// ���� �ؽ����� width					// 64
					renderSize.y,						// ���� �ؽ����� height					// 64
					_info->transparent);				// ������� �����ϰ� �׸���
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
