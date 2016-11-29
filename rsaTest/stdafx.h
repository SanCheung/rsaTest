// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif	

#define		_CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <tchar.h>

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



// TODO: reference additional headers your program requires here
