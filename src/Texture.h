#pragma once
#include "common_defs.h"
class Texture
{
public:
	Texture();

	void load(string key, string texturePath, int32 transparent, int32 xFrameCount, int32 yFrameCount);
	void render(HDC hdc, Vector pos, Vector src, Vector rederSize, bool applyCameraPos = true);

	int32 getTextureWidth() const  { return _width;  }
	int32 getTextureHeight() const { return _height; }

	void setTextureWidth(int32 width) { _width = width; }
	void setTextureHeight(int32 height) { _height = height; }

	int32 getFrameCountX() const { return _frameCountX; }
	int32 getFrameCountY() const { return _frameCountY; }

	int32 getFrameWidth() const { return _frameWidth; }
	int32 getFrameHeight() const { return _frameHeight; }

	HDC getHDC() const { return _hdc; }
	HBITMAP getBitmap() const { return _hBitmap; }

	bool isCenterAligned() const { return _centerAlign; }
	void setCenterAlign(bool center) { _centerAlign = center; }

private:
	// GDI ����
	HBITMAP		_hBitmap = nullptr;
	HDC			_hdc = nullptr;
	BITMAPINFO	_bitmapInfo = {};
	BYTE* _rawData = nullptr;

	// �ؽ�ó ���� ����
	int32		_transparent = -1;

	int32		_originTexSizeX = 0;
	int32		_originTexSizeY = 0;
	
	int32 _width;
	int32 _height;


	// ���� �ؽ�ó : frameCount�� 2 �̻�
	// �񿬼� �ؽ�ó : frameCount�� 1
	int32		_frameCountX = 1;
	int32		_frameCountY = 1;

	int32		_frameWidth = 0;
	int32		_frameHeight = 0;

	bool		_centerAlign = true; // �⺻�� ��� ��ġ�� �������� �ؽ�ó �׸���

	std::vector<BYTE> _pixels; // �ȼ� ������ ������
};