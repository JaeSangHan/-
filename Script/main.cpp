#include "stdafx.h"

int main(int argc, char* argv[])
{
	CSystem* pSystem = new CSystem; //memory �Ҵ� //��ü ����

	pSystem->Initialize(); //system �ʱ�ȭ

	pSystem->Run(); //pSystem ���� //������Ʈ

	pSystem->Terminate(); //pSystem ����

	delete pSystem; //��ü ���� //memory ����

	return 0;
}