#pragma once //������� �� ���� �ҷ�����.

class CSystem : public CBaseWindow,
	public CTimeManager,
	public IInputHandler
{
public:
	int SceneNumber; //�� ��ȣ
	int SongNumber = 0; //�÷��� �ǰ� �ִ� �뷡�� ��ȣ
	bool isMusicPlay = false; //���� �÷������ΰ�?
	bool isAniPlay = false; //�ִϸ��̼� ���� �÷��� ���ΰ�?

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

public: //Animation���� �뷡 �ð� �޾ƿ��� ���� ���
	bool Nod(float start_Time, float end_Time); //������ ��ũ�� �Լ�?
	bool CheckAniDelay(CHARACTER* obj);
	void SetDelay(int songnum);
	
	bool Aninod1(int _songnum);
	bool Aninod2(int _songnum);
	bool Aninod3(int _songnum);
	bool Aninod4(int _songnum);
	bool Aninod5(int _songnum);
};
