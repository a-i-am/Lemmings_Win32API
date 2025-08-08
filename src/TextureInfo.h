#pragma once
class TextureInfo
{
public:

    // 텍스처를 그리기 위한 변수
    HBITMAP hBitmap = nullptr;
    HDC	    hdc = 0;

    int32   transparent = -1;	    // 투명하게 보여야하는 색상
    
    int32   originTexSizeX = 0;	// 원본 텍스처 크기
    int32   originTexSizeY = 0;

    int32	frameCountX = 0;	// X축으로 몇개의 프레임이 있는지
    int32	frameCountY = 0;	// Y축으로 몇개의 프레임이 있는지

    int32	frameWidth = 0;	// Sprite 처럼 한장의 이미지에 합쳐있다면, 한칸의 프레임 사이즈
    int32	frameHeight = 0;

    BYTE* rawData = nullptr;
    BITMAPINFO bitmapInfo = {};

};
