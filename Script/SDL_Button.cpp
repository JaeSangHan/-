#include "SDL_Button.h"
#include "stdafx.h"

BUTTON* InitButton(SDL_Renderer* screen, const char* szUp, const char* szDown, const char* szHold,
	int x, int y, std::function<void()> func)
{
	BUTTON* Temp;

	Temp = new BUTTON; //동적할당. 멀록은 메모리 만들어주는 기능
	SDL_Surface* imgTemp;

	imgTemp = SDL_LoadBMP(szUp);
	Uint32 colorkey = SDL_MapRGB(imgTemp->format, 255, 0, 255);
	SDL_SetColorKey(imgTemp, SDL_TRUE, colorkey);
	Temp->imgUp = SDL_CreateTextureFromSurface(screen, imgTemp); //서페이스를 텍스쳐로

	imgTemp = SDL_LoadBMP(szDown);
	colorkey = SDL_MapRGB(imgTemp->format, 255, 0, 255); //색깔 키 값 
	SDL_SetColorKey(imgTemp, SDL_TRUE, colorkey); //색깔 키 값 설정
	Temp->imgDown = SDL_CreateTextureFromSurface(screen, imgTemp);

	imgTemp = SDL_LoadBMP(szHold);
	colorkey = SDL_MapRGB(imgTemp->format, 255, 0, 255); //색깔 키 값 
	SDL_SetColorKey(imgTemp, SDL_TRUE, colorkey); //색깔 키 값 설정
	Temp->imgHold = SDL_CreateTextureFromSurface(screen, imgTemp);

	Temp->imgCurrent = Temp->imgUp;
	Temp->rtClip.x = x;
	Temp->rtClip.y = y;
	Temp->rtClip.w = imgTemp->w;
	Temp->rtClip.h = imgTemp->h;

	SetCoord(Temp, x, y); //버튼 포지션 설정
	SetVisible(Temp, true); //true형으로 변환

	/*CSystem system;
	(system.*f)();*/
	Temp->m_Func = func; //함수 넣기
	SDL_FreeSurface(imgTemp);

	return Temp;
}

void Release(BUTTON* pBtn)
{
	if (!pBtn) return;
	if (pBtn->imgUp != 0)	SDL_DestroyTexture(pBtn->imgUp);
	if (pBtn->imgDown != 0)	SDL_DestroyTexture(pBtn->imgDown);

	delete pBtn;
}

void Draw(SDL_Renderer* screen, BUTTON* pBtn)
{
	if (!pBtn->bIsVisible) return;
	SDL_RenderCopy(screen, pBtn->imgCurrent, NULL, &pBtn->rtClip);
}

BUTTON::eButtonState GetState(BUTTON* pBtn)
{
	if (pBtn->imgCurrent == pBtn->imgDown)
		return BUTTON::eButtonState::BUTTONDOWN;
	else 
		return BUTTON::eButtonState::BUTTONUP;
}

void ClickDown(BUTTON* pBtn)
{
	pBtn->imgCurrent = pBtn->imgDown;
}

void ClickUp(BUTTON* pBtn)
{
	pBtn->imgCurrent = pBtn->imgUp; //클릭업상태로 변경
	if (pBtn->m_Func != 0)
	{
		pBtn->m_Func(); //함수 실행
	}
}

bool IsOver(BUTTON* pBtn, int px, int py) //위치 구하는 함수
{
	if ((px >= pBtn->nX) && (px < (pBtn->nX + pBtn->rtClip.w)))
	{
		if ((py >= pBtn->nY) && (py < (pBtn->nY + pBtn->rtClip.h)))
		{
			return true;
		}
	}
	return false;
}

void Toggle(BUTTON* pBtn)
{
	if (pBtn->imgCurrent == pBtn->imgUp)
		pBtn->imgCurrent = pBtn->imgDown;
	else
		pBtn->imgCurrent = pBtn->imgUp;		
}

void ResetOnUp(BUTTON* pBtn)
{
	pBtn->imgCurrent = pBtn->imgUp;
}

void SetCoord(BUTTON* pBtn, int x, int y)
{
	pBtn->nX = x;
	pBtn->nY = y;
}

void SetVisible(BUTTON* pBtn, bool visible)
{
	pBtn->bIsVisible = visible;
}

bool IsVisible(BUTTON* pBtn)
{
	return pBtn->bIsVisible;
}

void MouseDown(BUTTON* pBtn, int px, int py)
{
	if (IsOver(pBtn, px, py) && IsVisible(pBtn))
	{
		ClickDown(pBtn);
	}
}

void MouseUp(BUTTON* pBtn, int px, int py)
{
	if (IsOver(pBtn, px, py) && IsVisible(pBtn)) //마우스가 버튼 위에 있고 보이는 상태면
	{
		sndPlaySound(L"..\\Song\\Click.wav", SND_ASYNC); //효과음 재생
		//mciSendString(L"play ..\\Song\\Click.wav", NULL, 0, NULL);
		ClickUp(pBtn); //클릭 업 상태로 변경
		ResetOnUp(pBtn); //이미지 리셋
	}
}

void MouseHold(BUTTON* pBtn, int px, int py)
{
	if (IsOver(pBtn, px, py) && IsVisible(pBtn) && pBtn->isPlayingSong == false) //마우스가 버튼 위에 있고 보이는 상태면
	{
		pBtn->imgCurrent = pBtn->imgHold; //클릭업상태로 변경
	}
	else if (pBtn->isPlayingSong == false) //지금 플레이 되고 있는 버튼이 아니면
		ResetOnUp(pBtn); //이미지 리셋
}