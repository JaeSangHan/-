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
void Release(BUTTON* pBtn); //메모리 해제
void Draw(SDL_Renderer* drawSurface, BUTTON* pBtn); //드로우
//여기까지 가장 기본적인 세트

BUTTON::eButtonState GetState(BUTTON* pBtn); //버튼의 상태를 알아오기. //::은 스코프 연산. 버튼 구조체 안의 e버튼스테이트를 찾아와라 라는 뜻
void ClickDown(BUTTON* pBtn);
void ClickUp(BUTTON* pBtn);

bool IsOver(BUTTON* pBtn, int px, int py); //위에 있냐?
void Toggle(BUTTON* pBtn); //반전
void ResetOnUp(BUTTON* pBtn); //무조건 업상태로 바꿔라
void SetCoord(BUTTON* btn, int x, int y); //새로운 좌표로 바꿔주기
void SetVisible(BUTTON* btn, bool visible); //보이는지 아닌지 설정
bool IsVisible(BUTTON* btn); //보이냐?

void MouseDown(BUTTON* pBtn, int px, int py); 
void MouseUp(BUTTON* pBtn, int px, int py);
void MouseHold(BUTTON* pBtn, int px, int py);