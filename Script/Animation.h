#pragma once

typedef struct tagChar
{
	SDL_Renderer* pRender; //�׸��� �׸��� ���� �޾ƿ͵� ��
	SDL_Texture* pAniImage;
	int numAni;
	int x[5]; //�뷡���� ������ �ٸ���
	int y[5];
	//int w, h;
	int chType; //ĳ���� ��ȣ

	SDL_Rect rtClip [256];
}CHARACTER;

//typedef struct charTiming
//{
//	int songtime;
//	int Delay;
//	bool isPlay;
//};

CHARACTER* InitCharacter(SDL_Renderer* pRender, const char* ImgDIR, int x, int y, int _numAni, int chType); //������Ʈ �ʱ�ȭ
void SetCoord(CHARACTER * obj, int _songnum);
void Draw(CHARACTER* obj, int _songnum); //������Ʈ �׸���
void PauseDraw(CHARACTER* obj,int _songnum); //������ �׸���
void Release(CHARACTER* obj); //������Ʈ ����/����
void AniReset();