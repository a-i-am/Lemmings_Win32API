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
	
	// 1. WinAPI 텍스처 로딩
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

	// 2. TextureInfo 생성

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
	if (_isCollisionGenerated) return;  // 이미 생성했으면 바로 return

	_pixelData.resize(targetWidth * targetHeight);

	float scaleX = (float)_originTexSizeX / targetWidth;
	float scaleY = (float)_originTexSizeY / targetHeight;

	int32 rowStride = ((_originTexSizeX * _bitmapInfo.bmiHeader.biBitCount + 31) / 32) * 4;

	int32 dwBmpSize = rowStride * _originTexSizeY;
	_rawData = new BYTE[dwBmpSize];

	GetDIBits(_hdc, _hBitmap, 0, _bitmapInfo.bmiHeader.biHeight, _rawData, &_bitmapInfo, DIB_RGB_COLORS);

	// BGR(A) → COLORREF 변환 (픽셀 충돌)
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
	// 월드좌표를 카메라 좌표로 변환
	Vector screenPos = _centerAlign ? Vector(pos.x - frameSize.x * 0.5f, pos.y - frameSize.y * 0.5f) : pos;

	int32 destX = screenPos.x;
	int32 destY = screenPos.y;
	int32 destW = frameSize.x;
	int32 destH = frameSize.y;

	// flipX 처리: StretchBlt/TransparentBlt에서 width 음수로 좌우 반전
	if (isFlipX)
	{
		destX += destW;   // 오른쪽부터 시작
		destW = -destW;   // width 음수로 좌우 반전
	}

		// 불투명 처리(맵 이미지 여백을 배경색으로 변환해 출력)
		if (_transparent == -1) //  렌더링 시 게임 씬 맵 이미지 기본 배경색(Black)과 통일할 이미지인지 확인
		{
			// 2. 전체 이미지 출력
			//픽셀 버퍼를 통째로 HDC에 한 번에 그려줌(SetPixel보다 빠름
			StretchDIBits(hdc,
				destX,
				destY,
				destW,
				destH,
				0, 0, // DIB 원본 좌상귀 X, Y 좌표
				_originTexSizeX, _originTexSizeY, // 첫번째 스캔 라인, 출력할 스캔 라인 개수
				_rawData,
				&_bitmapInfo,
				DIB_RGB_COLORS,
				SRCCOPY
			);
		}
		else // 투명 처리
		{
			// 텍스처의 전체 크기를 구하고, 애니메이션 되어야 하는 개수로 나누기를 하면, 한장의 Sprite 크기를 구할수 있다.
			::TransparentBlt(hdc,
				destX,
				destY,
				destW,
				destH,
				_hdc,										// 텍스처의 정보
				(int32)srcPos.x,								// 원본 텍스쳐의 X						// 0~15번의 인덱스로 돌아가면서 그려야한다.
				(int32)srcPos.y,								// 원본 텍스쳐의 Y	
				// 잘라올 원본 크기
				_frameWidth,
				_frameHeight,
				_transparent);								// 어떤색상을 투명하게 그릴까
		}
}


/*
// (예시)레밍즈가 해당 픽셀을 지운다. // rawData 값을 변경해야한다.
//int32 randValue = rand() % 100;
//if (randValue < 2)
//{
//	// 랜덤 삭제 (검은색으로 변경)
//	rawData[index + 0] = 0; // Blue
//	rawData[index + 1] = 0; // Green
//	rawData[index + 2] = 0; // Red
//	rawData[index + 3] = 255; // Alpha (불투명 유지)
//}

//SetPixel(hdc, static_cast<int32>(pos.x) + x, static_cast<int32>(pos.y) + y, RGB(red, green, blue));

*/
