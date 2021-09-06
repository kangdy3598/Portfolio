#pragma once

class Skill_Ultimate;
class Skill_Swift;

class Skill : public PlayerClass
{
public:
	Skill();
	Skill(const Skill&);
	~Skill();

public:
	bool Initialize(ID3D11Device*);
	void InitAnimation();
	void DeleteAnimation();
	void Frame(float tickTime);
	void Shutdown();

	static Skill* Instance();

public:
	// 0 : 캐릭터 전방
	// 1 : 캐릭터 후방
	int m_layerOrder = 0; 

	Skill_Swift* m_skill_Swift;
	Skill_Ultimate* m_skill_Ultimate;
	Skill_Ultimate* m_skill_Ultimate_hit[15];

	XMFLOAT2 m_attackBox[2] = { XMFLOAT2(0, 0) };
	//test ★
	const TCHAR* m_name;
};