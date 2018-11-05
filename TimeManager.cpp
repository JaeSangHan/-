#include "stdafx.h"
#include "TimeManager.h"


CTimeManager::CTimeManager(void)
{
	m_fAcculTime = 0.0f;	// 누적시간
	m_fSongAcculTime = 0.0f;	// 델타타임

	m_fFPS = 0.0f;			// FPS
	m_fTimeStep = 0.0f;		// 현재시간.
	m_fFPSTime = 0.0f;

	m_nFrameCount = 0;
	m_dwBeforeTime = 0;
}

CTimeManager::~CTimeManager(void)
{
}

bool CTimeManager::Initialize()
{
	srand((unsigned)time(NULL));
	m_dwBeforeTime = timeGetTime();
	//	m_dwBeforeTime = GetTickCount();

	return true;
}

void CTimeManager::Terminate()
{
}

void CTimeManager::Pulse (bool isMusicPlay)
{
	DWORD dwTime = timeGetTime();

	DWORD dwTick = dwTime - m_dwBeforeTime;
	m_fTimeStep = (float)dwTick * 0.001f;
	m_fAcculTime += m_fTimeStep;
	if (isMusicPlay) m_fSongAcculTime += m_fTimeStep; //음악 실행중일때만 더하기

	m_fFPSTime += m_fTimeStep;
	if (m_fFPSTime > 1.0f)
	{
		m_fFPS = (float)m_nFrameCount / m_fFPSTime;
		m_fFPSTime = 0.0f;
		m_nFrameCount = 0;
	}
	else
	{
		m_nFrameCount++;
	}
	m_dwBeforeTime = dwTime;
}
