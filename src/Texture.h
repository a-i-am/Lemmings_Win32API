#pragma once
#include "common_defs.h"
#include "TextureInfo.h"
class Texture
{
public:
	Texture();

	void load(string key, string texturePath, int32 transparent, int32 xFrameCount, int32 yFrameCount);
	void render(HDC hdc, Vector pos, Vector src, Vector rederSize, bool applyCameraPos = true);

	// TextureInfo getter 추가
	TextureInfo* getInfo() const { return _info; }

public:
	// 기본은 가운데 위치를 기준으로 텍스처 그리기
	bool _centerAlign = true;

private:
	TextureInfo* _info = nullptr; // 핵심: 이미지 정보를 여기서 저장
	std::vector<BYTE> pixels;
};