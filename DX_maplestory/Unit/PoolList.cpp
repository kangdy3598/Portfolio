#include "../../Header/stdafx.h"
//#include "ObjectPool.h"
#include "PoolList.h"

PoolListClass::PoolListClass()
{
}
PoolListClass::PoolListClass(const PoolListClass&)
{
}
PoolListClass::~PoolListClass()
{
}

void PoolListClass::PrintPoolList()
{
	if (m_PoolList.empty())
	{ 
		MessageBox(0, L"리스트가 없습니다.", L"리스트 출력", MB_OK);
		return;
	}
	//char text[30]; wchar_t text1[300]; char dest[300] ="";
	//list<ObjectPoolClass*>::iterator iter;
	//for (iter = m_PoolList.begin(); iter != m_PoolList.end(); iter++)
	//{
	//	sprintf(text, "Name : %s / Size : %d\n", (*iter)->m_name.c_str(), (*iter)->m_size);
	//	strcat(dest, text);
	//	mbstowcs(text1, dest, strlen(dest) + 1);
	//}
	//MessageBox(0, text1, 0, 0);
}

PoolListClass* PoolListClass::Instance()
{
	static PoolListClass* instance = new PoolListClass();
	return instance;
}
