#pragma once

enum MOUSE_BUTTON {LEFT, RIGHT, MIDDLE};
enum MousePressState { Hold, Down, Up, Unhold };
typedef struct MOUSESTATE //마우스 입력에 대한 구조체
{
	int x;
	int y;
	BYTE BTN[4] = {0, }; //BYTE = unsigned char //여유를 두기 위해 4칸 줬음
	BYTE prv_BTN[4] = {0, };
}MOUSESTATE;

class IInputHandler
{
public:
	IInputHandler()
	{
	}

	virtual ~IInputHandler()
	{
	}

public:
	virtual void KeyboardHandler(void) = 0; //나중에 설명해준다고 함
	virtual void MouseHandler(MOUSESTATE mouseState) = 0;
};


