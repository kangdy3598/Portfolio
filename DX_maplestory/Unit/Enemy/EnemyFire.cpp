#include "../../Header/stdafx.h"
//#include "../../Class/SoundManager.h"
#include "EnemyFire.h"

EnemyFireClass::EnemyFireClass()
{
}
EnemyFireClass::EnemyFireClass(const EnemyFireClass& other)
{
}
EnemyFireClass::~EnemyFireClass()
{
}

EnemyFireClass* EnemyFireClass::Instance()
{
	static EnemyFireClass* instance = new EnemyFireClass();
	return instance;
}

bool EnemyFireClass::Initialize(ID3D11Device* device)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}
	m_device = device;
	
	sprite = new Sprite[2];
	sprite[0] = LoadTexture(device, L"../Graphics/data/Enemy/attack6_2_fire.dds", 341, 810, 2048, 2048, 2, 6, 100);
	sprite[1] = LoadTexture(device, L"../Graphics/data/Enemy/attack6_3_fire.dds", 341, 679, 2048, 2048, 2, 6, 100);

	nowSprite = sprite[0];

	m_bAttackAble = false;

	nowSprite.m_isRender = false;

	m_Pos.y = 300;

	return true;
}