#include "../../Header/stdafx.h"
//#include "../../Graphics/TextureClass.h"
#include "KeyConfig.h"

KeyConfigUIClass::KeyConfigUIClass()
{
	m_remainCount = 0;
	m_isClick = -1;
	memset(m_UIPos, 0, sizeof(m_UIPos));
}

KeyConfigUIClass::KeyConfigUIClass(const KeyConfigUIClass&)
{
	m_remainCount = 0;
	m_isClick = -1;
	memset(m_UIPos, 0, sizeof(m_UIPos));
}

KeyConfigUIClass::~KeyConfigUIClass()
{
}

bool KeyConfigUIClass::Initialize(ID3D11Device* device)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}

	m_device = device;

	sprite = new Sprite[4];

	sprite[0] = LoadTexture(device, L"../Graphics/data/UI/KeyConfigBack_1.dds"); // 660 521
	sprite[1] = LoadTexture(device, L"../Graphics/data/UI/KeyConfigBack_2.dds"); // 640 479
	sprite[2] = LoadTexture(device, L"../Graphics/data/UI/KeyConfig.dds"); // 620 300

	sprite[0].m_fullSizeX = 660; sprite[0].m_fullSizeY = 660;
	sprite[0].m_bitmapWidth = 660; sprite[0].m_bitmapHeight = 521;
	sprite[1].m_fullSizeX = 640; sprite[1].m_fullSizeY = 640;
	sprite[1].m_bitmapWidth = 640; sprite[1].m_bitmapHeight = 479;
	sprite[2].m_fullSizeX = 620; sprite[2].m_fullSizeY = 300;
	sprite[2].m_bitmapWidth = 620; sprite[2].m_bitmapHeight = 231;

	nowSprite.m_startBitmapX = 0; nowSprite.m_startBitmapY = 0;

	m_UIPos[0].x = -500; m_UIPos[0].y = -300;
	m_UIPos[1].x = m_UIPos[0].x + 9.7f; m_UIPos[1].y = m_UIPos[0].y + 19.3f;
	m_UIPos[2].x = m_UIPos[0].x + 20.5f; m_UIPos[2].y = m_UIPos[0].y + 222;

	m_keyPosition = new KeyPosition[66];
#pragma region F1 ~ F12
	m_keyPosition[0].Key = 0x70; m_keyPosition[0].pos = XMFLOAT2(m_UIPos[0].x + 96, m_UIPos[0].y + 403);
	m_keyPosition[1].Key = 0x71; m_keyPosition[1].pos = XMFLOAT2(m_keyPosition[0].pos.x + 33, m_keyPosition[0].pos.y);
	m_keyPosition[2].Key = 0x72; m_keyPosition[2].pos = XMFLOAT2(m_keyPosition[0].pos.x + 66, m_keyPosition[0].pos.y);
	m_keyPosition[3].Key = 0x73; m_keyPosition[3].pos = XMFLOAT2(m_keyPosition[0].pos.x + 99, m_keyPosition[0].pos.y);
	m_keyPosition[4].Key = 0x74; m_keyPosition[4].pos = XMFLOAT2(m_UIPos[0].x + 244, m_UIPos[0].y + 403);
	m_keyPosition[5].Key = 0x75; m_keyPosition[5].pos = XMFLOAT2(m_keyPosition[4].pos.x + 33, m_keyPosition[4].pos.y);
	m_keyPosition[6].Key = 0x76; m_keyPosition[6].pos = XMFLOAT2(m_keyPosition[4].pos.x + 66, m_keyPosition[4].pos.y);
	m_keyPosition[7].Key = 0x77; m_keyPosition[7].pos = XMFLOAT2(m_keyPosition[4].pos.x + 99, m_keyPosition[4].pos.y);
	m_keyPosition[8].Key = 0x78; m_keyPosition[8].pos = XMFLOAT2(m_UIPos[0].x + 393, m_UIPos[0].y + 403);
	m_keyPosition[9].Key = 0x79; m_keyPosition[9].pos = XMFLOAT2(m_keyPosition[8].pos.x + 33, m_keyPosition[8].pos.y);
	m_keyPosition[10].Key = 0x80; m_keyPosition[10].pos = XMFLOAT2(m_keyPosition[8].pos.x + 66, m_keyPosition[8].pos.y);
	m_keyPosition[11].Key = 0x81; m_keyPosition[11].pos = XMFLOAT2(m_keyPosition[8].pos.x + 99, m_keyPosition[8].pos.y);
#pragma endregion

#pragma region  1 ~ =
	m_keyPosition[12].Key = 0x31; m_keyPosition[12].pos = XMFLOAT2(m_UIPos[0].x + 63, m_UIPos[0].y + 365);
	m_keyPosition[13].Key = 0x32; m_keyPosition[13].pos = XMFLOAT2(m_keyPosition[12].pos.x + 33, m_keyPosition[12].pos.y);
	m_keyPosition[14].Key = 0x33; m_keyPosition[14].pos = XMFLOAT2(m_keyPosition[12].pos.x + 66, m_keyPosition[12].pos.y);
	m_keyPosition[15].Key = 0x34; m_keyPosition[15].pos = XMFLOAT2(m_keyPosition[12].pos.x + 99, m_keyPosition[12].pos.y);
	m_keyPosition[16].Key = 0x35; m_keyPosition[16].pos = XMFLOAT2(m_keyPosition[12].pos.x + 132, m_keyPosition[12].pos.y);
	m_keyPosition[17].Key = 0x36; m_keyPosition[17].pos = XMFLOAT2(m_keyPosition[12].pos.x + 165, m_keyPosition[12].pos.y);
	m_keyPosition[18].Key = 0x37; m_keyPosition[18].pos = XMFLOAT2(m_keyPosition[12].pos.x + 198, m_keyPosition[12].pos.y);
	m_keyPosition[19].Key = 0x38; m_keyPosition[19].pos = XMFLOAT2(m_keyPosition[12].pos.x + 231, m_keyPosition[12].pos.y);
	m_keyPosition[20].Key = 0x39; m_keyPosition[20].pos = XMFLOAT2(m_keyPosition[12].pos.x + 264, m_keyPosition[12].pos.y);
	m_keyPosition[21].Key = 0x30; m_keyPosition[21].pos = XMFLOAT2(m_keyPosition[12].pos.x + 297, m_keyPosition[12].pos.y);
	/*m_keyPosition[22].Key = 0x6D; m_keyPosition[22].pos = XMFLOAT2(-272 + 320, 220);
	m_keyPosition[23].Key = 0x6B; m_keyPosition[23].pos = XMFLOAT2(-272 + 352, 220);*/
#pragma endregion

#pragma region Q ~ ]
	m_keyPosition[24].Key = 0x51; m_keyPosition[24].pos = XMFLOAT2(m_UIPos[0].x + 78, m_UIPos[0].y + 332);
	m_keyPosition[25].Key = 0x57; m_keyPosition[25].pos = XMFLOAT2(m_keyPosition[24].pos.x + 33, m_keyPosition[24].pos.y);
	m_keyPosition[26].Key = 0x45; m_keyPosition[26].pos = XMFLOAT2(m_keyPosition[24].pos.x + 66, m_keyPosition[24].pos.y);
	m_keyPosition[27].Key = 0x52; m_keyPosition[27].pos = XMFLOAT2(m_keyPosition[24].pos.x + 99, m_keyPosition[24].pos.y);
	m_keyPosition[28].Key = 0x54; m_keyPosition[28].pos = XMFLOAT2(m_keyPosition[24].pos.x + 132, m_keyPosition[24].pos.y);
	m_keyPosition[29].Key = 0x59; m_keyPosition[29].pos = XMFLOAT2(m_keyPosition[24].pos.x + 165, m_keyPosition[24].pos.y);
	m_keyPosition[30].Key = 0x55; m_keyPosition[30].pos = XMFLOAT2(m_keyPosition[24].pos.x + 198, m_keyPosition[24].pos.y);
	m_keyPosition[31].Key = 0x49; m_keyPosition[31].pos = XMFLOAT2(m_keyPosition[24].pos.x + 231, m_keyPosition[24].pos.y);
	m_keyPosition[32].Key = 0x4F; m_keyPosition[32].pos = XMFLOAT2(m_keyPosition[24].pos.x + 264, m_keyPosition[24].pos.y);
	m_keyPosition[33].Key = 0x50; m_keyPosition[33].pos = XMFLOAT2(m_keyPosition[24].pos.x + 297, m_keyPosition[24].pos.y);
	//m_keyPosition[34].Key = 0x38; m_keyPosition[20].pos = XMFLOAT2(-256 + 320, 255 - 32);
	//m_keyPosition[35].Key = 0x39; m_keyPosition[21].pos = XMFLOAT2(-256 + 352, 220 - 32);
#pragma endregion

#pragma region A ~ L
	m_keyPosition[36].Key = 0x41; m_keyPosition[36].pos = XMFLOAT2(m_UIPos[0].x + 95, m_UIPos[0].y + 299);
	m_keyPosition[37].Key = 0x53; m_keyPosition[37].pos = XMFLOAT2(m_keyPosition[36].pos.x + 33, m_keyPosition[36].pos.y);
	m_keyPosition[38].Key = 0x44; m_keyPosition[38].pos = XMFLOAT2(m_keyPosition[36].pos.x + 66, m_keyPosition[36].pos.y);
	m_keyPosition[39].Key = 0x46; m_keyPosition[39].pos = XMFLOAT2(m_keyPosition[36].pos.x + 99, m_keyPosition[36].pos.y);
	m_keyPosition[40].Key = 0x47; m_keyPosition[40].pos = XMFLOAT2(m_keyPosition[36].pos.x + 132, m_keyPosition[36].pos.y);
	m_keyPosition[41].Key = 0x48; m_keyPosition[41].pos = XMFLOAT2(m_keyPosition[36].pos.x + 165, m_keyPosition[36].pos.y);
	m_keyPosition[42].Key = 0x4A; m_keyPosition[42].pos = XMFLOAT2(m_keyPosition[36].pos.x + 198, m_keyPosition[36].pos.y);
	m_keyPosition[43].Key = 0x4B; m_keyPosition[43].pos = XMFLOAT2(m_keyPosition[36].pos.x + 231, m_keyPosition[36].pos.y);
	m_keyPosition[44].Key = 0x4C; m_keyPosition[44].pos = XMFLOAT2(m_keyPosition[36].pos.x + 264, m_keyPosition[36].pos.y);
	//m_keyPosition[45].Key = 0x38; m_keyPosition[20].pos = XMFLOAT2(-256 + 320, 255 - 32);
	//m_keyPosition[46].Key = 0x39; m_keyPosition[21].pos = XMFLOAT2(-256 + 352, 220 - 32);
#pragma endregion

#pragma region Z ~ /
	m_keyPosition[47].Key = 0x5A; m_keyPosition[47].pos = XMFLOAT2(m_UIPos[0].x + 111, m_UIPos[0].y + 266);
	m_keyPosition[48].Key = 0x58; m_keyPosition[48].pos = XMFLOAT2(m_keyPosition[47].pos.x + 33, m_keyPosition[47].pos.y);
	m_keyPosition[49].Key = 0x43; m_keyPosition[49].pos = XMFLOAT2(m_keyPosition[47].pos.x + 66, m_keyPosition[47].pos.y);
	m_keyPosition[50].Key = 0x56; m_keyPosition[50].pos = XMFLOAT2(m_keyPosition[47].pos.x + 99, m_keyPosition[47].pos.y);
	m_keyPosition[51].Key = 0x42; m_keyPosition[51].pos = XMFLOAT2(m_keyPosition[47].pos.x + 132, m_keyPosition[47].pos.y);
	m_keyPosition[52].Key = 0x4E; m_keyPosition[52].pos = XMFLOAT2(m_keyPosition[47].pos.x + 165, m_keyPosition[47].pos.y);
	m_keyPosition[53].Key = 0x4D; m_keyPosition[53].pos = XMFLOAT2(m_keyPosition[47].pos.x + 198, m_keyPosition[47].pos.y);
	//m_keyPosition[54].Key = 0x4B; m_keyPosition[43].pos = XMFLOAT2(-240 + 224, 188 - 32);
	//m_keyPosition[55].Key = 0x4C; m_keyPosition[44].pos = XMFLOAT2(-240 + 256, 255 - 32);
	//m_keyPosition[45].Key = 0x38; m_keyPosition[20].pos = XMFLOAT2(-256 + 320, 255 - 32);
#pragma endregion

#pragma region Ctrl, Alt, Shift, Space
	m_keyPosition[56].Key = 0x11; m_keyPosition[56].pos = XMFLOAT2(m_UIPos[0].x + 37, m_UIPos[0].y + 233); // Ctrl
	m_keyPosition[57].Key = 0x12; m_keyPosition[57].pos = XMFLOAT2(m_keyPosition[56].pos.x + 98, m_keyPosition[56].pos.y); // Alt
	m_keyPosition[58].Key = 0x10; m_keyPosition[58].pos = XMFLOAT2(m_keyPosition[56].pos.x + 16, m_keyPosition[56].pos.y + 33); // Shift
	m_keyPosition[59].Key = 0x20; m_keyPosition[59].pos = XMFLOAT2(m_keyPosition[56].pos.x + 222, m_keyPosition[56].pos.y); // Space
#pragma endregion

#pragma region Delete ~ PageUp
	m_keyPosition[60].Key = 0x2E; m_keyPosition[60].pos = XMFLOAT2(m_UIPos[0].x + 534, m_UIPos[0].y + 332); // Delete
	m_keyPosition[61].Key = 0x23; m_keyPosition[61].pos = XMFLOAT2(m_keyPosition[60].pos.x + 33, m_keyPosition[60].pos.y); // End
	m_keyPosition[62].Key = 0x22; m_keyPosition[62].pos = XMFLOAT2(m_keyPosition[60].pos.x + 66, m_keyPosition[60].pos.y); // PageDown
	m_keyPosition[63].Key = 0x2D; m_keyPosition[63].pos = XMFLOAT2(m_keyPosition[60].pos.x, m_keyPosition[60].pos.y + 33);  // Insert
	m_keyPosition[64].Key = 0x24; m_keyPosition[64].pos = XMFLOAT2(m_keyPosition[60].pos.x + 33, m_keyPosition[60].pos.y + 33); // Home
	m_keyPosition[65].Key = 0x21; m_keyPosition[65].pos = XMFLOAT2(m_keyPosition[60].pos.x + 66, m_keyPosition[60].pos.y + 33); // PageUp
#pragma endregion

	m_UIPos[3] = m_keyPosition[26].pos; // 파엘
	m_UIPos[4] = m_keyPosition[36].pos; // 공격
	m_UIPos[5] = m_keyPosition[39].pos; // 점프

	nowSprite.m_isRender = false;
	return true;
}

void KeyConfigUIClass::Frame(POINT pos)
{
	if (m_isClick != -1)
	{
		m_UIPos[m_isClick].x = pos.x - 10; m_UIPos[m_isClick].y = pos.y - 25;
	}
}

bool KeyConfigUIClass::boxCheck(POINT pos, int num)
{
	bool b_Check = true;
	b_Check &= pos.x >= m_UIPos[num].x - 5;
	b_Check &= pos.x <= m_UIPos[num].x + 30;

	b_Check &= pos.y >= m_UIPos[num].y + 18;
	b_Check &= pos.y <= m_UIPos[num].y + 50;

	return b_Check;
}

void KeyConfigUIClass::set(POINT pos, int num)
{
	if (boxCheck(pos, num))
	{
		if (m_isClick == -1)
		{
			m_isClick = num;
		}
		else
		{
			for (int i = 0; i < 66; i++)
			{
				if (pos.x >= m_keyPosition[i].pos.x - 5 && pos.x <= m_keyPosition[i].pos.x + 30 &&
					pos.y >= m_keyPosition[i].pos.y + 18 && pos.y <= m_keyPosition[i].pos.y + 50)
				{
					m_isClick = -1;
					m_UIPos[num] = m_keyPosition[i].pos;

					switch (num)
					{
					case 3:
						PlayerClass::Instance()->m_HPRecover = m_keyPosition[i].Key;
						break;
					case 4:
						PlayerClass::Instance()->m_AttackKey = m_keyPosition[i].Key;
						break;
					case 5:
						PlayerClass::Instance()->m_JumpKey = m_keyPosition[i].Key;
						break;
					}
					break;
				}
			}
			
		}
	}
}
