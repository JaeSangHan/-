#pragma once
class IInputHandler; //중요한 부분인듯

class CInputManager
{
public:
	IInputHandler* m_pCurInputHandler; 
	SDL_bool m_OldKeyState[256];
	SDL_bool m_CurKeyState[256];
	MOUSESTATE m_MouseState; 
	MousePressState m_PressState[4];

public:
	CInputManager(void);
	~CInputManager(void);

private:
	void Keyboard(); //키보드 입력에 관한 함수
	void Mouse(); //마우스 입력에 관한 함수
public:
	bool Initialize();
	void Terminate();
	void Pulse();

public:
	inline void SetInputHandler(IInputHandler* pInputHandler);
	inline IInputHandler* GetInputHandler() const;
	inline SDL_bool GetOldKeyState(int nKey);
	inline SDL_bool GetCurKeyState(int nKey);
	inline MousePressState GetPressState(int state);
};


inline void CInputManager::SetInputHandler(IInputHandler* pInputHandler)
{
	m_pCurInputHandler = pInputHandler;
}

inline IInputHandler* CInputManager::GetInputHandler() const
{
	return m_pCurInputHandler;
}

inline SDL_bool CInputManager::GetOldKeyState(int nKey)
{
	return m_OldKeyState[nKey];
}

inline SDL_bool CInputManager::GetCurKeyState(int nKey)
{
	return m_CurKeyState[nKey];
}

inline MousePressState CInputManager::GetPressState(int state)
{
	return m_PressState[state];
}
