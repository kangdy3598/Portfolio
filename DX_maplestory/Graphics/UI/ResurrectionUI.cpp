#include "../../Header/stdafx.h"
#include "ResurrectionUI.h"
#include "../Unit/Player/PlayerState.h"
ResurrectionUIClass::ResurrectionUIClass()
{
	memset(m_UIPos, 0, sizeof(m_UIPos));
}
ResurrectionUIClass::ResurrectionUIClass(const ResurrectionUIClass& other)
{
	memset(m_UIPos, 0, sizeof(m_UIPos));
}
ResurrectionUIClass::~ResurrectionUIClass()
{
}

bool ResurrectionUIClass::Initialize(ID3D11Device* device)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}
	m_device = device;

	sprite = new Sprite[2];

	nowSprite = LoadTexture(device, L"../Graphics/data/UI/ResurrectionUI.dds");
	nowSprite.m_fullSizeX = nowSprite.m_fullSizeY = 512;

	sprite[0] = sprite[1] = nowSprite;

	sprite[0].m_startBitmapX = 0; sprite[0].m_startBitmapY = 0;
	sprite[1].m_startBitmapX = 0; sprite[1].m_startBitmapY = 140;

	sprite[0].m_bitmapWidth = 300; sprite[0].m_bitmapHeight = 131;
	sprite[1].m_bitmapWidth = 40; sprite[1].m_bitmapHeight = 16;

	m_UIPos[0].x = -150; m_UIPos[0].y = 50;
	m_UIPos[1].x = m_UIPos[0].x + 240; m_UIPos[1].y = m_UIPos[0].y + 15;

	return true;
}

bool ResurrectionUIClass::ClickButton(POINT pos, int type)
{
	bool bCheck = true;
	bCheck &= type == 3;
	bCheck &= pos.x > m_UIPos[1].x - 10;
	bCheck &= pos.x < m_UIPos[1].x + 30;
	bCheck &= pos.y > m_UIPos[1].y + 15;
	bCheck &= pos.y < m_UIPos[1].y + 45;

	if (bCheck)
	{
		PlayerClass::Instance()->m_Pos = XMFLOAT2(0, 0);
		PlayerClass::Instance()->ChangeState(PlayerJump::Instance(), PlayerClass::Instance());
		PlayerClass::Instance()->m_nowHP = PlayerClass::Instance()->m_maxHP;
		return true;
	}
	return false;
}
