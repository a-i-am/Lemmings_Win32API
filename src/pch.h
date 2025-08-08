#pragma once

#define NOMINMAX
#include <iostream>

#include <windows.h>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <functional>
#include <algorithm>


// C++ 20
#include <format>		// std::format("x:{0}, y:{1}"
#include <numbers>  
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

using int8 = char;
using int16 = short;
using int32 = int;
using int64 = long long;
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

// transparent Blt
#pragma comment(lib, "msimg32.lib")

// GDI+
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

// 사운드
#include <MMSystem.h>
#include <dsound.h>
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dsound.lib")

using namespace std;

#define SAFE_DELETE(ptr)		\
	if (ptr)					\
	{							\
		delete ptr;				\
		ptr = nullptr;			\
	}

// 메모리 릭. json 라이브러리 뒤쪽에서 해야지 new 키워드랑 충돌하지 않는다.
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>

// 공용 선언들 
#include "Defines.h"
