#pragma once

typedef struct tagChar
{
	SDL_Renderer* pRender; //그림을 그리는 순간 받아와도 됨
	SDL_Texture* pAniImage;
	int numAni;
	int x[5]; //노래별로 포지션 다르게
	int y[5];
	//int w, h;
	int chType; //캐릭터 번호

	SDL_Rect rtClip [256];
}CHARACTER;

//typedef struct charTiming
//{
//	int songtime;
//	int Delay;
//	bool isPlay;
//};

CHARACTER* InitCharacter(SDL_Renderer* pRender, const char* ImgDIR, int x, int y, int _numAni, int chType); //오브젝트 초기화
void SetCoord(CHARACTER * obj, int _songnum);
void Draw(CHARACTER* obj, int _songnum); //오브젝트 그리기
void PauseDraw(CHARACTER* obj,int _songnum); //대기상태 그리기
void Release(CHARACTER* obj); //오브젝트 해제/종료
void AniReset();