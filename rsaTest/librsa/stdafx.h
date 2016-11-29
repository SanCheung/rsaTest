// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <math.h>
#include <time.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

typedef		unsigned char		u8;
typedef		unsigned long		u32;
typedef		unsigned __int64	u64;

typedef		__int64				int64;

#define		MAX( a, b )			( a>=b?a:b )