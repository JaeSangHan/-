#include "stdafx.h"
#include "FrameSkip.h"


CFrameSkip::CFrameSkip()
{
	SetFramePerSec(60.0f);
}


CFrameSkip::~CFrameSkip()
{

}

void CFrameSkip::SetFramePerSec(float fps)
{
	m_fTimer = 0.0f;
	m_fFPS = 0.0f;
	m_fAcculTime = 0.0f;

	m_fSongAcculTime = 0.0f;

	m_nFrameCount = 0;
	m_fLimitFPS = fps;
	m_fSecPerFrame = 1.0f / fps;
}

// 원하는 프레임보다 너무 빠르면, 
// false를 반환해서 코드를 동작시키지 않도록 한다. 
// dt는 '초'단위 (밀리초 아님!!!) 
bool CFrameSkip::Update(float dt)
{
	m_fTimer += dt;
	m_fAcculTime += dt;
	m_fSongAcculTime += dt;

	if (m_fTimer < 0)
	{
		if ((float)m_nFrameCount / m_fAcculTime != 0.0f)
		{
			m_fFPS = (float)m_nFrameCount / m_fAcculTime;
			m_fAcculTime = 0;
			m_fSongAcculTime = 0;


			m_nFrameCount = 0;
		}
		return false;
	}

	// 한프레임에 해당하는 시간을 뺀다. 
	m_fTimer -= m_fSecPerFrame;
	m_nFrameCount += 1;

	return true;
}

// Update후에 호출해서 frame skip을 수행해야 하는지 검사한다. 
// frame skip이 일어나야 한다면 true를 반환한다. 
bool CFrameSkip::IsFrameSkip()
{
	return (m_fTimer >= 0);
}
