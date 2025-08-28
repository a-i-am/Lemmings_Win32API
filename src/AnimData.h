#pragma once
#include "pch.h"

struct AnimData
{
    int32 startIndex;      // 프레임 시작 인덱스
    int32 totalCount;      // 프레임 수
    bool isFlipX;          // 좌우 반전 여부
    bool isLoop;           // 반복 여부
    bool isEnd;          // 현재 애니메이션 종료 여부
};