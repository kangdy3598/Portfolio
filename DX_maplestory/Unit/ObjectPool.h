#pragma once
#include <list>

using namespace std;
class PoolListClass;
class ObjectPoolClass : public ObjectClass
{
public:
	ObjectPoolClass();
	ObjectPoolClass(const ObjectPoolClass&);
	~ObjectPoolClass();

	ObjectClass* PopFromPool();
	void PushToPool(ObjectClass* ob, string name = NULL);
	void SetObjectPool(ObjectClass* ob, string name = NULL, int size = 1);

	static ObjectPoolClass* Instance();

public:
	list<ObjectClass*> m_objectPool;
	ObjectClass* m_ob = nullptr;

	string m_name = "";
	int m_size = 0;
};