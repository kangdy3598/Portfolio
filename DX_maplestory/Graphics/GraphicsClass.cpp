#include "../Header/stdafx.h"
#include "../Class/D3DClass.h"
#include "../Class/CameraClass.h"

#include "../Unit/Player/SkillEffect.h"
//#include "../Unit/Player/Skill_Ultimate.h"
//#include "../Unit/Damage.h"

//#include "../Unit/Enemy/EnemyPoison.h"
//#include "../Unit/Enemy/EnemyFire.h"
//#include "../Unit/Enemy/EnemyObstacle.h"

#include "../Graphics/UI/PlayerHP.h"
#include "../Graphics/UI/EnemyHP.h"
#include "../Graphics/UI/ResurrectionUI.h"
#include "../Graphics/UI/DeathCountUI.h"
#include "../Graphics/UI/KeyConfig.h"
#include "../Graphics/UI/Notice.h"

#include "../Unit/Enemy/EnemyState.h"
//#include "../Unit/ObjectPool.h"
//#include "../Unit/PoolList.h"

#include "textureshaderclass.h"
#include "LineShaderClass.h"
#include "GraphicsClass.h"

#include <vector>

GraphicsClass::GraphicsClass()
{
}
GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}
GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	m_Direct3D = new D3DClass;
	m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);

	m_Camera = new CameraClass;
	m_Camera->SetPosition(0.0f, 0.0f, -6.0f);

	m_TextureShader = new TextureShaderClass;
	m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd);

	m_Background = new BackgroundClass;
	m_Background->Initialize(m_Direct3D->GetDevice(), L"../Graphics/data/Background.dds", 3055, 910);

	//m_Enemy = EnemyClass::Instance();
	//m_Enemy->Initialize(m_Direct3D->GetDevice());

	//for (int i = 0; i < sizeof(obPool) / sizeof(ObjectPoolClass*); i++) obPool[i] = new ObjectPoolClass;

	//obPool[0]->SetObjectPool(EnemyObstacleClass::Instance(), "obstacle", 8);
	//srand((unsigned int)time(NULL));
	//for (int i = 0; i < sizeof(m_EnemyObstacle) / sizeof(EnemyObstacleClass*); i++)
	//{
	//	m_EnemyObstacle[i] = (EnemyObstacleClass*)obPool[0]->PopFromPool();
	//	m_EnemyObstacle[i]->Initialize(m_Direct3D->GetDevice());
	//	m_EnemyObstacle[i]->m_Pos.x = i * 100;// -1500 + (rand() % 11) * 300.0f;
	//	/*for (int j = 0; j < i; j++)
	//	{
	//		if (m_EnemyObstacle[i]->m_Pos.x == m_EnemyObstacle[j]->m_Pos.x)
	//		{
	//			obPool[0]->PushToPool(m_EnemyObstacle[i]); 
	//			m_EnemyObstacle[i] = NULL;
	//			i--;
	//			break;
	//		}
	//	}*/
	//}

	//obPool[1]->SetObjectPool(EnemyTailClass::Instance(), "tail", 3);
	//for (int i = 0; i < sizeof(m_EnemyTail) / sizeof(EnemyTailClass*); i++)
	//{
	//	m_EnemyTail[i] = (EnemyTailClass*)obPool[1]->PopFromPool();
	//	m_EnemyTail[i]->Initialize(m_Direct3D->GetDevice());
	//}

	//obPool[2]->SetObjectPool(EnemyPoisonClass::Instance(), "poison", 24);
	//for (int i = 0; i < sizeof(m_EnemyPoison) / sizeof(EnemyPoisonClass*); i++)
	//{
	//	m_EnemyPoison[i] = (EnemyPoisonClass*)obPool[2]->PopFromPool();
	//	m_EnemyPoison[i]->Initialize(m_Direct3D->GetDevice());
	//}

	//obPool[3]->SetObjectPool(DamageClass::Instance(), "hit_damage", 15);
	//for (int i = 0; i < sizeof(m_hitDamage) / sizeof(DamageClass*); i++)
	//{
	//	m_hitDamage[i] = (DamageClass*)obPool[3]->PopFromPool();
	//	m_hitDamage[i]->Initialize(m_Direct3D->GetDevice(), 0);
	//	//m_hitDamage[i]->nowSprite.m_isRender = false;
	//}

	//obPool[4]->SetObjectPool(DamageClass::Instance(), "attack_damage", 15);
	//for (int i = 0; i < sizeof(m_attackDamage) / sizeof(DamageClass*); i++)
	//{
	//	m_attackDamage[i] = (DamageClass*)obPool[4]->PopFromPool();
	//	m_attackDamage[i]->Initialize(m_Direct3D->GetDevice(), 1);
	//	//m_attackDamage[i]->nowSprite.m_isRender = false;
	//}

	m_Player = PlayerClass::Instance();
	m_Player->Initialize(m_Direct3D->GetDevice());

	m_PlayerHPBar = new PlayerHPClass;
	m_PlayerHPBar->Initialize(m_Direct3D->GetDevice());
	m_EnemyHPBar = new EnemyHPClass;
	m_EnemyHPBar->Initialize(m_Direct3D->GetDevice());

	m_KeyConfigUI = new KeyConfigUIClass;
	m_KeyConfigUI->Initialize(m_Direct3D->GetDevice());

	//m_Notice[0] = new NoticeClass;
	//m_Notice[0]->Initialize(m_Direct3D->GetDevice());

	m_ResurrectionUI = new ResurrectionUIClass;
	m_ResurrectionUI->Initialize(m_Direct3D->GetDevice());
/*
	m_DeathCountUI[0] = new DeathCountUIClass;
	m_DeathCountUI[0]->Initialize(m_Direct3D->GetDevice(), L"../Graphics/data/UI/DeathCountUI.dds", 89, 56, 0);
	m_DeathCountUI[1] = new DeathCountUIClass;
	m_DeathCountUI[1]->Initialize(m_Direct3D->GetDevice(), L"../Graphics/data/UI/DeathCountUI.dds", 12, 17, 1);

	m_Notice[0] = new NoticeClass;
	m_Notice[0]->Initialize(m_Direct3D->GetDevice(), L"../Graphics/data/UI/Notice.dds");
	m_Notice[1] = new NoticeClass;
	m_Notice[1]->Initialize(m_Direct3D->GetDevice(), L"../Graphics/data/UI/Notice.dds");
	m_Notice[2] = new NoticeClass;
	m_Notice[2]->Initialize(m_Direct3D->GetDevice(), L"../Graphics/data/UI/Notice.dds");*/

	m_Collision = new CollisionClass;
	m_Collision->Initialize(m_Direct3D->GetDevice());

	m_LineShader = new LineShaderClass;
	m_LineShader->Initialize(m_Direct3D->GetDevice(), hwnd);

	return true;
}

void GraphicsClass::Shutdown()
{
	if (m_Player)
	{
		m_Player->Shutdown();
		delete m_Player;
		m_Player = 0;
	}

	if (m_Enemy)
	{
		m_Enemy->Shutdown();
		delete m_Enemy;
		m_Enemy = 0;
	}

	//for (int i = 0; i < sizeof(m_hitDamage) / sizeof(DamageClass*); i++)
	//{
	//	if (m_hitDamage[i])
	//	{
	//		m_hitDamage[i]->Shutdown();
	//		//delete m_hitDamage[i];
	//		m_hitDamage[i] = 0;
	//	}
	//}
	//
	//for (int i = 0; i < sizeof(m_attackDamage) / sizeof(DamageClass*); i++)
	//{
	//	if (m_attackDamage[i])
	//	{
	//		m_attackDamage[i]->Shutdown();
	//		//delete m_attackDamage[i];
	//		m_attackDamage[i] = 0;
	//	}
	//}

	if (m_PlayerHPBar)
	{
		m_PlayerHPBar->Shutdown();
		delete m_PlayerHPBar;
		m_PlayerHPBar = 0;
	}
	
	if (m_EnemyHPBar)
	{
		m_EnemyHPBar->Shutdown();
		delete m_EnemyHPBar;
		m_EnemyHPBar = 0;
	}

	if (m_ResurrectionUI)
	{
		m_ResurrectionUI->Shutdown();
		delete m_ResurrectionUI;
		m_ResurrectionUI = 0;
	}

	for (int i = 0; i < sizeof(m_DeathCountUI) / sizeof(DeathCountUIClass*); i++)
	{
		if (m_DeathCountUI[i])
		{
			m_DeathCountUI[i]->Shutdown();
			delete m_DeathCountUI[i];
			m_DeathCountUI[i] = 0;
		}
	}

	if (m_KeyConfigUI)
	{
		m_KeyConfigUI->Shutdown();
		delete m_KeyConfigUI;
		m_KeyConfigUI = 0;
	}

	for (int i = 0; i < sizeof(m_Notice) / sizeof(NoticeClass*); i++)
	{
		if (m_Notice[i])
		{
			m_Notice[i]->Shutdown();
			delete m_Notice[i];
			m_Notice[i] = 0;
		}
	}

	if (m_Background)
	{
		m_Background->Shutdown();
		delete m_Background;
		m_Background = 0;
	}

	if (m_Collision)
	{
		m_Collision->Shutdown();
		delete m_Collision;
		m_Collision = 0;
	}

	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	
}

bool GraphicsClass::Frame(int mouseX, int mouseY, int isClick, unsigned char keyState[256], float tickTime)
{
	//m_MouseClick = isClick;

	XMMATRIX ortho;
	m_Direct3D->GetOrthoMatrix(ortho);
	POINT pos; pos.x = mouseX, pos.y = mouseY;
	POINT worldpos = m_Camera->ScreenToWorldPoint(ortho, pos);
	m_mousePosX = worldpos.x; m_mousePosY = worldpos.y;
	
	if (isClick == 1)
	{
		bool bCheck = true;
		bCheck &= !m_KeyConfigUI->nowSprite.m_isRender;
		bCheck &= m_mousePosX > -60; bCheck &=  m_mousePosX < 320;
		bCheck &= m_mousePosY > -250; bCheck &= m_mousePosY < 0;

		if (bCheck && !m_Enemy)
		{
			m_Enemy = EnemyClass::Instance();
			m_Enemy->Initialize(m_Direct3D->GetDevice());
			m_Enemy->ChangeState(EnemySummon::Instance(), m_Enemy);
		}

		for (int i = 3; i < 6; i++)
		{
			m_KeyConfigUI->set(pos, i);
		}
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
	{
		m_KeyConfigUI->nowSprite.m_isRender ^= TRUE;
		/*m_KeyConfigUI[0]->m_bIsRender ^= TRUE;
		m_KeyConfigUI[1]->m_bIsSelect = false;
		m_KeyConfigUI[1]->m_Pos = m_KeyConfigUI[1]->m_nowPos;*/
	}

	
	if(m_Enemy) m_Enemy->Frame(tickTime);
	m_Player->Frame(tickTime, keyState);

	m_KeyConfigUI->Frame(pos);
	m_ResurrectionUI->ClickButton(pos, isClick);

	return Render(tickTime);
}

bool GraphicsClass::Render(float tickTime)
{
	m_Direct3D->BeginScene(1.0f, 1.0f, 1.0f, 1.0f);

	m_Camera->SetPosition(m_Player->m_Pos.x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
	m_Camera->Render();

	XMMATRIX viewMatrix, orthoMatrix;

	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);
	m_Direct3D->TurnZBufferOff();

	#pragma region 배경
		m_Background->Render(m_Direct3D->GetDeviceContext());
		m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Background->GetIndexCount(),
			XMMatrixIdentity(), viewMatrix, orthoMatrix, m_Background->GetTexture());
	#pragma endregion

	#pragma region 적
		if (m_Enemy)
		{
			m_Enemy->Render(m_Direct3D->GetDeviceContext(), tickTime);
			m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Enemy->GetIndexCount(),
				XMMatrixIdentity(), viewMatrix, orthoMatrix, m_Enemy->GetTexture());

			if (m_Enemy->m_bHit)
			{

			}
		#pragma region 꼬리

			if (m_Enemy->m_summon)
			{
				m_Enemy->m_summon = false;
				for (int i = 0; i < 3; i++)
				{
					if (!m_Enemy->m_EnemyTail[i]->nowSprite.m_isRender)
					{
						m_Enemy->m_EnemyTail[i]->nowSprite.m_isRender = true;
						m_Enemy->m_EnemyTail[i]->m_Pos.x = m_Player->m_Pos.x;
						break;
					}
				}
			}

			for (int i = 0; i < 3; i++)
			{
				if (m_Enemy->m_EnemyTail[i]->nowSprite.m_isRender)
				{
					m_Enemy->m_EnemyTail[i]->Render(m_Direct3D->GetDeviceContext(), tickTime);
					m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Enemy->m_EnemyTail[i]->GetIndexCount(),
						XMMatrixIdentity(), viewMatrix, orthoMatrix, m_Enemy->m_EnemyTail[i]->GetTexture());
				}
			}

		#pragma endregion

		#pragma region 독 영역
			if ((GetAsyncKeyState(0x42) & 0x0001)) //B
			{
				m_Enemy->m_warning = true;
				m_Enemy->m_warningCount++;
			}
			if (m_Enemy->m_warning)
			{
				m_Enemy->m_warning = false;
				srand((unsigned int)time(NULL));
				for (int i = 0; i < 8; i++)
				{
					if (!m_Enemy->m_EnemyPoison[m_Enemy->m_warningCount * 8 + i]->nowSprite.m_isRender)
					{
						m_Enemy->m_EnemyPoison[m_Enemy->m_warningCount * 8 + i]->nowSprite.m_isRender = true;
						m_Enemy->m_EnemyPoison[m_Enemy->m_warningCount * 8 + i]->m_Pos.x = -1500 + (rand() % 11) * 150.0f;
						for (int j = 0; j < i; j++)
						{
							if (m_Enemy->m_EnemyPoison[m_Enemy->m_warningCount * 8 + i]->m_Pos.x == m_Enemy->m_EnemyPoison[m_Enemy->m_warningCount * 8 + j]->m_Pos.x)
							{
								m_Enemy->m_EnemyPoison[m_Enemy->m_warningCount * 8 + i]->nowSprite.m_isRender = false;
								i--;
								break;
							}
						}
					}
				}
				if (m_Enemy->m_warningCount == 2) m_Enemy->m_warningCount = - 1;
			}

			for (int i = 0; i < 24; i++)
			{
				if (m_Enemy->m_EnemyPoison[i]->nowSprite.m_isRender)
				{
					m_Enemy->m_EnemyPoison[i]->Render(m_Direct3D->GetDeviceContext(), tickTime);
					m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Enemy->m_EnemyPoison[i]->GetIndexCount(),
						XMMatrixIdentity(), viewMatrix, orthoMatrix, m_Enemy->m_EnemyPoison[i]->GetTexture());
				}
			}
		#pragma endregion

		#pragma region 깊숨

			if (m_Enemy->m_EnemyState == EnemyClass::eEnemyState::ATTACK6)
			{
				//if (m_Enemy->m_AttackNumber >= 2 /*&& m_Enemy->m_AttackNumber <= 4*/)
				//{
				//	for (int i = 0; i < sizeof(m_Enemy->m_EnemyFire) / sizeof(EnemyFireClass*); i++)
				//	{
				//		//m_Enemy->m_EnemyFire[i]->LoadTexture(m_Direct3D->GetDevice(), L"../Graphics/data/Enemy/attack6_2_fire.dds", 341, 810);

				//		m_Enemy->m_EnemyFire[i]->Render(m_Direct3D->GetDeviceContext(), tickTime, i);
				//		m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Enemy->m_EnemyFire[i]->GetIndexCount(),
				//			XMMatrixIdentity(), viewMatrix, orthoMatrix, m_Enemy->m_EnemyFire[i]->GetTexture());
				//	}


				//}
				//else if (m_Enemy->m_AttackNumber == 5)
				//{
				//	//m_Enemy->m_EnemyFire->LoadTexture(m_Direct3D->GetDevice(), L"../Graphics/data/Enemy/attack6_3_fire.dds", 341, 679);
				//	for (int i = 0; i < sizeof(m_Enemy->m_EnemyFire) / sizeof(EnemyFireClass*); i++)
				//	{
				//		m_Enemy->m_EnemyFire[i]->Render(m_Direct3D->GetDeviceContext(), tickTime, i);
				//		m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Enemy->m_EnemyFire[i]->GetIndexCount(),
				//			XMMatrixIdentity(), viewMatrix, orthoMatrix, m_Enemy->m_EnemyFire[i]->GetTexture());
				//	}

				//}
			}
#pragma endregion

		#pragma region 종유석
		srand((unsigned int)time(NULL));
		for (int i = 0; i < 8; i++)
		{
			if (!m_Enemy->m_EnemyObstacle[i]->nowSprite.m_isRender)
			{
				m_Enemy->m_EnemyObstacle[i]->nowSprite.m_isRender = true;
				//m_Enemy->m_EnemyObstacle[i] = (EnemyObstacleClass*)ObjectPoolClass::Instance()->PopFromPool();
				m_Enemy->m_EnemyObstacle[i]->m_Pos.x = -1500 + (rand() % 11) * 300;
				for (int j = 0; j < i; j++)
				{
					if (m_Enemy->m_EnemyObstacle[i]->m_Pos.x == m_Enemy->m_EnemyObstacle[j]->m_Pos.x)
					{
						m_Enemy->m_EnemyObstacle[i]->nowSprite.m_isRender = false;
						i--;
						break;
					}
				}
			}
			else
			{
				m_Enemy->m_EnemyObstacle[i]->Render(m_Direct3D->GetDeviceContext(), tickTime);
				m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Enemy->m_EnemyObstacle[i]->GetIndexCount(),
					XMMatrixIdentity(), viewMatrix, orthoMatrix, m_Enemy->m_EnemyObstacle[i]->GetTexture());
			}
				
		}
	#pragma endregion
		}
		
	#pragma endregion

	#pragma region 스킬 이펙트(후방)

		for (int i = 0; i < 15; i++)
		{
			if (m_Player->m_skillEffect[i] && m_Player->m_skillEffect[i]->m_layerOrder == 1)
			{
				m_Player->m_skillEffect[i]->Render(m_Direct3D->GetDeviceContext(), tickTime);
				m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Player->m_skillEffect[i]->GetIndexCount(),
					XMMatrixIdentity(), viewMatrix, orthoMatrix, m_Player->m_skillEffect[i]->GetTexture());
			}
		}
		
		
	#pragma endregion

	#pragma region 플레이어
		m_Player->Render(m_Direct3D->GetDeviceContext(), tickTime);
		m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Player->GetIndexCount(),
			XMMatrixIdentity(), viewMatrix, orthoMatrix, m_Player->GetTexture());
	#pragma endregion

	#pragma region 스킬 이펙트(전방)

		for (int i = 0; i < 15; i++)
		{
			if (m_Player->m_skillEffect[i] && m_Player->m_skillEffect[i]->m_layerOrder == 0)
			{
				m_Player->m_skillEffect[i]->Render(m_Direct3D->GetDeviceContext(), tickTime);
				m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Player->m_skillEffect[i]->GetIndexCount(),
					XMMatrixIdentity(), viewMatrix, orthoMatrix, m_Player->m_skillEffect[i]->GetTexture());
			}
		}
		
	#pragma endregion

	#pragma region 스킬 피격 이펙트
		for (int i = 0; i < 15; i++)
		{
			if (m_Player->m_skillEffect[i] && m_Player->m_skillEffect[i]->m_layerOrder == 2)
			{
				m_Player->m_skillEffect[i]->m_Pos.x = m_Enemy->m_Pos.x;
				m_Player->m_skillEffect[i]->m_Pos.y = -300;

				m_Player->m_skillEffect[i]->Render(m_Direct3D->GetDeviceContext(), tickTime);
				m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Player->m_skillEffect[i]->GetIndexCount(),
					XMMatrixIdentity(), viewMatrix, orthoMatrix, m_Player->m_skillEffect[i]->GetTexture());

				
				if (m_Player->m_skillEffect[i]->m_isAnimationEnd)
				{
					m_Player->m_skillEffect[i]->Shutdown();
					delete m_Player->m_skillEffect[i];
					m_Player->m_skillEffect[i] = 0;

					break;
				}
			}
				
		}
	#pragma endregion

	#pragma region 충돌 상자
		//적
		if (m_Enemy)
		{
			if (m_Enemy->m_bHitAble)
			{
				m_Collision->Render(m_Direct3D->GetDeviceContext(), m_Enemy->m_hitBox, XMFLOAT4(0, 1, 0, 1));
				m_LineShader->Render(m_Direct3D->GetDeviceContext(), m_Collision->GetIndexCount(),
					XMMatrixIdentity(), viewMatrix, orthoMatrix);
			}

			if (m_Enemy->m_bAttackAble)
			{
				m_Collision->Render(m_Direct3D->GetDeviceContext(), m_Enemy->m_attackBox, XMFLOAT4(1, 0, 0, 1));
				m_LineShader->Render(m_Direct3D->GetDeviceContext(), m_Collision->GetIndexCount(),
					XMMatrixIdentity(), viewMatrix, orthoMatrix);
			}

			for (int i = 0; i < 3; i++)
			{
				if (m_Enemy->m_EnemyTail[i]->nowSprite.m_isRender && m_Enemy->m_EnemyTail[i]->m_bAttackAble)
				{
					m_Collision->Render(m_Direct3D->GetDeviceContext(), m_Enemy->m_EnemyTail[i]->m_attackBox, XMFLOAT4(1, 0, 0, 1));
					m_LineShader->Render(m_Direct3D->GetDeviceContext(), m_Collision->GetIndexCount(),
						XMMatrixIdentity(), viewMatrix, orthoMatrix);
				}
			}
			for (int i = 0; i < 24; i++)
			{
				if (m_Enemy->m_EnemyPoison[i]->nowSprite.m_isRender && m_Enemy->m_EnemyPoison[i]->m_bAttackAble)
				{
					m_Collision->Render(m_Direct3D->GetDeviceContext(), m_Enemy->m_EnemyPoison[i]->m_attackBox, XMFLOAT4(1, 0, 0, 1));
					m_LineShader->Render(m_Direct3D->GetDeviceContext(), m_Collision->GetIndexCount(),
						XMMatrixIdentity(), viewMatrix, orthoMatrix);
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if (m_Enemy->m_EnemyObstacle[i] && m_Enemy->m_EnemyObstacle[i]->m_bAttackAble)
				{
					m_Collision->Render(m_Direct3D->GetDeviceContext(), m_Enemy->m_EnemyObstacle[i]->m_attackBox, XMFLOAT4(1, 0, 0, 1));
					m_LineShader->Render(m_Direct3D->GetDeviceContext(), m_Collision->GetIndexCount(),
						XMMatrixIdentity(), viewMatrix, orthoMatrix);
				}
			}
		}
		
		// 플레이어
		m_Collision->Render(m_Direct3D->GetDeviceContext(), m_Player->m_hitBox, XMFLOAT4(0, 1, 0, 1));
		m_LineShader->Render(m_Direct3D->GetDeviceContext(), m_Collision->GetIndexCount(),
			XMMatrixIdentity(), viewMatrix, orthoMatrix);

		for (int i = 0; i < 15; i++)
		{
			if (m_Player->m_skillEffect[i])
			{
				m_Collision->Render(m_Direct3D->GetDeviceContext(), m_Player->m_skillEffect[i]->m_attackBox, XMFLOAT4(1, 0, 0, 1));
				m_LineShader->Render(m_Direct3D->GetDeviceContext(), m_Collision->GetIndexCount(),
					XMMatrixIdentity(), viewMatrix, orthoMatrix);
			}
		}
	#pragma endregion

	#pragma region 데미지출력

		//피격데미지
		if (m_Player->m_Hit)
		{
			for (int i = 0; i < 15; i++)
			{
				if (!m_Player->m_hitDamage[i]->nowSprite.m_isRender)
				{
					m_Player->m_hitDamage[i]->nowSprite.m_isRender = true;
					m_Player->m_hitDamage[i]->m_amount = m_Player->m_HitAmount;
					m_Player->m_hitDamage[i]->m_startPos = m_Player->m_head;
					m_Player->m_hitDamage[i]->m_Pos.y = m_Player->m_hitDamage[i]->m_startPos.y;
					m_Player->m_Hit = false;
					break;
				}
			}
		}

		for (int i = 0; i < 15; i++)
		{
			if (m_Player->m_hitDamage[i]->nowSprite.m_isRender)
			{
				int hitAmount = m_Player->m_hitDamage[i]->m_amount;
				std::vector<int> v;

				while (hitAmount)
				{
					v.push_back(hitAmount % 10);
					hitAmount /= 10;
				}
				int size = (int)v.size();
				for (int j = 0; j < size; j++)
				{
					m_Player->m_hitDamage[i]->m_animationX = v.back() % 5 + 1;
					m_Player->m_hitDamage[i]->m_animationY = v.back() / 5 + 1;

					m_Player->m_hitDamage[i]->m_Pos.x = m_Player->m_hitDamage[i]->m_startPos.x + j * 25;
					m_Player->m_hitDamage[i]->Render(m_Direct3D->GetDeviceContext(), tickTime);
					m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Player->m_hitDamage[i]->GetIndexCount(),
						XMMatrixIdentity(), viewMatrix, orthoMatrix, m_Player->m_hitDamage[i]->GetTexture(), m_Player->m_hitDamage[i]->m_fadePercentage);
					v.pop_back();
				}
			}
		}

		if (m_Enemy && m_Enemy->m_bHit)
		{
			for (int i = 0; i < 15; i++)
			{
				if (!m_Player->m_attackDamage[i]->nowSprite.m_isRender)
				{
					m_Enemy->m_bHit = false;
					m_Player->m_attackDamage[i]->nowSprite.m_isRender = true;
					m_Player->m_attackDamage[i]->m_Pos.y = m_Enemy->m_head.y;
					m_Player->m_attackDamage[i]->m_amount = m_Enemy->m_hitDamage;
					break;
				}
			}
		}

		for (int i = 0; i < 15; i++)
		{
			if (m_Player->m_attackDamage[i]->nowSprite.m_isRender)
			{
				int hitAmount = m_Player->m_attackDamage[i]->m_amount;
				std::vector<int> v;

				while (hitAmount)
				{
					v.push_back(hitAmount % 10);
					hitAmount /= 10;
				}
				int size = (int)v.size();
				for (int j = 0; j < size; j++)
				{
					m_Player->m_attackDamage[i]->m_animationX = v.back() % 5 + 1;
					m_Player->m_attackDamage[i]->m_animationY = v.back() / 5 + 1;
					
					m_Player->m_attackDamage[i]->m_Pos.x = m_Enemy->m_head.x + j * 24.0f;
					m_Player->m_attackDamage[i]->Render(m_Direct3D->GetDeviceContext(), tickTime);
					m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Player->m_attackDamage[i]->GetIndexCount(),
						XMMatrixIdentity(), viewMatrix, orthoMatrix, m_Player->m_attackDamage[i]->GetTexture(), m_Player->m_attackDamage[i]->m_fadePercentage);
					v.pop_back();
				}
			}
		}
		
		
	#pragma endregion

	#pragma region Msg

		XMFLOAT3 cameraPosition = m_Camera->GetPosition();
		XMMATRIX UIworldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, 0.0f);

		/*const TCHAR* textMsg = nullptr;
		int notice_type = 0; float notice_xpos = 0;
		m_Notice[0]->m_frameTime += tickTime;*/

		//if (m_Enemy->m_EnemyState == EnemyClass::eEnemyState::WAIT && m_Notice[0]->m_frameTime < 7000)
		//{
		//	textMsg = L"벨룸이 보이지 않는다. 제단 근처를 조사해보자."; //26, 95
		//	//textMsg = L"내 경고를 무시하고 다시 찾아온 것은 네놈이니 더 이상 자비를 베풀지는 않겠다."; //44 160
		//	notice_xpos = _tcslen(textMsg) * -7.5f;
		//	m_Notice[0]->m_Pos.x = notice_xpos;
		//	for (int i = 0; i < 3; i++)
		//	{
		//		m_Notice[0]->nowSprite = m_Notice[0]->sprite[i];
		//		if (i == 1)
		//		{
		//			for (int j = 0; j < _tcslen(textMsg) * 3.6f; j++)
		//			{
		//				m_Notice[0]->m_Pos.x += 4;
		//				m_Notice[0]->Render(m_Direct3D->GetDeviceContext());
		//				m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Notice[0]->GetIndexCount(),
		//					UIworldMatrix, viewMatrix, orthoMatrix, m_Notice[0]->GetTexture());
		//			}
		//		}

		//		m_Notice[0]->Render(m_Direct3D->GetDeviceContext());
		//		m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Notice[0]->GetIndexCount(),
		//			UIworldMatrix, viewMatrix, orthoMatrix, m_Notice[0]->GetTexture());
		//	}
		//	m_Direct3D->Text(m_screenWidth, m_Notice[0]->m_Pos.y - 50.0f, 1.4f, Colors::AliceBlue, textMsg);
		//}

		/*else if(m_Enemy->m_EnemyState != EnemyClass::eEnemyClass::SUMMON)
		{
			if (m_Notice[0]->m_frameTime >= 7000)
			{
				m_Notice[0]->m_bIsRender = false;
			}

			else
			{
				textMsg = L"내 경고를 무시하고 다시 찾아온 것은 네놈이니 더 이상 자비를 베풀지는 않겠다.";
				notice_type = 1;
				notice_xpos = _tcslen(textMsg) * -7;
				m_Notice[0]->m_bIsRender = true;
			}
		}*/

		

		/*if (m_Enemy->m_EnemyState == EnemyClass::eEnemyClass::ATTACK6)
		{
			m_Direct3D->Text(m_screenWidth, 150, 1.5f, Colors::DarkOrange, L"벨룸이 깊은 숨을 들이쉽니다.");
		}*/
		
		//m_Direct3D->Text(m_screenWidth - 900, 100, 1.3f, Colors::White, L"플레이어 좌표 : [%f, %f]", m_Player->m_Pos.x , m_Player->m_Pos.y);
		//m_Direct3D->Text(m_screenWidth - 900, 130, 1.3f, Colors::White, L"플레이어 속력 : [%f, %f]", m_Player->m_AccelationX, m_Player->m_AccelationY);
		//m_Direct3D->Text(m_screenWidth - 900, 160, 1.3f, Colors::White, L"플레이어 상태 : %d", (int)m_Player->m_PlayerState);

		/*for (int i = 0; i < 6; i++)
		{
			m_Direct3D->Text(m_screenWidth + 900, 130 + i * 30, 1.3f, Colors::White, L"패턴 %d 쿨타임 :%f 초", i, m_Enemy->m_patternCoolTime[i]);
		}
		
		m_Direct3D->Text(m_screenWidth + 900, 100, 1.3f, Colors::White, L"적 상태 : %d", (int)m_Enemy->m_EnemyState);*/

		/*for (int i = 0; i < 3; i++)
		{
			if (m_EnemyTail[i]->nowSprite.m_isRender) m_Direct3D->Text(m_screenWidth + 700 + i * 200, 350, 1.3f, Colors::Aqua, L"꼬리 %d 생성", i);
			else m_Direct3D->Text(m_screenWidth + 700 + i * 200, 350, 1.3f, Colors::White, L"꼬리 %d 대기", i);
		}*/

		for (int i = 0; i < 24; i++)
		{
			//m_Direct3D->Text(m_screenWidth + 800 + i/8 * 200, 400 + i%8 * 30, 1.3f, Colors::Cyan, L"독 %d : %.2lf", i, m_EnemyPoison[i]->m_durationTime);
		}
		//m_Direct3D->Text(m_screenWidth, 100, 1.3f, Colors::White, L"마우스 월드좌표 : [%d, %d]", m_mousePosX, m_mousePosY);

		for (int i = 0; i < 15; i++)
		{
			if (m_Player->m_skillEffect[i])
			{
				//m_Direct3D->Text(m_screenWidth, 100, 1.3f, Colors::White, L"%s", m_Player->m_skillEffect[i]->m_name);
			}
		}
	#pragma endregion

	#pragma region UI
		// Player HP
		for (int i = 0; i < 4; i++)
		{
			m_PlayerHPBar->m_Pos = m_PlayerHPBar->m_UIPos[i];
			m_PlayerHPBar->nowSprite = m_PlayerHPBar->sprite[i];
			if (i == 3)
			{
				int nowHPAmount = m_Player->m_nowHP;
				std::vector<int> v;

				while (nowHPAmount)
				{
					v.push_back(nowHPAmount % 10);
					nowHPAmount /= 10;
				}
				int size = (int)v.size();
				if (size)
				{
					for (int j = 0; j < size; j++)
					{
						m_PlayerHPBar->nowSprite.m_startBitmapX = v.back() * m_PlayerHPBar->nowSprite.m_bitmapWidth;
						m_PlayerHPBar->m_Pos.x += 7;
						m_PlayerHPBar->Render(m_Direct3D->GetDeviceContext());
						m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_PlayerHPBar->GetIndexCount(),
							UIworldMatrix, viewMatrix, orthoMatrix, m_PlayerHPBar->GetTexture());
						v.pop_back();
					}
				}
				else
				{
					m_PlayerHPBar->nowSprite.m_startBitmapX = 0;
					m_PlayerHPBar->Render(m_Direct3D->GetDeviceContext());
					m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_PlayerHPBar->GetIndexCount(),
						UIworldMatrix, viewMatrix, orthoMatrix, m_PlayerHPBar->GetTexture());
				}
				break;
			}
			m_PlayerHPBar->Render(m_Direct3D->GetDeviceContext(), i);
			m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_PlayerHPBar->GetIndexCount(),
				UIworldMatrix, viewMatrix, orthoMatrix, m_PlayerHPBar->GetTexture());
		}

		// Enemy HP UI
		for (int i = 0; i < 6; i++)
		{
			m_EnemyHPBar->m_Pos = m_EnemyHPBar->m_UIPos[i];
			m_EnemyHPBar->nowSprite = m_EnemyHPBar->sprite[i];
			if (i == 3)
			{
				for (int j = 0; j < 1280; j++)
				{
					m_EnemyHPBar->m_Pos.x = m_EnemyHPBar->m_UIPos[i].x + j;
					m_EnemyHPBar->Render(m_Direct3D->GetDeviceContext());
					m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_EnemyHPBar->GetIndexCount(),
						UIworldMatrix, viewMatrix, orthoMatrix, m_EnemyHPBar->GetTexture());
				}
			}
			else if (i == 5 && m_Enemy)
			{
				for (int j = 0; j < 1280 * (float)m_Enemy->m_nowHP / (float)m_Enemy->m_maxHP; j++)
				{
					m_EnemyHPBar->m_Pos.x = m_EnemyHPBar->m_UIPos[i].x + j;
					m_EnemyHPBar->Render(m_Direct3D->GetDeviceContext());
					m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_EnemyHPBar->GetIndexCount(),
						UIworldMatrix, viewMatrix, orthoMatrix, m_EnemyHPBar->GetTexture());
				}
			}
			else
			{
				m_EnemyHPBar->Render(m_Direct3D->GetDeviceContext());
				m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_EnemyHPBar->GetIndexCount(),
					UIworldMatrix, viewMatrix, orthoMatrix, m_EnemyHPBar->GetTexture());
			}

		}

		//데스카운트
		/*m_DeathCountUI[0]->Render(m_Direct3D->GetDeviceContext(), XMFLOAT2(0, 0));
		m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_DeathCountUI[0]->GetIndexCount(),
			UIworldMatrix, viewMatrix, orthoMatrix, m_DeathCountUI[0]->GetTexture());

		m_DeathCountUI[1]->Render(m_Direct3D->GetDeviceContext(), XMFLOAT2(0, 0));
		m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_DeathCountUI[1]->GetIndexCount(),
			UIworldMatrix, viewMatrix, orthoMatrix, m_DeathCountUI[1]->GetTexture());*/

		// 부활 안내
		if (m_Player->m_nowHP <= 0)
		{
			for (int i = 0; i < 2; i++)
			{
				m_ResurrectionUI->m_Pos = m_ResurrectionUI->m_UIPos[i];
				m_ResurrectionUI->nowSprite = m_ResurrectionUI->sprite[i];
				m_ResurrectionUI->Render(m_Direct3D->GetDeviceContext());
				m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_ResurrectionUI->GetIndexCount(),
					UIworldMatrix, viewMatrix, orthoMatrix, m_ResurrectionUI->GetTexture());
			}
			
		}
		
		// 단축키설정
		if (m_KeyConfigUI->nowSprite.m_isRender)
		{
			for (int i = 0; i < 3; i++)
			{
				m_KeyConfigUI->m_Pos = m_KeyConfigUI->m_UIPos[i];
				m_KeyConfigUI->nowSprite = m_KeyConfigUI->sprite[i];
				m_KeyConfigUI->Render(m_Direct3D->GetDeviceContext());
				m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_KeyConfigUI->GetIndexCount(),
					UIworldMatrix, viewMatrix, orthoMatrix, m_KeyConfigUI->GetTexture());
			}

			for (int i = 0; i < 3; i++)
			{
				m_KeyConfigUI->m_Pos = m_KeyConfigUI->m_UIPos[i + 3];
				m_KeyConfigUI->nowSprite = m_KeyConfigUI->sprite[2];
				m_KeyConfigUI->nowSprite.m_startBitmapX = i * 40;
				m_KeyConfigUI->nowSprite.m_startBitmapY = 245;
				m_KeyConfigUI->nowSprite.m_bitmapWidth = m_KeyConfigUI->nowSprite.m_bitmapHeight = 32;
				m_KeyConfigUI->Render(m_Direct3D->GetDeviceContext());
				m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_KeyConfigUI->GetIndexCount(),
					UIworldMatrix, viewMatrix, orthoMatrix, m_KeyConfigUI->GetTexture());
			}
		}
	#pragma endregion

	//m_Direct3D->FrameCheck;

	m_Direct3D->TurnZBufferOn();
	
	m_Direct3D->EndScene();

	return true;
}
