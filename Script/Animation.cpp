#include "stdafx.h"

SDL_Rect rtAniImage[256];
static int AniCount[5] = {0, };
//그대여 28
//봄이좋냐 37
float Delay[6][5] =
{
	{28 ,28, 28, 28, 28},
	{15, 15, 15, 15, 15},
	{20, 20, 20, 20, 20},
	{20, 20, 20, 20, 20},
	{20, 20, 16, 16, 16},
};
int DelayCount[5] = {0, };

CHARACTER* InitCharacter(SDL_Renderer* pRender, const char* ImgDIR, int x, int y, int _numAni, int _chType) //렌더, 애니메이션 장수
{
	CHARACTER* Temp;
	Temp = new CHARACTER;
	Temp->pRender = pRender;
	SDL_Surface* pAniImage = SDL_LoadBMP(ImgDIR);

	Uint32 ColorKey;
	ColorKey = SDL_MapRGB(pAniImage->format, 255, 0, 255);
	SDL_SetColorKey(pAniImage, SDL_TRUE, ColorKey);
	
	Temp->numAni = _numAni;
	Temp->pAniImage = SDL_CreateTextureFromSurface(pRender, pAniImage);
	SDL_FreeSurface(pAniImage);
	Temp->x[0] = x;
	Temp->y[0] = y;

	for (int i = 0; i <= Temp->numAni; i++)
	{
		rtAniImage[i].x = i * 512;
		rtAniImage[i].y = 0;
		rtAniImage[i].w = 512;
		rtAniImage[i].h = 512;
	}
	Temp->chType = _chType;
	return Temp;
}

void SetCoord(CHARACTER* obj, int _songnum) //노래에 따라서 캐릭터 위치 설정
{
	for (int i = 0; i < 5; i++)
	{
		switch (obj->chType)
		{
		case 0:
			obj->x[i] = 300; obj->y[i] = 100; break;
		case 1:
			obj->x[i] = 50;  obj->y[i] = 180; break;
		case 2:
			obj->x[i] = 550; obj->y[i] = 150; break;
		case 3:
			obj->x[i] = 150; obj->y[i] = 250; break;
		case 4:
			obj->x[i] = 400; obj->y[i] = 230; break;
		}
	}

	if (_songnum == 1 && obj->chType == 2)//봄이좋냐 && 기타솔로일 경우 배치 변경
	{
		obj->x[1] = 500; obj->y[1] = 220;
	}
	if (_songnum == 0 && obj->chType == 3)//벚꽃엔딩 && 기타보컬일 경우 배치 변경
	{
		obj->x[0] = 300;
	}

}

void Draw(CHARACTER* obj, int _songnum)
{
	if (obj == NULL) return; 
	
	SDL_Rect rtOutAni = { obj->x[_songnum], obj->y[_songnum], 512, 512 };
	SDL_RenderCopy(obj->pRender, obj->pAniImage, &rtAniImage[AniCount[obj->chType]], &rtOutAni);

	if (AniCount[obj->chType] >= obj->numAni - 1) AniCount[obj->chType] = 0; //마지막 장에 도달하면 첫 장으로 돌아가기
	else 
	{
		if (DelayCount[obj->chType] > Delay[_songnum][obj->chType]) //카운트가 딜레이를 넘기면
		{
			DelayCount[obj->chType] = 0; //딜레이 초기화
			AniCount[obj->chType]++; //다음 장 넘기기
		}
		else DelayCount[obj->chType]++; //딜레이 카운트 추가
	}
}

void PauseDraw(CHARACTER* obj, int _songnum) //정지상태 그리기
{
	if (obj == NULL) return;
	switch (_songnum) //0이 건반 1이 플룻 2가 기타 솔로 3이 기타 보컬 4가 여자보컬
	{
		case 0:
			if (obj->chType == 4) return; //이 노래엔 여자 보컬이 안나오기 때문에 return
			else break;
		case 1:
			if (obj->chType != 3) return;
			else break;
		case 2: break;
		case 3: break;
		case 4: break;
	}
	SDL_Rect rtOutAni = { obj->x[_songnum], obj->y[_songnum], 512, 512 };
	SDL_RenderCopy(obj->pRender, obj->pAniImage, &rtAniImage[0], &rtOutAni);
}

void Release(CHARACTER* obj) 
{
	if (obj == NULL) return;

	obj->pRender = NULL;
	SDL_DestroyTexture(obj->pAniImage);
	free(obj);
}

bool CSystem::Aninod1(int _songnum) //건반
{
	switch (_songnum)
	{
		case 0: 
		{
			if (Nod(40, 54.5))	 return true;
			if (Nod(56.5, 104))	 return true;
			if (Nod(120, 134.5)) return true;
			if (Nod(136.5, 200)) return true;
			if (Nod(217, 259))	 return true;
			if (Nod(40, 54.5))	 return true;
			break;
		}
		case 1: return false;
		case 2: 
		{
			if (Nod(2.5, 186))	 return true;
			break;
		}
		case 3: 
		{
			if ( Nod(6.5, 78) )		 return true;
			if ( Nod(82, 151.5) )	 return true;
			if ( Nod(152.5, 176) )	 return true;
			if ( Nod(187.5, 200) )	 return true;
			break;
		}
		case 4: 
		{
			if (Nod(0, 180))	 return true;
		}
	}
	return false;
}

bool CSystem::Aninod2(int _songnum) //플룻
{
	switch (_songnum)
	{
		case 0: 
		{
			if (Nod(8, 24))	return true;
			if (Nod(88, 104)) return true;
			break;
		}
		case 1: return false;
		case 2: 
		{
			if (Nod(61, 81.5))	 return true;
			if (Nod(123, 142))	 return true;
			break;
		}
		case 3: 
		{
			if (Nod(29, 78))	return true;
			break;
		}
		case 4:
		{
			if (Nod(39, 67))		 return true;
			if (Nod(95, 132))		 return true;
			if (Nod(133.5, 180))	 return true;
			break;
		}
	}
	return false;
}

bool CSystem::Aninod3(int _songnum) //기타솔로
{
	switch (_songnum)
	{
		case 0:
		{
			if (Nod(0, 4))		 return true;  //{ Delay[0][2] = 28; }
			if (Nod(4, 6.8))	 return true; //{ Delay[0][2] = 14; }
			if (Nod(8, 54.5))	 return true;
			if (Nod(56.5, 104))	 return true;
			if (Nod(104, 108))	 return true; //{ Delay[0][2] = 28; return true; }
			if (Nod(108, 112))	 return true; //{ Delay[0][2] = 14; return true; }
			if (Nod(112, 134.5)) return true;
			if (Nod(136.5, 200)) return true;
			if (Nod(217, 249))	 return true;
			break;
		}
		case 1: return true;
		case 2:
		{
			if (Nod(61, 81.5))	 return true;
			if (Nod(123, 142))	 return true;
			break;
		}
		case 3:
		{
			if (Nod(29, 78))		 return true;
			if (Nod(128, 151.5))	 return true;
			if (Nod(152.5, 163))	 return true;
			if (Nod(163.8, 176))	 return true;
			if (Nod(187.5, 200))	 return true;
			break;
		}
		case 4: 
		{
			if (Nod(28, 67))		 return true;
			if (Nod(95, 132))		 return true;
			if (Nod(133.5, 180))	 return true;
			break;
		}
	}
	return false;
}
bool CSystem::Aninod4(int _songnum) //기타보컬
{
	switch (_songnum)
	{
		case 0: 
		{
			if (Nod(0, 4))		 return true; //{ Delay[0][3] = 28; return true; }
			if (Nod(4, 6.8))	 return true; //{ Delay[0][3] = 14; return true; }
			if (Nod(8, 54.5))	 return true;
			if (Nod(56.5, 104))	 return true;
			if (Nod(104, 108))	 return true; //{ Delay[0][3] = 28; return true; }
			if (Nod(108, 112))	 return true; //{ Delay[0][3] = 14; return true; }
			if (Nod(112, 134.5)) return true;
			if (Nod(136.5, 200)) return true;
			if (Nod(201, 249))	 return true;
			if (Nod(250, 260))	 return true;//{ Delay[0][3] = 56; return true; }
			break;
		}
		case 1: return true; //Delay[1][3] = 30;
		case 2:
		{
			if (Nod(23, 61))	 return true;
			if (Nod(81.5, 123))	 return true;
			if (Nod(142, 166))	 return true;

			break;
		}
		case 3: 
		{
			if (Nod(29, 78))		return true;
			if (Nod(82, 105))		return true;
			if (Nod(128, 151.5))	return true;
			if (Nod(152.5, 162.5))	return true;
			if (Nod(163.8, 176))	return true;
			if (Nod(187.5, 20))		return true;
			break;
		}
		case 4: 
		{
			if (Nod(10, 67))		 return true;
			if (Nod(75.5, 132))		 return true;
			if (Nod(133.5, 180))	 return true;
			break;
		}
	}
	return false;
}
bool CSystem::Aninod5(int _songnum) //여자보컬
{
	switch (_songnum)
	{
	case 0: return false;
	case 1: return false;
	case 2: 
	{
		if (Nod(2.5, 23))	 return true;
		if (Nod(23, 61))	 return true;
		if (Nod(61, 81.5))	 return true;
		if (Nod(81.5, 123))  return true;
		if (Nod(123, 142))   return true;
		if (Nod(142, 166))	 return true;
		if (Nod(166, 186))   return true;
		if (Nod(166, 200))   return true;

		break;
	}
	case 3:
	{
		if (Nod(6.5, 78))		return true;
		if (Nod(105, 162.7))	return true;
		if (Nod(163.8, 200))	return true;

		break;
	}
	case 4:
	{
		if (Nod(10, 67))		 return true;
		if (Nod(75.5, 132))		 return true;
		if (Nod(133.5, 180))	 return true;
		break;
	}
	}
	return false;
}

void AniReset() //애니메이션 장면 초기화
{
	for (int i = 0; i < 5; i++)
	{
		AniCount[i] = 0;
	}
}

bool CSystem::Nod(float start_Time, float end_Time)
{
	if (start_Time < m_fSongAcculTime && m_fSongAcculTime < end_Time) return true;
	else return false;
}

bool CSystem::CheckAniDelay(CHARACTER* obj) //멈추는 부분에서 부자연스럽게 급정지하는 현상을 막기 위함
{
	if (DelayCount[obj->chType] > 0) return false; //만약 잔류하는 딜레이 카운트가 있다면 false 반환
	else return true;
}

void CSystem::SetDelay(int songnum) //노래별 딜레이 구간 설정해주기
{
	switch (songnum)
	{
	case 0: //벚꽃엔딩
		if ((int)m_fSongAcculTime == 0) //노래 시작될 때 초기화
		{
			Delay[0][0] = 28;
			Delay[0][1] = 28;
			Delay[0][2] = 28;
			Delay[0][3] = 28;
			Delay[0][4] = 28;
		}
		if ((int)m_fSongAcculTime == 4)
		{
			Delay[0][2] = 14;
			Delay[0][3] = 14;
		}
		if ((int)m_fSongAcculTime == 104)
		{
			Delay[0][2] = 28;
			Delay[0][3] = 28;
		}
		if ((int)m_fSongAcculTime == 108)
		{
			Delay[0][2] = 14;
			Delay[0][3] = 14;
		}
		if ((int)m_fSongAcculTime == 108)
		{
			Delay[0][3] = 56;
		}
		break;
	case 1: //봄이좋냐
		if ((int)m_fSongAcculTime == 0) //노래 시작될 때 초기화
		{
			Delay[1][0] = 15;
			Delay[1][1] = 15;
			Delay[1][2] = 15;
			Delay[1][3] = 15;
			Delay[1][4] = 15;
		}
		if ((int)m_fSongAcculTime == 9)
		{
			Delay[1][2] = 30; 
			Delay[1][3] = 30;
		}
		if ((int)m_fSongAcculTime == 11)
		{
			Delay[1][2] = 15;
			Delay[1][3] = 15;
		}
		break;
	case 2://우연히봄
		if ((int)m_fSongAcculTime == 0) //노래 시작될 때 초기화
		{
			Delay[2][0] = 20;
			Delay[2][1] = 20;
			Delay[2][2] = 20;
			Delay[2][3] = 20;
			Delay[2][4] = 20;
		}
		if ((int)m_fSongAcculTime == 23)
		{
			Delay[2][4] = 30;
		}
		if ((int)m_fSongAcculTime == 61)
		{
			Delay[2][4] = 20;
		}
		if ((int)m_fSongAcculTime == 81.5)
		{
			Delay[2][4] = 30;
		}
		if ((int)m_fSongAcculTime == 123)
		{
			Delay[2][4] = 20;
		}
		if ((int)m_fSongAcculTime == 142)
		{
			Delay[2][4] = 30;
		}
		break;
	case 3:
		if ((int)m_fSongAcculTime == 0) //노래 시작될 때 초기화
		{
			Delay[3][0] = 20;
			Delay[3][1] = 20;
			Delay[3][2] = 20;
			Delay[3][3] = 20;
			Delay[3][4] = 20;
		}
		if ((int)m_fSongAcculTime == 52)
		{
			Delay[3][0] = 30;
			Delay[3][1] = 30;
			Delay[3][2] = 30;
			Delay[3][3] = 30;
			Delay[3][4] = 30;
		}
		if ((int)m_fSongAcculTime == 56)
		{
			Delay[3][0] = 20;
			Delay[3][1] = 20;
			Delay[3][2] = 20;
			Delay[3][3] = 20;
			Delay[3][4] = 20;
		}
		if ((int)m_fSongAcculTime == 66)
		{
			Delay[3][0] = 30;
			Delay[3][1] = 30;
			Delay[3][2] = 30;
			Delay[3][3] = 30;
			Delay[3][4] = 30;
		}
		if ((int)m_fSongAcculTime == 67)
		{
			Delay[3][0] = 20;
			Delay[3][1] = 20;
			Delay[3][2] = 20;
			Delay[3][3] = 20;
			Delay[3][4] = 20;
		}
	case 4: //썸탈거야
		if ((int)m_fSongAcculTime == 0) //노래 시작될 때 초기화
		{
			Delay[4][0] = 20;
			Delay[4][1] = 20;
			Delay[4][2] = 16;
			Delay[4][3] = 16;
			Delay[4][4] = 16;
		}
		if ((int)m_fSongAcculTime == 37)
		{
			Delay[4][0] = 30;
			Delay[4][2] = 30;
			Delay[4][3] = 30;
			Delay[4][4] = 30;
		}
		if ((int)m_fSongAcculTime == 39)
		{
			Delay[4][0] = 20;
			Delay[4][2] = 20;
			Delay[4][3] = 20;
			Delay[4][4] = 20;
		}
	}
}