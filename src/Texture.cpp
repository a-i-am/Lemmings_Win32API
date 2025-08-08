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


	// 3. 알파 마스크 처리
	
	int width = _originTexSizeX;
	int height = _originTexSizeY;
	int rowSize = width * 4; // 32bit → 4바이트 per 픽셀
	
	// 마스크 비트맵 로드 (ex: 맵)

		for (int y = 0; y < height; ++y)
		{
			int invertedY = height - 1 - y; // 비트맵은 bottom-up 저장
	
			for (int x = 0; x < width; ++x)
			{
				int index = invertedY * rowSize + x * 4;
	
				BYTE red = _rawData[index + 2];
				BYTE green = _rawData[index + 1];
				BYTE blue = _rawData[index + 0];
				//BYTE alpha = _rawData[index + 3]; // 사용하지 않아도 무방
	
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
	// 월드좌표를 카메라 좌표로 변환
	Vector screenPos = _centerAlign ? Vector(pos.x - renderSize.x * 0.5f, pos.y - renderSize.y * 0.5f) : pos;

		// 불투명 처리(맵 이미지 여백을 배경색으로 변환해 출력)
		if (_transparent == -1) //  렌더링 시 게임 씬 맵 이미지 기본 배경색(Black)과 통일할 이미지인지 확인
		{
			// 2. 전체 이미지 출력
			//픽셀 버퍼를 통째로 HDC에 한 번에 그려줌(SetPixel보다 빠름
			StretchDIBits(hdc,
				(int32)screenPos.x,
				(int32)screenPos.y,
				renderSize.x,
				renderSize.y,
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
					(int32)screenPos.x - (renderSize.x / 2),	// 텍스처를 중심좌표로 그리기위해 size의 절반만큼 빼준다.
					(int32)screenPos.y - (renderSize.y / 2),
					renderSize.x,
					renderSize.y,						// 텍스쳐가 그려져야하는 크기 height	// 64
					_hdc,							// 텍스처의 정보
					src.x,								// 원본 텍스쳐의 X						// 0~15번의 인덱스로 돌아가면서 그려야한다.
					src.y,								// 원본 텍스쳐의 Y	
					renderSize.x,						// 원본 텍스쳐의 width					// 64
					renderSize.y,						// 원본 텍스쳐의 height					// 64
					_transparent);				// 어떤색상을 투명하게 그릴까
		}
}




/*
// (예시)레밍즈가 해당 픽셀을 지운다. // rawData 값을 변경해야한다.
//int randValue = rand() % 100;
//if (randValue < 2)
//{
//	// 랜덤 삭제 (검은색으로 변경)
//	rawData[index + 0] = 0; // Blue
//	rawData[index + 1] = 0; // Green
//	rawData[index + 2] = 0; // Red
//	rawData[index + 3] = 255; // Alpha (불투명 유지)
//}

//SetPixel(hdc, static_cast<int>(pos.x) + x, static_cast<int>(pos.y) + y, RGB(red, green, blue));

*/
