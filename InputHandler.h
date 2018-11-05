#pragma once

enum MOUSE_BUTTON {LEFT, RIGHT, MIDDLE};
enum MousePressState { Hold, Down, Up, Unhold };
typedef struct MOUSESTATE //���콺 �Է¿� ���� ����ü
{
	int x;
	int y;
	BYTE BTN[4] = {0, }; //BYTE = unsigned char //������ �α� ���� 4ĭ ����
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
	virtual void KeyboardHandler(void) = 0; //���߿� �������شٰ� ��
	virtual void MouseHandler(MOUSESTATE mouseState) = 0;
};


