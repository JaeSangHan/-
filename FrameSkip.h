#pragma once

class CFrameSkip
{
private:
	float	m_fTimer;
	float	m_fSecPerFrame;
	float	m_fLimitFPS;

	float	m_fFPS;
	float	m_fAcculTime;
	float   m_fSongAcculTime;
	int		m_nFrameCount;

public:
	void SetFramePerSec(float fps);
	bool Update(float dt);
	bool IsFrameSkip();

	CFrameSkip();
	virtual ~CFrameSkip();

	__inline float GetFPS() const { return m_fFPS;  }
	__inline float GetLimitFPS() const { return m_fLimitFPS; }
};

