#include "../../Header/stdafx.h"
//#include "../../Graphics/TextureClass.h"
#include "EnemyHP.h"

EnemyHPClass::EnemyHPClass()
{
	for (int i = 0; i < sizeof(m_UIPos) / sizeof(XMFLOAT2*); i++)
	{
		m_UIPos[i] = XMFLOAT2(0, 0);
	}	
}
EnemyHPClass::EnemyHPClass(const EnemyHPClass& other)
{
	for (int i = 0; i < sizeof(m_UIPos) / sizeof(XMFLOAT2*); i++)
	{
		m_UIPos[i] = XMFLOAT2(0, 0);
	}
}
EnemyHPClass::~EnemyHPClass()
{
}

bool EnemyHPClass::Initialize(ID3D11Device* device)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}
	m_device = device;
	

	sprite = new Sprite[6];

	nowSprite = LoadTexture(device, L"../Graphics/data/UI/EnemyHPUI.dds");
	nowSprite.m_fullSizeX = nowSprite.m_fullSizeY = 256;

	sprite[0] = sprite[1] = sprite[2] = sprite[3] = sprite[4] = sprite[5] = nowSprite;

	sprite[0].m_startBitmapX = 0; sprite[0].m_startBitmapY = 0;
	sprite[1].m_startBitmapX = 40; sprite[1].m_startBitmapY = 0;
	sprite[2].m_startBitmapX = 70; sprite[2].m_startBitmapY = 0;
	sprite[3].m_startBitmapX = 80; sprite[2].m_startBitmapY = 0;
	sprite[4].m_startBitmapX = 90; sprite[2].m_startBitmapY = 0;
	sprite[5].m_startBitmapX = 101; sprite[2].m_startBitmapY = 0;

	sprite[0].m_bitmapWidth = 37; sprite[0].m_bitmapHeight = 37;
	sprite[1].m_bitmapWidth = 25; sprite[1].m_bitmapHeight = 25;
	sprite[2].m_bitmapWidth = 3; sprite[2].m_bitmapHeight = 20;
	sprite[3].m_bitmapWidth = 1; sprite[3].m_bitmapHeight = 20;
	sprite[4].m_bitmapWidth = 5; sprite[4].m_bitmapHeight = 20;
	sprite[5].m_bitmapWidth = 1; sprite[5].m_bitmapHeight = 10;

	m_UIPos[0].x = -650; m_UIPos[0].y = 330;
	m_UIPos[1].x = m_UIPos[0].x + 5; m_UIPos[1].y = m_UIPos[0].y + 5;
	m_UIPos[2].x = m_UIPos[0].x + 36; m_UIPos[2].y = m_UIPos[0].y + 17;
	m_UIPos[3].x = m_UIPos[0].x + 38; m_UIPos[3].y = m_UIPos[0].y + 17;
	m_UIPos[4].x = m_UIPos[0].x + 1318; m_UIPos[4].y = m_UIPos[0].y + 17;
	m_UIPos[5].x = m_UIPos[0].x + 38; m_UIPos[5].y = m_UIPos[0].y + 22;

	return true;
}