#pragma once

class KeyConfigUIClass : public UIClass
{
public:
	KeyConfigUIClass();
	KeyConfigUIClass(const KeyConfigUIClass&);
	~KeyConfigUIClass();

	struct KeyPosition
	{
		XMFLOAT2 pos;
		__int16 Key;
	};
	KeyPosition* m_keyPosition;

	bool Initialize(ID3D11Device*);
	void Frame(POINT pos);

	bool boxCheck(POINT pos, int);
	void set(POINT pos , int);

	static KeyConfigUIClass* Instance();
	
	int m_remainCount = 0;
	int m_isClick = -1;
	XMFLOAT2 m_UIPos[6] = { XMFLOAT2(0, 0) };
};