#include "../Header/stdafx.h"
#include "Damage.h"

DamageClass::DamageClass()
{
}
DamageClass::DamageClass(const DamageClass& other)
{
}
DamageClass::~DamageClass()
{
}

DamageClass* DamageClass::Instance()
{
	static DamageClass* instance = new DamageClass();
	return instance;

}
bool DamageClass::Initialize(ID3D11Device* device, int type)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}
	m_device = device;

	m_startPos = XMFLOAT2(0, 0);
	m_amount = 0;
	m_fadePercentage = 1.0f;
	m_tickTime = 0.0f;

	if(type == 0) nowSprite = LoadTexture(device, L"../Graphics/data/Hit.dds", 32, 34, 256, 256, 5, 10, 0);
	else nowSprite = LoadTexture(device, L"../Graphics/data/Attack.dds", 32, 34, 256, 256, 5, 10, 0);
	
	m_Flip = false;
	return true;
}

void DamageClass::Frame(float tickTime)
{
	m_tickTime += tickTime;
	if (m_tickTime >= 20)
	{
		m_tickTime = 0;
		m_fadePercentage -= 0.01f;
		m_Pos.y += 0.5f;
	}
	if (m_fadePercentage < 0.3f)
	{
		m_Pos.y = 0.0f;
		m_fadePercentage = 1.0f;
		nowSprite.m_isRender = false;
	}
}