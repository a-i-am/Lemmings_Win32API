#pragma once
#include "pch.h"

struct AnimData
{
    int32 startIndex;      // ������ ���� �ε���
    int32 totalCount;      // ������ ��
    bool isFlipX;          // �¿� ���� ����
    bool isLoop;           // �ݺ� ����
    bool isEnd;          // ���� �ִϸ��̼� ���� ����
};