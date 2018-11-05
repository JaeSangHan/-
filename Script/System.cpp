#include "stdafx.h"

#define IMG_DIR		"..\\Image\\Button\\"

bool turn = true; //기본 bg 발표할때 임시로 끄고 켜기 위해서 만듦

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

SDL_Surface* BackGroundSurface; //배경화면 레스터
SDL_Texture* BackGroundTexture; //배경화면 텍스쳐
SDL_Surface* CursorSurface; //커서 레스터
SDL_Texture* CursorTexture; //커서 텍스쳐

SDL_Rect rtTemp; //배경화면
SDL_Rect rtOutAni; //커서

char strTemp[3][256] = { IMG_DIR, IMG_DIR }; //이미지 위치

CSystem::CSystem(void) //뭔진 모르겠지만 없으면 안되는 듯1 //메인에서 제일먼저 호출
{ 
	
}

CSystem::~CSystem(void) //뭔진 모르겠지만 없으면 안되는 듯2
{
	//SDL_Quit();
}

void CSystem::DrawCursor(SDL_Surface * img, int x, int y) //커서 그리기
{
	SDL_Rect dest;
	SDL_Rect rtOutAni = { x, y, 100, 100 };
	dest.x = x;
	dest.y = y;
	SDL_RenderCopy(m_pRender, CursorTexture, NULL, &rtOutAni); //배경화면 띄우기
}

void CSystem::PreviousScene()
{
	StopMusic();
	mciSendString(L"play ..\\Song\\Song0.mp3", NULL, 0, NULL); //시작하자마자 기본 bgm틀기
	SceneNumber = 1;
	BackGroundSurface = SDL_LoadBMP("..\\Image\\BackGround\\Title_bg.bmp");
	BackGroundTexture = SDL_CreateTextureFromSurface(m_pRender, BackGroundSurface);
}

void CSystem::NextScene()
{
	SceneNumber = 2;
	BackGroundSurface = SDL_LoadBMP("..\\Image\\BackGround\\Ingame_bg.bmp");
	BackGroundTexture = SDL_CreateTextureFromSurface(m_pRender, BackGroundSurface);
	mciSendString(L"stop ..\\Song\\Song0.mp3", NULL, 0, NULL); //기본 bgm 멈추기
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
	SetVisible(StopSongBtn, true); //스톱버튼 보이게 하기
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

	SetCoord(ch1, SongNumber); //애니메이션 포지션 재배치
	SetCoord(ch2, SongNumber);
	SetCoord(ch3, SongNumber);
	SetCoord(ch4, SongNumber);
	SetCoord(ch5, SongNumber);
}

void CSystem::PauseMusic() //TODO: 일시 정지 후, 다른 곡을 선택해 재생하면 중첩되는 버그가 있음
{
	isMusicPlay = false; 
	SetVisible(PlaySongBtn, true); //플레이 버튼 보이게 하기
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

void CSystem::StopMusic() //모든 음악 정지
{
	ClickUp(StopSongBtn);
	m_fSongAcculTime = 0; //음악 누적시간 초기화
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
	SetVisible(StopAniBtn, true); //스톱버튼 보이게 하기
	SetVisible(PlayAniBtn, false);
}

void CSystem::StopAni()
{
	isAniPlay = false;
	SetVisible(PlayAniBtn, true); //스톱버튼 보이게 하기
	SetVisible(StopAniBtn, false);
}

void CSystem::SetSong1() {	StopMusic(); SongNumber = 0;}
void CSystem::SetSong2() {	StopMusic(); SongNumber = 1;}
void CSystem::SetSong3() {	StopMusic(); SongNumber = 2;}
void CSystem::SetSong4() {	StopMusic(); SongNumber = 3;}
void CSystem::SetSong5() {	StopMusic(); SongNumber = 4;}

void CSystem::PlayingSongList() //실행중인 송리스트의 이미지 불러오기
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
	SDL_SetColorKey(SurfaceimgTemp, SDL_TRUE, colorkey); //색깔 키 값 설정
	TextureimgTemp = SDL_CreateTextureFromSurface(m_pRender, SurfaceimgTemp);
	switch (SongNumber) //텍스쳐를 입히고 플레이중인 버튼의 형식을 true로 바꾼다
	{
	case 0: { Song1->imgCurrent = TextureimgTemp;	Song1->isPlayingSong = true;  break;}
	case 1: { Song2->imgCurrent = TextureimgTemp;	Song2->isPlayingSong = true;  break;}
	case 2: { Song3->imgCurrent = TextureimgTemp;	Song3->isPlayingSong = true;  break;}
	case 3: { Song4->imgCurrent = TextureimgTemp;	Song4->isPlayingSong = true;  break;}
	case 4: { Song5->imgCurrent = TextureimgTemp;	Song5->isPlayingSong = true;  break;}
	}
	SDL_FreeSurface(SurfaceimgTemp);
}

void CSystem::PauseSongList() //보통 멈춘 상태의 송리스트 불러오기
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

bool CSystem::Initialize()  //메인에서 불러오는 것으로 추측되는 부분
{
	CBaseWindow::Initialize(); //창 띄우기 기본설정
	CTimeManager::Initialize(); //srand 등등 시간 관련 기본설정인듯
	
	m_pGameFrame = new CFrameSkip; //프레임 제한
	m_pGameFrame->SetFramePerSec(60); //60fps

	m_pInputManager = new CInputManager;
	m_pInputManager->SetInputHandler(this); 

	////이 아래로 오브젝트 초기화 코드를 넣자////
	sinc = fopen("SINC.txt", "w"); //싱크 조절용 메모장

	SDL_ShowCursor(0); //기본 커서 숨기기
	CursorSurface = SDL_LoadBMP("mycursor.bmp"); //마우스 커서
	Uint32 colorkey = SDL_MapRGB(CursorSurface->format, 255, 0, 255);
	SDL_SetColorKey(CursorSurface, SDL_TRUE, colorkey); //색깔 키 값 설정
	CursorTexture = SDL_CreateTextureFromSurface(m_pRender, CursorSurface);

	ch1 = InitCharacter(m_pRender, "..\\Animation\\ch1.bmp", 300, 100, 7, 0); //건반
	ch2 = InitCharacter(m_pRender, "..\\Animation\\ch2.bmp", 50, 180, 6, 1); //플룻
	ch3 = InitCharacter(m_pRender, "..\\Animation\\ch3.bmp", 570, 150, 5, 2); //기타솔로
	ch4 = InitCharacter(m_pRender, "..\\Animation\\ch4.bmp", 130, 250, 5, 3); //기타보컬
	ch5 = InitCharacter(m_pRender, "..\\Animation\\ch5.bmp", 400, 230, 5, 4); //여자보컬

	strcpy_s(strTemp[0], IMG_DIR);				strcpy_s(strTemp[1], IMG_DIR);					strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "StartBtn_Up.bmp");	strcat_s(strTemp[1], "StartBtn_Down.bmp");		strcat_s(strTemp[2], "StartBtn_Hold.bmp");
	Change_nextScene = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 200, 550, [&]() { NextScene(); });
	//ㄴ 스타트 버튼

	strcpy_s(strTemp[0], IMG_DIR);			 strcpy_s(strTemp[1], IMG_DIR);					    strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "HelpBtn_Up.bmp");	 strcat_s(strTemp[1], "HelpBtn_Down.bmp");		    strcat_s(strTemp[2], "HelpBtn_Hold.bmp");
	Help_Btn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 400, 550, [&]() { HelpPannel(); });
	//ㄴ 도움말 버튼

	strcpy_s(strTemp[0], IMG_DIR);				strcpy_s(strTemp[1], IMG_DIR);                  strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "CreditBtn_Up.bmp");	strcat_s(strTemp[1], "CreditBtn_Down.bmp");		strcat_s(strTemp[2], "CreditBtn_Hold.bmp");
	Credit_Btn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 600, 550, [&]() { CreditPannel(); });
	//ㄴ 크레딧 버튼

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "ExitBtn_Up.bmp");			strcat_s(strTemp[1], "ExitBtn_Down.bmp");	strcat_s(strTemp[2], "ExitBtn_Hold.bmp");
	Exit_Btn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 800, 550, [&]() { ExitBtn(); });
	//ㄴ 종료 버튼

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "BackBtn_Up.bmp");			strcat_s(strTemp[1], "BackBtn_Down.bmp");	strcat_s(strTemp[2], "BackBtn_Hold.bmp");
	Close_Btn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1100, 0, [&]() { PreviousScene(); });
	//ㄴ '닫기' 버튼
	 
	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "HomeBtn_Up.bmp");			strcat_s(strTemp[1], "HomeBtn_Down.bmp");   strcat_s(strTemp[2], "HomeBtn_Hold.bmp");
	Change_prvScene = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 0, 0, [&]() { PreviousScene(); });
	//ㄴ 홈 버튼

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "PlayMusicBtn.bmp");		strcat_s(strTemp[1], "PlayMusicBtn.bmp");	strcat_s(strTemp[2], "PlayMusicBtn.bmp");
	PlaySongBtn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1115, 75, [&]() { PlayMusic(); });
	//ㄴ 노래 재생 버튼

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "StopMusicBtn.bmp");		strcat_s(strTemp[1], "StopMusicBtn.bmp");   strcat_s(strTemp[2], "StopMusicBtn.bmp");
	StopSongBtn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1115, 75, [&]() { PauseMusic(); });
	SetVisible(StopSongBtn, false);
	//ㄴ 노래 정지 버튼 


	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "PlayAniBtn.bmp");		strcat_s(strTemp[1], "PlayAniBtn.bmp");   strcat_s(strTemp[2], "PlayAniBtn.bmp");
	PlayAniBtn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2],1180, 0, [&]() { PlayAni(); });
	//ㄴ 애니 재생 버튼 

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "StopAniBtn.bmp");		strcat_s(strTemp[1], "StopAniBtn.bmp");   strcat_s(strTemp[2], "StopAniBtn.bmp");
	StopAniBtn = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1180, 0, [&]() { StopAni(); });
	SetVisible(StopSongBtn, false);
	//ㄴ 애니 정지 버튼 

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "01_Song1_01.bmp");		strcat_s(strTemp[1], "01_Song1_03.bmp");    strcat_s(strTemp[2], "01_Song1_02.bmp");
	Song1 = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1000, 120, [&]() { SetSong1(); });
	//ㄴ 벚꽃엔딩 
																							   
	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "02_Song2_01.bmp");		strcat_s(strTemp[1], "02_Song2_03.bmp");    strcat_s(strTemp[2], "02_Song2_02.bmp");
	Song2 = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1000, 250, [&]() { SetSong2(); });
	//ㄴ 봄이좋냐 
																							    
	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "03_Song3_01.bmp");		strcat_s(strTemp[1], "03_Song3_03.bmp");    strcat_s(strTemp[2], "03_Song3_02.bmp");
	Song3 = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1000, 330, [&]() { SetSong3(); });
	//ㄴ 우연히 봄

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "04_Song4_01.bmp");	strcat_s(strTemp[1], "04_Song4_03.bmp");	    strcat_s(strTemp[2], "04_Song4_02.bmp");
	Song4 = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1000, 410, [&]() { SetSong4(); });
	//ㄴ 우주를줄게

	strcpy_s(strTemp[0], IMG_DIR);					strcpy_s(strTemp[1], IMG_DIR);              strcpy_s(strTemp[2], IMG_DIR);
	strcat_s(strTemp[0], "05_Song5_01.bmp");	strcat_s(strTemp[1], "05_Song5_03.bmp");	    strcat_s(strTemp[2], "05_Song5_02.bmp");
	Song5 = InitButton(m_pRender, strTemp[0], strTemp[1], strTemp[2], 1000, 490, [&]() { SetSong5(); });
	//ㄴ 썸탈거야

	/////이 위로 오브젝트 초기화 코드를 넣자/////
	PreviousScene(); //처음은 1번 씬으로 시작
	return true;
}

void CSystem::Pulse()  //밀다 //업데이트
{
	CTimeManager::Pulse(isMusicPlay);

	//m_pGameFrame = new CFrameSkip; //프레임 제한
	//m_pGameFrame->SetFramePerSec(60); //60fps

	float fTimeStep = CTimeManager::GetTimeStep();

	if (m_pGameFrame->Update(fTimeStep))
	{
		//====================================
		//여기에 오브젝트 프로세스 코드를 넣으세요. //update
		SDL_RenderCopy(m_pRender, BackGroundTexture, NULL, NULL); //배경화면 띄우기
		//printf("%.1f초 노래번호 %d\n", m_fSongAcculTime, SongNumber);

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
				if (isMusicPlay) //음악이 재생중일때
				{
					SetDelay(SongNumber); //딜레이 박아주기
					if (Aninod1(SongNumber)) Draw(ch1, SongNumber); //타이밍 재서 실행
					else if (isAniPlay) PauseDraw(ch1, SongNumber); //if (delay가 잔류) Draw(ch1, Songnum) 추가하기'

					if (Aninod2(SongNumber)) Draw(ch2, SongNumber); //타이밍 재서 실행
					else if (isAniPlay) PauseDraw(ch2, SongNumber);

					if (Aninod3(SongNumber)) Draw(ch3, SongNumber); //타이밍 재서 실행
					else if (isAniPlay) PauseDraw(ch3, SongNumber);

					if (Aninod4(SongNumber)) Draw(ch4, SongNumber); //타이밍 재서 실행
					else if (isAniPlay) PauseDraw(ch4, SongNumber);

					if (Aninod5(SongNumber)) Draw(ch5, SongNumber); //타이밍 재서 실행
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
	//이 아래로 오브젝트 종료/해제 코드를 넣으세요.
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

	fclose(sinc); //싱크 기록용 메모장

	//이 위로 오브젝트 종료/해제 코드를 넣으세요.
	m_pInputManager->Terminate();
	CBaseWindow::Terminate(); //디스트로이 렌더 //디스트로이 스크린
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
		fprintf(sinc, "시작시간 : %.2f\n", m_fSongAcculTime);
	}
	if (GetAsyncKeyState(0x51) & 0x0001) //Q
	{
		fprintf(sinc, "끝난시간 : %.2f\n", m_fSongAcculTime);
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
		//printf("마우스 다운 발생: ");
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
				MouseUp(Change_prvScene, mouseState.x, mouseState.y); //이 순서때문에 문제 발생
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
		//printf("마우스 업 발생: ");
		//printf("%d %d\n", mouseState.prv_BTN[MOUSE_BUTTON::LEFT], mouseState.BTN[MOUSE_BUTTON::LEFT]);
	}

	else if (m_pInputManager->GetPressState(MOUSE_BUTTON::LEFT) == MousePressState::Hold)
	{
		//printf("마우스 홀드중: ");
		//printf("%d %d\n", mouseState.prv_BTN[MOUSE_BUTTON::LEFT], mouseState.BTN[MOUSE_BUTTON::LEFT]);
	}

	else if (m_pInputManager->GetPressState(MOUSE_BUTTON::LEFT) == MousePressState::Unhold)
	{
		DrawCursor(CursorSurface, mouseState.x, mouseState.y); //마우스 커서
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
		//printf("마우스 언홀드중: ");
		//printf("%d %d\n", mouseState.prv_BTN[MOUSE_BUTTON::LEFT], mouseState.BTN[MOUSE_BUTTON::LEFT]);
	}
	if (m_pInputManager->GetPressState(MOUSE_BUTTON::MIDDLE) == MousePressState::Down)
	{
		if (!turn) mciSendString(L"pause ..\\Song\\Song0.mp3", NULL, 0, NULL); //발표할 때 시끄러우면 잠시 정지
		else mciSendString(L"play ..\\Song\\Song0.mp3", NULL, 0, NULL);
		turn = !turn;
		system("cls");
	}
	//요 아래로는 메인이 거쳐가는 부분
}
