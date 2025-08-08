#pragma once
class TextureInfo
{
public:

    // �ؽ�ó�� �׸��� ���� ����
    HBITMAP hBitmap = nullptr;
    HDC	    hdc = 0;

    int32   transparent = -1;	    // �����ϰ� �������ϴ� ����
    
    int32   originTexSizeX = 0;	// ���� �ؽ�ó ũ��
    int32   originTexSizeY = 0;

    int32	frameCountX = 0;	// X������ ��� �������� �ִ���
    int32	frameCountY = 0;	// Y������ ��� �������� �ִ���

    int32	frameWidth = 0;	// Sprite ó�� ������ �̹����� �����ִٸ�, ��ĭ�� ������ ������
    int32	frameHeight = 0;

    BYTE* rawData = nullptr;
    BITMAPINFO bitmapInfo = {};

};
