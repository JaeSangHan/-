#include "stdafx.h"

#define IMG_DIR		"..\\Image\\Button\\"

bool turn = true; //�⺻ bg ��ǥ�Ҷ� �ӽ÷� ���� �ѱ� ���ؼ� ����

BUTTON* Change_prvScene;
BUTTON* Change_nextScene;
BUTTON* PlaySongBtn;
BUTTON* StopSongBtn;

BUTTON* PlayAniBtn;
BUTTON* StopAniBtn;

BUTTON* Song1;
BUTTON* Song2;
BUTTON* Song3;
BUTTON* Song4;
BUTTON* Song5;

BUTTON* Help_Btn;
BUTTON* Credit_Btn;
BUTTON* Close_Btn;
BUTTON* Exit_Btn;

CHARACTER* ch1;
CHARACTER* ch2;
CHARACTER* ch3;
CHARACTER* ch4;
CHARACTER* ch5;

FILE *sinc;

SDL_Surface* BackGroundSurface; //���ȭ�� ������
SDL_Texture* BackGroundTexture; //���ȭ�� �ؽ���
SDL_Surface* CursorSurface; //Ŀ�� ������
SDL_Texture* CursorTexture; //Ŀ�� �ؽ���

SDL_Rect rtTemp; //���ȭ��
SDL_Rect rtOutAni; //Ŀ��

char strTemp[3][256] = { IMG_DIR, IMG_DIR }; //�̹��� ��ġ

CSystem::CSystem(void) //���� �𸣰����� ������ �ȵǴ� ��1 //���ο��� ���ϸ��� ȣ��
{ 
	
}

CSystem::~CSystem(void) //���� �𸣰����� ������ �ȵǴ� ��2
{
	//SDL_Quit();
}

void CSystem::DrawCursor(SDL_Surface * img, int x, int y) //Ŀ�� �׸���
{
	SDL_Rect dest;
	SDL_Rect rtOutAni = { x, y, 100, 100 };
	dest.x = x;
	dest.y = y;
	SDL_RenderCopy(m_pRender, CursorTexture, NULL, &rtOutAni); //���ȭ�� ����
}

void CSystem::PreviousScene()
{
	StopMusic();
	mciSendString(L"play ..\\Song\\Song0.mp3", NULL, 0, NULL); //�������ڸ��� �⺻ bgmƲ��
	SceneNumber = 1;
	BackGroundSurface = SDL_LoadBMP("..\\Image\\BackGround\\Title_bg.bmp");
	BackGroundTexture = SDL_CreateTextureFromSurface(m_pRender, BackGroundSurface);
}

void CSystem::NextScene()
{
	SceneNumber = 2;
	BackGroundSurface = SDL_LoadBMP("..\\Image\\BackGround\\Ingame_bg.bmp");
	BackGroundTexture = SDL_CreateTextureFromSurface(m_pRender, BackGroundSurface);
	mciSendString(L"stop ..\\Song\\Song0.mp3", NULL, 0, NULL); //�⺻ bgm ���߱�
}

void CSystem::HelpPannel()
{
	SceneNumber = 0;
	BackGroundSurface = SDL_LoadBMP("..\\Image\\Pannel\\HelpPannel.bmp");
	BackGroundTexture = SDL_CreateTextureFromSurface(m_pRender, BackGroundSurface);
}

void CSystem::CreditPannel()
{
	SceneNumber = 0;
	BackGroundSurface = SDL_LoadBMP("..\\Image\\Pannel\\CreditPannel.bmp");
	BackGroundTexture = SDL_CreateTextureFromSurface(m_pRender, BackGroundSurface);
}

void CSystem::ExitBtn()
{
	Terminate();
	exit(0);
}

void CSystem::PlayMusic()
{
	isMusicPlay = true;
	SetVisible(StopSongBtn, true); //�����ư ���̰� �ϱ�
	SetVisible(PlaySongBtn, false);
	switch (SongNumber)
	{
		case 0: mciSendString(L"play ..\\Song\\Song1.mp3", NULL, 0, NULL); break;
		case 1: mciSendString(L"play ..\\Song\\Song2.mp3", NULL, 0, NULL); break;
		case 2: mciSendString(L"play ..\\Song\\Song3.mp3", NULL, 0, NULL); break;
		case 3: mciSendString(L"play ..\\Song\\Song4.mp3", NULL, 0, NULL); break;
		case 4: mciSendString(L"play ..\\Song\\Song5.mp3", NULL, 0, NULL); break;
	}
	PlayingSongList();

	SetCoord(ch1, SongNumber); //�ִϸ��̼� ������ ���ġ
	SetCoord(ch2, SongNumber);
	SetCoord(ch3, SongNumber);
	SetCoord(ch4, SongNumber);
	SetCoord(ch5, SongNumber);
}

void CSystem::PauseMusic() //TODO: �Ͻ� ���� ��, �ٸ� ���� ������ ����ϸ� ��ø�Ǵ� ���װ� ����
{
	isMusicPlay = false; 
	SetVisible(PlaySongBtn, true); //�÷��� ��ư ���̰� �ϱ�
	SetVisible(StopSongBtn, false);
	switch (SongNumber)
	{
	case 0: mciSendString(L"pause ..\\Song\\Song1.mp3", NULL, 0, NULL); break;
	case 1: mciSendString(L"pause ..\\Song\\Song2.mp3", NULL, 0, NULL); break;
	case 2: mciSendString(L"pause ..\\Song\\Song3.mp3", NULL, 0, NULL); break;
	case 3: mciSendString(L"pause ..\\Song\\Song4.mp3", NULL, 0, NULL); break;
	case 4: mciSendString(L"pause ..\\Song\\Song5.mp3", NULL, 0, NULL); break;
	}
	PauseSongList();
}

void CSystem::StopMusic() //��� ���� ����
{
	ClickUp(StopSongBtn);
	m_fSongAcculTime = 0; //���� �����ð� �ʱ�ȭ
	mciSendString(L"stop ..\\Song\\Song1.mp3", NULL, 0, NULL);
	mciSendString(L"stop ..\\Song\\Song2.mp3", NULL, 0, NULL);
	mciSendString(L"stop ..\\Song\\Song3.mp3", NULL, 0, NULL);
	mciSendString(L"stop ..\\Song\\Song4.mp3", NULL, 0, NULL);
	mciSendString(L"stop ..\\Song\\Song5.mp3", NULL, 0, NULL);
	PauseSongList();
}

void CSystem::PlayAni()
{
	isAniPlay = true;
	SetVisible(StopAniBtn, true); //�����ư ���̰� �ϱ�
	SetVisible(PlayAniBtn, false);
}

void CSystem::StopAni()
{
	isAniPlay = false;
	SetVisible(PlayAniBtn, true); //�����ư ���̰� �ϱ�
	SetVisible(StopAniBtn, false);
}

void CSystem::SetSong1() {	StopMusic(); SongNumber = 0;}
void CSystem::SetSong2() {	StopMusic(); SongNumber = 1;}
void CSystem::SetSong3() {	StopMusic(); SongNumber = 2;}
void CSystem::SetSong4() {	StopMusic(); SongNumber = 3;}
void CSystem::SetSong5() {	StopMusic(); SongNumber = 4;}

void CSystem::PlayingSongList() //�������� �۸���Ʈ�� �̹��� �ҷ�����
{
	SDL_Surface* SurfaceimgTemp;
	SDL_Texture* TextureimgTemp;
	switch (SongNumber)
	{
	case 0: SurfaceimgTemp = SDL_LoadBMP("..\\Image\\Button\\01_Song1_04.bmp"); break;
	case 1: SurfaceimgTemp = SDL_LoadBMP("..\\Image\\Button\\02_Song2_04.bmp"); break;
	case 2: SurfaceimgTemp = SDL_LoadBMP("..\\Image\\Button\\03_Song3_04.bmp"); break;
	case 3: SurfaceimgTemp = SDL_LoadBMP("..\\Image\\Button\\04_Song4_04.bmp"); break;
	case 4: SurfaceimgTemp = SDL_LoadBMP("..\\Image\\Button\\05_Song5_04.bmp"); break;
	}
	Uint32 colorkey = SDL_MapRGB(SurfaceimgTemp->format, 255, 0, 255);
	SDL_SetColorKey(SurfaceimgTemp, SDL_TRUE, colorkey); //���� Ű �� ����
	TextureimgTemp = SDL_CreateTextureFromSurface(m_pRender, SurfaceimgTemp);
	switch (SongNumber) //�ؽ��ĸ� ������ �÷������� ��ư�� ������ true�� �ٲ۴�
	{
	case 0: { Song1->imgCurrent = TextureimgTemp;	Song1->isPlayingSong = true;  break;}
	case 1: { Song2->imgCurrent = TextureimgTemp;	Song2->isPlayingSong = true;  break;}
	case 2: { Song3->imgCurrent = TextureimgTemp;	Song3->isPlayingSong = true;  break;}
	case 3: { Song4->imgCurrent = TextureimgTemp;	Song4->isPlayingSong = true;  break;}
	case 4: { Song5->imgCurrent = TextureimgTemp;	Song5->isPlayingSong = true;  break;}
	}
	SDL_FreeSurface(SurfaceimgTemp);
}

void CSystem::PauseSongList() //���� ���� ������ �۸���Ʈ �ҷ�����
{
	switch (SongNumber)
	{
	case 0: { Song1->isPlayingSong = false;  break; }
	case 1: { Song2->isPlayingSong = false;  break; }
	case 2: { Song3->isPlayingSong = false;  break; }
	case 3: { Song4->isPlayingSong = false;  break; }
	case 4: { Song5->isPlayingSong = false;  break; }
	}
}

bool CSystem::Initialize()  //���ο��� �ҷ����� ������ �����Ǵ� �κ�
{
	CBaseWindow::Initialize(); //â ���� �⺻����
	CTimeManager::Initialize(); //srand ��� �ð� ���� �⺻�����ε�
	
	m_pGameFrame = new CFrameSkip; //������ ����
	m_pGameFrame->SetFramePerSec(60); //60fps

	m_pInputManager = new CInputManager;
	m_pInputManager->SetInputHandler(this); 

	////�� �Ʒ��� ������Ʈ �ʱ�ȭ �ڵ带 ����////
	sinc = fopen("SINC.txt", "w"); //��ũ ������ �޸���

	SDL_ShowCursor(0); //�⺻ Ŀ�� �����
	CursorSurface = SDL_LoadBMP("mycursor.bmp"); //���콺 Ŀ��
	Uint32 colorkey = SDL_MapRGB(CursorSurface->format, 255, 0, 255);
	SDL_SetColorKey(CursorSurface, SDL_TRUE, colorkey); //���� Ű �� ����
	CursorTexture = SDL_CreateTextureFromSurface(m_pRender, CursorSurface);

	ch1 = InitCharacter(m_pRender, "..\\Animation\\ch1.bmp", 300, 100, 7, 0); //�ǹ�
	ch2 = InitCharacter(m_pRender, "..\\Animation\\ch2.bmp", 50, 180, 6, 1); //�÷�
	ch3 = InitCharacter(m_pRender, "..\\Animation\\ch3.bmp", 570, 150, 5, 2); //��Ÿ�ַ�
	ch4 = InitCharacter(m_pRender, "..\\Animation\\ch4.bmp", 130, 250, 5, 3); //��Ÿ����
	ch5 = InitCharacter(m_pRender, "..\\Animation\\ch5.bmp", 400, 230, 5, 4); //���ں���

	strcpy_s(strTemp[0], IMG_DIR);				strcpy_s(strTemp[1], IMG_DIR);					strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "StartBtn_Up.bmp");	strcat_s(strTemp[1], "StartBtn_Down.bmp");		strcat_s(strTemp[2], "StartBtn_Hold.bmp");
	Change_nextScene = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 200, 550, [&]() { NextScene(); });
	//�� ��ŸƮ ��ư

	strcpy_s(strTemp[0], IMG_DIR);			 strcpy_s(strTemp[1], IMG_DIR);					    strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "HelpBtn_Up.bmp");	 strcat_s(strTemp[1], "HelpBtn_Down.bmp");		    strcat_s(strTemp[2], "HelpBtn_Hold.bmp");
	Help_Btn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 400, 550, [&]() { HelpPannel(); });
	//�� ���� ��ư

	strcpy_s(strTemp[0], IMG_DIR);				strcpy_s(strTemp[1], IMG_DIR);                  strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "CreditBtn_Up.bmp");	strcat_s(strTemp[1], "CreditBtn_Down.bmp");		strcat_s(strTemp[2], "CreditBtn_Hold.bmp");
	Credit_Btn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 600, 550, [&]() { CreditPannel(); });
	//�� ũ���� ��ư

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "ExitBtn_Up.bmp");			strcat_s(strTemp[1], "ExitBtn_Down.bmp");	strcat_s(strTemp[2], "ExitBtn_Hold.bmp");
	Exit_Btn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 800, 550, [&]() { ExitBtn(); });
	//�� ���� ��ư

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "BackBtn_Up.bmp");			strcat_s(strTemp[1], "BackBtn_Down.bmp");	strcat_s(strTemp[2], "BackBtn_Hold.bmp");
	Close_Btn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1100, 0, [&]() { PreviousScene(); });
	//�� '�ݱ�' ��ư
	 
	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "HomeBtn_Up.bmp");			strcat_s(strTemp[1], "HomeBtn_Down.bmp");   strcat_s(strTemp[2], "HomeBtn_Hold.bmp");
	Change_prvScene = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 0, 0, [&]() { PreviousScene(); });
	//�� Ȩ ��ư

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "PlayMusicBtn.bmp");		strcat_s(strTemp[1], "PlayMusicBtn.bmp");	strcat_s(strTemp[2], "PlayMusicBtn.bmp");
	PlaySongBtn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1115, 75, [&]() { PlayMusic(); });
	//�� �뷡 ��� ��ư

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "StopMusicBtn.bmp");		strcat_s(strTemp[1], "StopMusicBtn.bmp");   strcat_s(strTemp[2], "StopMusicBtn.bmp");
	StopSongBtn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1115, 75, [&]() { PauseMusic(); });
	SetVisible(StopSongBtn, false);
	//�� �뷡 ���� ��ư 


	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "PlayAniBtn.bmp");		strcat_s(strTemp[1], "PlayAniBtn.bmp");   strcat_s(strTemp[2], "PlayAniBtn.bmp");
	PlayAniBtn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2],1180, 0, [&]() { PlayAni(); });
	//�� �ִ� ��� ��ư 

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "StopAniBtn.bmp");		strcat_s(strTemp[1], "StopAniBtn.bmp");   strcat_s(strTemp[2], "StopAniBtn.bmp");
	StopAniBtn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1180, 0, [&]() { StopAni(); });
	SetVisible(StopSongBtn, false);
	//�� �ִ� ���� ��ư 

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "01_Song1_01.bmp");		strcat_s(strTemp[1], "01_Song1_03.bmp");    strcat_s(strTemp[2], "01_Song1_02.bmp");
	Song1 = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1000, 120, [&]() { SetSong1(); });
	//�� ���ɿ��� 
																							   
	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "02_Song2_01.bmp");		strcat_s(strTemp[1], "02_Song2_03.bmp");    strcat_s(strTemp[2], "02_Song2_02.bmp");
	Song2 = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1000, 250, [&]() { SetSong2(); });
	//�� �������� 
																							    
	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "03_Song3_01.bmp");		strcat_s(strTemp[1], "03_Song3_03.bmp");    strcat_s(strTemp[2], "03_Song3_02.bmp");
	Song3 = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1000, 330, [&]() { SetSong3(); });
	//�� �쿬�� ��

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "04_Song4_01.bmp");	strcat_s(strTemp[1], "04_Song4_03.bmp");	    strcat_s(strTemp[2], "04_Song4_02.bmp");
	Song4 = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1000, 410, [&]() { SetSong4(); });
	//�� ���ָ��ٰ�

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "05_Song5_01.bmp");	strcat_s(strTemp[1], "05_Song5_03.bmp");	    strcat_s(strTemp[2], "05_Song5_02.bmp");
	Song5 = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1000, 490, [&]() { SetSong5(); });
	//�� ��Ż�ž�

	/////�� ���� ������Ʈ �ʱ�ȭ �ڵ带 ����/////
	PreviousScene(); //ó���� 1�� ������ ����
	return true;
}

void CSystem::Pulse()  //�д� //������Ʈ
{
	CTimeManager::Pulse(isMusicPlay);

	//m_pGameFrame = new CFrameSkip; //������ ����
	//m_pGameFrame->SetFramePerSec(60); //60fps

	float fTimeStep = CTimeManager::GetTimeStep();

	if (m_pGameFrame->Update(fTimeStep))
	{
		//====================================
		//���⿡ ������Ʈ ���μ��� �ڵ带 ��������. //update
		SDL_RenderCopy(m_pRender, BackGroundTexture, NULL, NULL); //���ȭ�� ����
		//printf("%.1f�� �뷡��ȣ %d\n", m_fSongAcculTime, SongNumber);

		switch (SceneNumber)
		{	
			case 0:
				Draw(m_pRender, Close_Btn);
				break;
			case 1:
				Draw(m_pRender, Change_nextScene);
				Draw(m_pRender, Exit_Btn);
				Draw(m_pRender, Help_Btn);
				Draw(m_pRender, Credit_Btn);
				break;

			case 2:
				Draw(m_pRender, Change_prvScene);

				Draw(m_pRender, Song1);
				Draw(m_pRender, Song2);
				Draw(m_pRender, Song3);
				Draw(m_pRender, Song4);
				Draw(m_pRender, Song5);

				Draw(m_pRender, PlaySongBtn);
				Draw(m_pRender, StopSongBtn);
				Draw(m_pRender, PlayAniBtn);
				Draw(m_pRender, StopAniBtn);
				printf("%.2f\n", m_fSongAcculTime);
				if (isMusicPlay) //������ ������϶�
				{
					SetDelay(SongNumber); //������ �ھ��ֱ�
					if (Aninod1(SongNumber)) Draw(ch1, SongNumber); //Ÿ�̹� �缭 ����
					else if (isAniPlay) PauseDraw(ch1, SongNumber); //if (delay�� �ܷ�) Draw(ch1, Songnum) �߰��ϱ�'

					if (Aninod2(SongNumber)) Draw(ch2, SongNumber); //Ÿ�̹� �缭 ����
					else if (isAniPlay) PauseDraw(ch2, SongNumber);

					if (Aninod3(SongNumber)) Draw(ch3, SongNumber); //Ÿ�̹� �缭 ����
					else if (isAniPlay) PauseDraw(ch3, SongNumber);

					if (Aninod4(SongNumber)) Draw(ch4, SongNumber); //Ÿ�̹� �缭 ����
					else if (isAniPlay) PauseDraw(ch4, SongNumber);

					if (Aninod5(SongNumber)) Draw(ch5, SongNumber); //Ÿ�̹� �缭 ����
					else if (isAniPlay) PauseDraw(ch5, SongNumber);
				}

				break;
		}
		//====================================
		m_pInputManager->Pulse();
		SDL_RenderPresent(m_pRender);
	}
}

void CSystem::Terminate() 
{
	//�� �Ʒ��� ������Ʈ ����/���� �ڵ带 ��������.
	SDL_FreeSurface(BackGroundSurface);
	SDL_DestroyTexture(BackGroundTexture);

	SDL_FreeSurface(CursorSurface);
	SDL_DestroyTexture(CursorTexture);

	Release(Change_prvScene);
	Release(Change_nextScene);
	Release(PlaySongBtn);
	Release(StopSongBtn);
	Release(PlayAniBtn);
	Release(StopAniBtn);
	Release(Song1);
	Release(Song2);
	Release(Song3);
	Release(Song4);
	Release(Song5);
	Release(Credit_Btn);
	Release(Help_Btn);
	Release(Close_Btn);
	Release(Exit_Btn);

	Release(ch1);
	Release(ch2);
	Release(ch3);
	Release(ch4);
	Release(ch5);

	fclose(sinc); //��ũ ��Ͽ� �޸���

	//�� ���� ������Ʈ ����/���� �ڵ带 ��������.
	m_pInputManager->Terminate();
	CBaseWindow::Terminate(); //��Ʈ���� ���� //��Ʈ���� ��ũ��
	CTimeManager::Terminate();
}

void CSystem::Run() 
{
	while (m_bIsGameRun)
	{
		Pulse();
	}
}

#define g_pKeyCodeScan(vk) (m_pInputManager->GetOldKeyState(vk)&&m_pInputManager->GetCurKeyState(vk))

void CSystem::KeyboardHandler() 
{
	if (GetAsyncKeyState(0x1B) & 0x0001) //esc
	{
		Terminate();
		exit(0);
	}
	{	if (GetAsyncKeyState(VK_SPACE) & 0x0001) //space

		AniReset();
	}
	if (GetAsyncKeyState(0x31) & 0x0001) //1
	{
		fprintf(sinc, "���۽ð� : %.2f\n", m_fSongAcculTime);
	}
	if (GetAsyncKeyState(0x51) & 0x0001) //Q
	{
		fprintf(sinc, "�����ð� : %.2f\n", m_fSongAcculTime);
	}

	//if (GetAsyncKeyState(0x33) & 0x0001)
	//{
	//	fprintf(sinc, "%f\n", m_fSongAcculTime);
	//}
	//if (GetAsyncKeyState(0x34) & 0x0001)
	//{
	//	fprintf(sinc, "%f\n", m_fSongAcculTime);
	//}
	//if (GetAsyncKeyState(0x45) & 0x0001)
	//{
	//	fprintf(sinc, "%f\n", m_fSongAcculTime);
	//}
}

void CSystem::MouseHandler(MOUSESTATE mouseState) 
{
	if (m_pInputManager->GetPressState(MOUSE_BUTTON::LEFT) == MousePressState::Down)
	{
		switch (SceneNumber)
		{
			case 0:
				MouseDown(Close_Btn, mouseState.x, mouseState.y);
				break;
			case 1:
				MouseDown(Change_nextScene, mouseState.x, mouseState.y);
				MouseDown(Help_Btn, mouseState.x, mouseState.y);
				MouseDown(Credit_Btn, mouseState.x, mouseState.y);
				MouseDown(Exit_Btn, mouseState.x, mouseState.y);
				break;
			case 2:
				MouseDown(Change_prvScene, mouseState.x, mouseState.y);
				MouseDown(PlaySongBtn, mouseState.x, mouseState.y);
				MouseDown(StopSongBtn, mouseState.x, mouseState.y);
				MouseDown(PlayAniBtn, mouseState.x, mouseState.y);
				MouseDown(StopAniBtn, mouseState.x, mouseState.y);

				MouseDown(Song1, mouseState.x, mouseState.y);
				MouseDown(Song2, mouseState.x, mouseState.y);
				MouseDown(Song3, mouseState.x, mouseState.y);
				MouseDown(Song4, mouseState.x, mouseState.y);
				MouseDown(Song5, mouseState.x, mouseState.y);
				break;
		}
		//printf("���콺 �ٿ� �߻�: ");
		//printf("%d %d\n", mouseState.BTN[MOUSE_BUTTON::LEFT], mouseState.BTN[MOUSE_BUTTON::LEFT]);
	}
	else if (m_pInputManager->GetPressState(MOUSE_BUTTON::LEFT) == MousePressState::Up)
	{
		switch (SceneNumber)
		{
			case 0:
				MouseUp(Close_Btn, mouseState.x, mouseState.y);
				break;
			case 1:
				MouseUp(Change_nextScene, mouseState.x, mouseState.y);
				MouseUp(Help_Btn, mouseState.x, mouseState.y);
				MouseUp(Credit_Btn, mouseState.x, mouseState.y);
				MouseUp(Exit_Btn, mouseState.x, mouseState.y);
				break;
			case 2:
				MouseUp(Change_prvScene, mouseState.x, mouseState.y); //�� ���������� ���� �߻�
				if (isMusicPlay) MouseUp(StopSongBtn, mouseState.x, mouseState.y);
				else MouseUp(PlaySongBtn, mouseState.x, mouseState.y);

				if (isAniPlay) MouseUp(StopAniBtn, mouseState.x, mouseState.y);
				else MouseUp(PlayAniBtn, mouseState.x, mouseState.y);

				MouseUp(Song1, mouseState.x, mouseState.y); 
				MouseUp(Song2, mouseState.x, mouseState.y);
				MouseUp(Song3, mouseState.x, mouseState.y);
				MouseUp(Song4, mouseState.x, mouseState.y);
				MouseUp(Song5, mouseState.x, mouseState.y);
				break;
		}
		//printf("���콺 �� �߻�: ");
		//printf("%d %d\n", mouseState.prv_BTN[MOUSE_BUTTON::LEFT], mouseState.BTN[MOUSE_BUTTON::LEFT]);
	}

	else if (m_pInputManager->GetPressState(MOUSE_BUTTON::LEFT) == MousePressState::Hold)
	{
		//printf("���콺 Ȧ����: ");
		//printf("%d %d\n", mouseState.prv_BTN[MOUSE_BUTTON::LEFT], mouseState.BTN[MOUSE_BUTTON::LEFT]);
	}

	else if (m_pInputManager->GetPressState(MOUSE_BUTTON::LEFT) == MousePressState::Unhold)
	{
		DrawCursor(CursorSurface, mouseState.x, mouseState.y); //���콺 Ŀ��
		switch (SceneNumber)
		{
		case 0:
			MouseHold(Close_Btn, mouseState.x, mouseState.y);
			break;
		case 1:
			MouseHold(Change_nextScene, mouseState.x, mouseState.y);
			MouseHold(Help_Btn, mouseState.x, mouseState.y);
			MouseHold(Credit_Btn, mouseState.x, mouseState.y);
			MouseHold(Exit_Btn, mouseState.x, mouseState.y);
			break;
		case 2:
			MouseHold(Change_prvScene, mouseState.x, mouseState.y);
			MouseHold(PlaySongBtn, mouseState.x, mouseState.y);
			MouseHold(StopSongBtn, mouseState.x, mouseState.y);

			MouseHold(Song1, mouseState.x, mouseState.y);
			MouseHold(Song2, mouseState.x, mouseState.y);
			MouseHold(Song3, mouseState.x, mouseState.y);
			MouseHold(Song4, mouseState.x, mouseState.y);
			MouseHold(Song5, mouseState.x, mouseState.y);
			break;
		}
		//printf("���콺 ��Ȧ����: ");
		//printf("%d %d\n", mouseState.prv_BTN[MOUSE_BUTTON::LEFT], mouseState.BTN[MOUSE_BUTTON::LEFT]);
	}
	if (m_pInputManager->GetPressState(MOUSE_BUTTON::MIDDLE) == MousePressState::Down)
	{
		if (!turn) mciSendString(L"pause ..\\Song\\Song0.mp3", NULL, 0, NULL); //��ǥ�� �� �ò������ ��� ����
		else mciSendString(L"play ..\\Song\\Song0.mp3", NULL, 0, NULL);
		turn = !turn;
		system("cls");
	}
	//�� �Ʒ��δ� ������ ���İ��� �κ�
}
