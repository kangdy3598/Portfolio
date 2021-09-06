#include "../../Header/stdafx.h"
//#include "../../Graphics/TextureClass.h"
#include "PlayerHP.h"

PlayerHPClass::PlayerHPClass()
{
	memset(m_UIPos, 0, sizeof(m_UIPos));
}
PlayerHPClass::PlayerHPClass(const PlayerHPClass& other)
{
	memset(m_UIPos, 0, sizeof(m_UIPos));
}
PlayerHPClass::~PlayerHPClass()
{
}

bool PlayerHPClass::Initialize(ID3D11Device* device)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}
	m_device = device;

	sprite = new Sprite[4];

	nowSprite = LoadTexture(device, L"../Graphics/data/UI/PlayerHPUI.dds");
	nowSprite.m_fullSizeX = nowSprite.m_fullSizeY = 256;

	sprite[0] = sprite[1] = sprite[2] = sprite[3] = nowSprite;

	sprite[0].m_startBitmapX = 0; sprite[0].m_startBitmapY = 10;
	sprite[1].m_startBitmapX = 0; sprite[1].m_startBitmapY = 120;
	sprite[2].m_startBitmapX = 0; sprite[2].m_startBitmapY = 50;

	sprite[0].m_bitmapWidth = 198; sprite[0].m_bitmapHeight = 21;
	sprite[1].m_bitmapWidth = 171; sprite[1].m_bitmapHeight = 13;
	sprite[2].m_bitmapWidth = 204; sprite[2].m_bitmapHeight = 54;
	sprite[3].m_bitmapWidth = 7; sprite[3].m_bitmapHeight = 9;

	m_UIPos[0].x = -100; m_UIPos[0].y = -350;
	m_UIPos[1].x = m_UIPos[0].x + 27; m_UIPos[1].y = m_UIPos[0].y + 3;
	m_UIPos[2].x = m_UIPos[0].x + 0; m_UIPos[2].y = m_UIPos[0].y - 10;
	m_UIPos[3].x = m_UIPos[0].x + 80; m_UIPos[3].y = m_UIPos[0].y + 5;

	return true;
}