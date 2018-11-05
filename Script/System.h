#pragma once //헤더파일 한 번만 불러오게.

class CSystem : public CBaseWindow,
	public CTimeManager,
	public IInputHandler
{
public:
	int SceneNumber; //씬 번호
	int SongNumber = 0; //플레이 되고 있는 노래의 번호
	bool isMusicPlay = false; //지금 플레이중인가?
	bool isAniPlay = false; //애니메이션 지금 플레이 중인가?

private:
	CFrameSkip* m_pGameFrame;
	CInputManager*	m_pInputManager;

public:

public:
	CSystem(void);
	~CSystem(void);



private:
	void Pulse();
public:
	void DrawCursor(SDL_Surface * img, int x, int y);

	void NextScene();
	void PreviousScene();
	void HelpPannel();
	void CreditPannel();
	void PlayMusic();
	void PauseMusic();
	void StopMusic();

	void PlayAni();
	void StopAni();

	void ExitBtn();

	void SetSong1();
	void SetSong2();
	void SetSong3();
	void SetSong4();
	void SetSong5();

	void PlayingSongList();
	void PauseSongList();

	bool Initialize();
	void Terminate();
	void Run();

public:
	void KeyboardHandler();
	void MouseHandler(MOUSESTATE mouseState);

public: //Animation에서 노래 시간 받아오기 위해 사용
	bool Nod(float start_Time, float end_Time); //일종의 매크로 함수?
	bool CheckAniDelay(CHARACTER* obj);
	void SetDelay(int songnum);
	
	bool Aninod1(int _songnum);
	bool Aninod2(int _songnum);
	bool Aninod3(int _songnum);
	bool Aninod4(int _songnum);
	bool Aninod5(int _songnum);
};
