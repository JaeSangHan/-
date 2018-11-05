#include "StdAfx.h"
#include "InputManager.h"


CInputManager::CInputManager(void)
{
	m_pCurInputHandler = NULL;
}


CInputManager::~CInputManager(void)
{
}

bool CInputManager::Initialize()
{
	memset( m_OldKeyState, 0, sizeof(m_OldKeyState) );
	memset( m_CurKeyState, 0, sizeof(m_CurKeyState) );
	memset( &m_MouseState, 0, sizeof(m_MouseState) );
	return true;
}

void CInputManager::Terminate()
{

}

void CInputManager::Keyboard()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	for (int nCnt = 0; nCnt < 256; nCnt++)
	{
		if (currentKeyStates[nCnt])
		{
			m_CurKeyState[nCnt] = SDL_TRUE;
		}
		else
		{
			m_CurKeyState[nCnt] = SDL_FALSE;
		}
	}
	m_pCurInputHandler->KeyboardHandler();

	memcpy(m_OldKeyState, m_CurKeyState, 256);
}

void CInputManager::Mouse()
{
	SDL_Event evnt;
	SDL_PollEvent(&evnt); //pollevent��� �칰�� evnt��� �絿�̸� ����

	//prv_BTN�� �����Ӹ��� ���� ��ư ���¸� �־��ش�.
	m_MouseState.prv_BTN[MOUSE_BUTTON::LEFT] = m_MouseState.BTN[MOUSE_BUTTON::LEFT];
	m_MouseState.prv_BTN[MOUSE_BUTTON::RIGHT] = m_MouseState.BTN[MOUSE_BUTTON::RIGHT];
	m_MouseState.prv_BTN[MOUSE_BUTTON::MIDDLE] = m_MouseState.BTN[MOUSE_BUTTON::MIDDLE];

	//�� �Ʒ��δ� LEFT, RIGHT, MIDDLE�� �����Ѵ�
	if (m_MouseState.prv_BTN[MOUSE_BUTTON::LEFT] != true)
	{
		if (evnt.type == SDL_MOUSEBUTTONDOWN && evnt.button.button == SDL_BUTTON_LEFT)
			m_MouseState.BTN[MOUSE_BUTTON::LEFT] = true;

		else 
			m_MouseState.BTN[MOUSE_BUTTON::LEFT] = false;
	}
	else
	{
		if (evnt.type == SDL_MOUSEBUTTONUP && evnt.button.button == SDL_BUTTON_LEFT)
			m_MouseState.BTN[MOUSE_BUTTON::LEFT] = false;

		else
			m_MouseState.BTN[MOUSE_BUTTON::LEFT] = true;
	}

	if (m_MouseState.prv_BTN[MOUSE_BUTTON::RIGHT] != true)
	{
		if (evnt.type == SDL_MOUSEBUTTONDOWN && evnt.button.button == SDL_BUTTON_RIGHT)
			m_MouseState.BTN[MOUSE_BUTTON::RIGHT] = true;

		else
			m_MouseState.BTN[MOUSE_BUTTON::RIGHT] = false;
	}
	else
	{
		if (evnt.type == SDL_MOUSEBUTTONUP && evnt.button.button == SDL_BUTTON_RIGHT)
			m_MouseState.BTN[MOUSE_BUTTON::RIGHT] = false;

		else
			m_MouseState.BTN[MOUSE_BUTTON::RIGHT] = true;
	}

	if (m_MouseState.prv_BTN[MOUSE_BUTTON::MIDDLE] != true)
	{
		if (evnt.type == SDL_MOUSEBUTTONDOWN && evnt.button.button == SDL_BUTTON_MIDDLE)
			m_MouseState.BTN[MOUSE_BUTTON::MIDDLE] = true;

		else
			m_MouseState.BTN[MOUSE_BUTTON::MIDDLE] = false;
	}
	else
	{
		if (evnt.type == SDL_MOUSEBUTTONUP && evnt.button.button == SDL_BUTTON_MIDDLE)
			m_MouseState.BTN[MOUSE_BUTTON::MIDDLE] = false;

		else
			m_MouseState.BTN[MOUSE_BUTTON::MIDDLE] = true;
	}

	//�� �Ʒ��δ� DOWN, UP, HOLD, UNHOLD�� �˻��Ѵ�
	if (!m_MouseState.prv_BTN[MOUSE_BUTTON::LEFT] && !m_MouseState.BTN[MOUSE_BUTTON::LEFT])
		m_PressState[MOUSE_BUTTON::LEFT] = MousePressState::Unhold;

	else if (m_MouseState.prv_BTN[MOUSE_BUTTON::LEFT] && m_MouseState.BTN[MOUSE_BUTTON::LEFT])
		m_PressState[MOUSE_BUTTON::LEFT] = MousePressState::Hold;

	else if (!m_MouseState.prv_BTN[MOUSE_BUTTON::LEFT] && m_MouseState.BTN[MOUSE_BUTTON::LEFT])
		m_PressState[MOUSE_BUTTON::LEFT] = MousePressState::Down;

	else if (m_MouseState.prv_BTN[MOUSE_BUTTON::LEFT] && !m_MouseState.BTN[MOUSE_BUTTON::LEFT])
		m_PressState[MOUSE_BUTTON::LEFT] = MousePressState::Up;

	//
	if (!m_MouseState.BTN[MOUSE_BUTTON::RIGHT] && !m_MouseState.prv_BTN[MOUSE_BUTTON::RIGHT])
		m_PressState[MOUSE_BUTTON::RIGHT] = MousePressState::Unhold;

	else if (m_MouseState.BTN[MOUSE_BUTTON::RIGHT] && m_MouseState.prv_BTN[MOUSE_BUTTON::RIGHT])
		m_PressState[MOUSE_BUTTON::RIGHT] = MousePressState::Hold;

	else if (m_MouseState.BTN[MOUSE_BUTTON::RIGHT] && !m_MouseState.prv_BTN[MOUSE_BUTTON::RIGHT])
		m_PressState[MOUSE_BUTTON::RIGHT] = MousePressState::Down;

	else if (!m_MouseState.BTN[MOUSE_BUTTON::RIGHT] && m_MouseState.prv_BTN[MOUSE_BUTTON::RIGHT])
		m_PressState[MOUSE_BUTTON::RIGHT] = MousePressState::Up;
	
	//
	if (!m_MouseState.BTN[MOUSE_BUTTON::MIDDLE] && !m_MouseState.prv_BTN[MOUSE_BUTTON::MIDDLE])
		m_PressState[MOUSE_BUTTON::MIDDLE] = MousePressState::Unhold;

	else if (m_MouseState.BTN[MOUSE_BUTTON::MIDDLE] && m_MouseState.prv_BTN[MOUSE_BUTTON::MIDDLE])
		m_PressState[MOUSE_BUTTON::MIDDLE] = MousePressState::Hold;

	else if (m_MouseState.BTN[MOUSE_BUTTON::MIDDLE] && !m_MouseState.prv_BTN[MOUSE_BUTTON::MIDDLE])
		m_PressState[MOUSE_BUTTON::MIDDLE] = MousePressState::Down;

	else if (!m_MouseState.BTN[MOUSE_BUTTON::MIDDLE] && m_MouseState.prv_BTN[MOUSE_BUTTON::MIDDLE])
		m_PressState[MOUSE_BUTTON::MIDDLE] = MousePressState::Up;

	int x, y;
	SDL_GetMouseState(&x, &y);
	m_MouseState.x = x;
	m_MouseState.y = y;
	
	m_pCurInputHandler->MouseHandler(m_MouseState); //�ý���.cpp�� �Լ� ����
}


void CInputManager::Pulse()
{
	if (m_pCurInputHandler)
	{
		Keyboard();
		Mouse();
	}
}
