#pragma once
#include "common_defs.h"
class Texture
{
public:
	Texture();

	void Load(string key, string texturePath, int32 transparent, int32 xFrameCount, int32 yFrameCount);
	void Render(HDC hdc, Vector pos, Vector srcPos, Vector frameSize, bool isFlipX);

	void SetTextureWidth(int32 width) { _width = width; }
	void SetTextureHeight(int32 height) { _height = height; }
	int32 GetTextureWidth() const  { return _width;  }
	int32 GetTextureHeight() const { return _height; }

	int32 GetOriginTextureWidth() const { return _originTexSizeX; }
	int32 GetOriginTextureHeight() const { return _originTexSizeY; }

	int32 GetFrameCountX() const { return _frameCountX; }
	int32 GetFrameCountY() const { return _frameCountY; }

	int32 GetFrameWidth() const { return _frameWidth; }
	int32 GetFrameHeight() const { return _frameHeight; }

	HDC GetHDC() const { return _hdc; }
	HBITMAP GetBitmap() const { return _hBitmap; }
	const vector<COLORREF>& GetPixelData() const { return _pixelData; }

	bool IsCenterAligned() const { return _centerAlign; }
	void SetCenterAlign(bool center) { _centerAlign = center; }

	void GenerateCollisionData(int32 targetWidth, int32 targetHeight);
private:
	// GDI ����
	HBITMAP		_hBitmap = nullptr;
	HDC			_hdc = nullptr;
	BITMAPINFO	_bitmapInfo = {};
	BYTE* _rawData = nullptr;
	vector<COLORREF> _pixelData;
	
	// �ؽ�ó ���� ����
	int32 _width;
	int32 _height;
	int32		_transparent = -1;

	int32		_originTexSizeX = 0;
	int32		_originTexSizeY = 0;
	


	// ���� �ؽ�ó : frameCount�� 2 �̻�
	// �񿬼� �ؽ�ó : frameCount�� 1
	int32		_frameCountX = 1;
	int32		_frameCountY = 1;

	int32		_frameWidth = 0;
	int32		_frameHeight = 0;

	bool		_centerAlign = true; // �⺻�� ��� ��ġ�� �������� �ؽ�ó �׸���
	bool		_isCollisionGenerated = false; // collision ���� ����

	   // flip ĳ��
	HDC     _flipHDC = nullptr;
	HBITMAP _flipBitmap = nullptr;
	bool    _flipCached = false;

	
};