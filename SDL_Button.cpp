#include "SDL_Button.h"
#include "stdafx.h"

BUTTON* InitButton(SDL_Renderer* screen, const char* szUp, const char* szDown, const char* szHold,
	int x, int y, std::function<void()> func)
{
	BUTTON* Temp;

	Temp = new BUTTON; //�����Ҵ�. �ַ��� �޸� ������ִ� ���
	SDL_Surface* imgTemp;

	imgTemp = SDL_LoadBMP(szUp);
	Uint32 colorkey = SDL_MapRGB(imgTemp->format, 255, 0, 255);
	SDL_SetColorKey(imgTemp, SDL_TRUE, colorkey);
	Temp->imgUp = SDL_CreateTextureFromSurface(screen, imgTemp); //�����̽��� �ؽ��ķ�

	imgTemp = SDL_LoadBMP(szDown);
	colorkey = SDL_MapRGB(imgTemp->format, 255, 0, 255); //���� Ű �� 
	SDL_SetColorKey(imgTemp, SDL_TRUE, colorkey); //���� Ű �� ����
	Temp->imgDown = SDL_CreateTextureFromSurface(screen, imgTemp);

	imgTemp = SDL_LoadBMP(szHold);
	colorkey = SDL_MapRGB(imgTemp->format, 255, 0, 255); //���� Ű �� 
	SDL_SetColorKey(imgTemp, SDL_TRUE, colorkey); //���� Ű �� ����
	Temp->imgHold = SDL_CreateTextureFromSurface(screen, imgTemp);

	Temp->imgCurrent = Temp->imgUp;
	Temp->rtClip.x = x;
	Temp->rtClip.y = y;
	Temp->rtClip.w = imgTemp->w;
	Temp->rtClip.h = imgTemp->h;

	SetCoord(Temp, x, y); //��ư ������ ����
	SetVisible(Temp, true); //true������ ��ȯ

	/*CSystem system;
	(system.*f)();*/
	Temp->m_Func = func; //�Լ� �ֱ�
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
	pBtn->imgCurrent = pBtn->imgUp; //Ŭ�������·� ����
	if (pBtn->m_Func != 0)
	{
		pBtn->m_Func(); //�Լ� ����
	}
}

bool IsOver(BUTTON* pBtn, int px, int py) //��ġ ���ϴ� �Լ�
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
	if (IsOver(pBtn, px, py) && IsVisible(pBtn)) //���콺�� ��ư ���� �ְ� ���̴� ���¸�
	{
		sndPlaySound(L"..\\Song\\Click.wav", SND_ASYNC); //ȿ���� ���
		//mciSendString(L"play ..\\Song\\Click.wav", NULL, 0, NULL);
		ClickUp(pBtn); //Ŭ�� �� ���·� ����
		ResetOnUp(pBtn); //�̹��� ����
	}
}

void MouseHold(BUTTON* pBtn, int px, int py)
{
	if (IsOver(pBtn, px, py) && IsVisible(pBtn) && pBtn->isPlayingSong == false) //���콺�� ��ư ���� �ְ� ���̴� ���¸�
	{
		pBtn->imgCurrent = pBtn->imgHold; //Ŭ�������·� ����
	}
	else if (pBtn->isPlayingSong == false) //���� �÷��� �ǰ� �ִ� ��ư�� �ƴϸ�
		ResetOnUp(pBtn); //�̹��� ����
}