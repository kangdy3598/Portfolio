#pragma once

class DamageClass : public ObjectClass
{
public:
	DamageClass();
	DamageClass(const DamageClass&);
	~DamageClass();

	bool Initialize(ID3D11Device*, int type);
	void Frame(float tickTime);

	static DamageClass* Instance();

public:
	XMFLOAT2 m_startPos = XMFLOAT2(0, 0);
	int m_amount = 0;
	float m_fadePercentage = 1.0f;
	float m_tickTime = 0.0f;
};