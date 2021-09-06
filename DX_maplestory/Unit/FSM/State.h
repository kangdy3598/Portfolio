
//template <typename T>
//__interface IState
//{
//	void Enter(T*);
//	void Execute(T*);
//	void Exit(T*);
//};
class ObjectClass;
class State
{
public:

	ObjectClass* ob = nullptr;

	virtual ~State() {}

	virtual void Enter() = 0;

	virtual void Execute() = 0;

	virtual void Exit() = 0;

};
