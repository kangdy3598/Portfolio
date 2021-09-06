#include "../../Header/stdafx.h"
//#include "../../Graphics/TextureClass.h"
#include "Notice.h"

NoticeClass::NoticeClass()
{
	textMsg = nullptr;
	m_frameTime = 0;
}
NoticeClass::NoticeClass(const NoticeClass&)
{
	textMsg = nullptr;
	m_frameTime = 0;
}
NoticeClass::~NoticeClass()
{
}

bool NoticeClass::Initialize(ID3D11Device* device)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}

	m_device = device;
	sprite = new Sprite[3];
	nowSprite = LoadTexture(device, L"../Graphics/data/UI/Notice.dds");
	nowSprite.m_fullSizeX = nowSprite.m_fullSizeY = 256;

	for (int i = 0; i < 3; i++)
	{
		sprite[i] = nowSprite;
		sprite[i].m_startBitmapX = i * 12; sprite[i].m_startBitmapY = 0;
		sprite[i].m_bitmapWidth = 12; sprite[i].m_bitmapHeight = 54;
	}
	
	//DrawNotice();
	m_Pos.y = 200;
	return true;
}

void NoticeClass::DrawNotice(int type)
{
	/*sprite = new Sprite[3];
	switch (type)
	{
	case 0:
		for (int i = 0; i < 3; i++)
		{
			sprite[i].m_startBitmapX = i * 12; sprite[i].m_startBitmapY = 0;
			sprite[i].m_bitmapWidth = 12; sprite[i].m_bitmapHeight = 54;
		}
		break;
	case 1:
		for (int i = 0; i < 3; i++)
		{
			sprite[i].m_startBitmapX = i * 33; sprite[i].m_startBitmapY = 100;
			sprite[i].m_bitmapWidth = 33; sprite[i].m_bitmapHeight = 83;
		}
		nowSprite = sprite[0];
		break;
	}*/
	
}
