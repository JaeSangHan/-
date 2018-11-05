#include "stdafx.h"

int main(int argc, char* argv[])
{
	CSystem* pSystem = new CSystem; //memory 할당 //객체 생성

	pSystem->Initialize(); //system 초기화

	pSystem->Run(); //pSystem 실행 //업데이트

	pSystem->Terminate(); //pSystem 종료

	delete pSystem; //객체 삭제 //memory 정리

	return 0;
}