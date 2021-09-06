#pragma once

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class D3DClass;
class CameraClass;

class TextureShaderClass;

class CollisionClass;
class LineShaderClass;

//class DamageClass;

//class EnemyTailClass;
//class EnemyPoisonClass;
//class EnemyObstacleClass;

class BackgroundClass;

class PlayerHPClass;
class EnemyHPClass;
class ResurrectionUIClass;
class DeathCountUIClass;
class KeyConfigUIClass;
class NoticeClass;

class ObjectPoolClass;
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int, int, unsigned char[256], float);
	bool Render(float);

private:
	D3DClass* m_Direct3D = nullptr;
	CameraClass* m_Camera = nullptr;

	TextureShaderClass* m_TextureShader = nullptr;
	LineShaderClass* m_LineShader = nullptr;

	CollisionClass* m_Collision = nullptr;
	//ObjectPoolClass* obPool[5] = { nullptr };
	
	//DamageClass* m_hitDamage[15] = { nullptr };
	//DamageClass* m_attackDamage[15] = { nullptr };

	PlayerClass* m_Player = nullptr;
	EnemyClass* m_Enemy = nullptr;
	//EnemyTailClass* m_EnemyTail[3] = { nullptr };
	//EnemyPoisonClass* m_EnemyPoison[24] = { nullptr };
	//EnemyObstacleClass* m_EnemyObstacle[8] = { nullptr };

	BackgroundClass* m_Background = nullptr;

	PlayerHPClass* m_PlayerHPBar = nullptr;
	EnemyHPClass* m_EnemyHPBar = nullptr;
	ResurrectionUIClass* m_ResurrectionUI = nullptr;
	DeathCountUIClass* m_DeathCountUI[2] = { nullptr };
	KeyConfigUIClass* m_KeyConfigUI = nullptr;
	NoticeClass* m_Notice[3] = { nullptr };

	//XMFLOAT2 m_mousePosition;
	int m_mousePosX = 0, m_mousePosY = 0;

	//int m_MouseClick;
	//unsigned char m_keyState[256] = { 0, };

	int m_screenWidth = 0;
	int m_screenHeight = 0;
	int m_hitRenderCount = 0;
	int m_attackRenderCount = 0;

};