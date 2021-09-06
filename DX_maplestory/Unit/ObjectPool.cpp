#include "../../Header/stdafx.h"
#include "PoolList.h"
//#include "ObjectPool.h"

#include <typeinfo>

ObjectPoolClass::ObjectPoolClass()
{
}
ObjectPoolClass::ObjectPoolClass(const ObjectPoolClass&)
{
}
ObjectPoolClass::~ObjectPoolClass()
{
}

ObjectClass* ObjectPoolClass::PopFromPool()
{
	if (PoolListClass::Instance()->m_PoolList.empty())
	{
		MessageBox(0, L"오브젝트 풀 부족", L"OK", MB_OK);
		return nullptr;
	}

	list<ObjectPoolClass*>::iterator iter;
	for (iter = PoolListClass::Instance()->m_PoolList.begin(); iter != PoolListClass::Instance()->m_PoolList.end(); iter++)
	{
		if (!(*iter)->m_objectPool.empty())
		{
			ObjectClass* ob = (*iter)->m_objectPool.front();
			(*iter)->m_objectPool.pop_front();

			return ob;
		}
	}
}

void ObjectPoolClass::PushToPool(ObjectClass* ob, string name)
{
	ob->m_animationX = ob->m_animationY = ob->m_animationFrameCount = 1;
	ob->m_isAnimationEnd = false;
	ob->nowSprite.m_isRender = false;

	list<ObjectPoolClass*>::iterator iter;
	for (iter = PoolListClass::Instance()->m_PoolList.begin(); iter != PoolListClass::Instance()->m_PoolList.end(); iter++)
	{
		if (
			(*iter)->m_name == typeid(ob).name() || (*iter)->m_name == name
			)
		{
			(*iter)->m_objectPool.push_back(ob);
			break;
		}
	}
	
	//PoolListClass::Instance()->m_PoolList.front()->m_objectPool.push_back(ob);
}

void ObjectPoolClass::SetObjectPool(ObjectClass* ob, string name, int size)
{
	m_size = size;
	if (name.empty()) m_name = typeid(ob).name();
	else m_name = name;

	m_objectPool.push_back(ob);
	PoolListClass::Instance()->m_PoolList.push_back(this);
}

ObjectPoolClass* ObjectPoolClass::Instance()
{
	static ObjectPoolClass* instance = new ObjectPoolClass();
	return instance;
}
