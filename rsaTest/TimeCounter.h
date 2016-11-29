#pragma once

#include <windows.h>
#include <mmsystem.h>
#pragma comment( lib, "winmm.lib" )

class CTimeCounter
{
public:
	CTimeCounter(void)
	{
		Reset();
	}

	~CTimeCounter(void)
	{
	
	}

protected:
	DWORD	m_dwStart;

public:
	void	Reset()
	{
		m_dwStart = ::timeGetTime();
	}

	DWORD	GetTime()
	{
		DWORD	dwEnd = ::timeGetTime();
		return dwEnd - m_dwStart;
	}

	void	ShowTime()
	{
		printf( "%dms\n", GetTime() );
		Reset();
	}
};
