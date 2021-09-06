#pragma once
#include <list>

using namespace std;
class ObjectPoolClass;
class PoolListClass : public ObjectClass
{
public:
	PoolListClass();
	PoolListClass(const PoolListClass&);
	~PoolListClass();

	void PrintPoolList();
	static PoolListClass* Instance();

public:
	list<ObjectPoolClass*> m_PoolList;
};