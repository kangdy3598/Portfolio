#pragma once

//class TextureClass;
class Skill_Swift : public Skill
{
public:
	Skill_Swift();
	Skill_Swift(const Skill_Swift&);
	~Skill_Swift();

	bool Initialize(ID3D11Device*, int order);
	void Frame(Skill* s, PlayerClass* p, float tickTime, int layerOrder);
	void Flip(Skill* s, PlayerClass*);

	static Skill_Swift* Instance();

public:
	float m_tickTime = 0;

private:

};