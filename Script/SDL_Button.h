#pragma once
#include "stdafx.h"

typedef struct S_BUTTON
{
	enum eButtonState { BUTTONDOWN, BUTTONUP };

	SDL_Texture* imgUp;
	SDL_Texture* imgDown;
	SDL_Texture* imgHold;
	SDL_Texture* imgCurrent;

	SDL_Rect rtClip;

	int nX, nY;
	bool bIsVisible = true;
	bool isPlayingSong = false;
	std::function<void()> m_Func;

}BUTTON;

BUTTON* InitButton(SDL_Renderer* screen, const char* szUp, const char* szDown, const char* szHold, int x, int y, std::function<void()> func);
void Release(BUTTON* pBtn); //�޸� ����
void Draw(SDL_Renderer* drawSurface, BUTTON* pBtn); //��ο�
//������� ���� �⺻���� ��Ʈ

BUTTON::eButtonState GetState(BUTTON* pBtn); //��ư�� ���¸� �˾ƿ���. //::�� ������ ����. ��ư ����ü ���� e��ư������Ʈ�� ã�ƿͶ� ��� ��
void ClickDown(BUTTON* pBtn);
void ClickUp(BUTTON* pBtn);

bool IsOver(BUTTON* pBtn, int px, int py); //���� �ֳ�?
void Toggle(BUTTON* pBtn); //����
void ResetOnUp(BUTTON* pBtn); //������ �����·� �ٲ��
void SetCoord(BUTTON* btn, int x, int y); //���ο� ��ǥ�� �ٲ��ֱ�
void SetVisible(BUTTON* btn, bool visible); //���̴��� �ƴ��� ����
bool IsVisible(BUTTON* btn); //���̳�?

void MouseDown(BUTTON* pBtn, int px, int py); 
void MouseUp(BUTTON* pBtn, int px, int py);
void MouseHold(BUTTON* pBtn, int px, int py);