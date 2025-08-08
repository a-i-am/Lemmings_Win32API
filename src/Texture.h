#pragma once
#include "common_defs.h"
#include "TextureInfo.h"
class Texture
{
public:
	Texture();

	void load(string key, string texturePath, int32 transparent, int32 xFrameCount, int32 yFrameCount);
	void render(HDC hdc, Vector pos, Vector src, Vector rederSize, bool applyCameraPos = true);

	// TextureInfo getter �߰�
	TextureInfo* getInfo() const { return _info; }

public:
	// �⺻�� ��� ��ġ�� �������� �ؽ�ó �׸���
	bool _centerAlign = true;

private:
	TextureInfo* _info = nullptr; // �ٽ�: �̹��� ������ ���⼭ ����
	std::vector<BYTE> pixels;
};