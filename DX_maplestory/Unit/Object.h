#pragma once

class State;
class TextureClass;
class ObjectPoolClass;
class ObjectClass
{
public:
	ObjectClass() { };
	~ObjectClass() { };

	struct VertexType
	{
		XMFLOAT2 position;
		XMFLOAT2 texture;
	};
	struct IndexType
	{
		DWORD A, B, C;
	};

	ID3D11Device* m_device = nullptr;

	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	TextureClass* m_Texture = nullptr;

	int m_vertexCount = 0;
	int m_indexCount = 0;

	// 오브젝트 정보
	XMFLOAT2 m_pivot = XMFLOAT2(0, 0);
	XMFLOAT2 m_Pos = XMFLOAT2(0, 0);
	const wchar_t* m_objectType = nullptr;
	XMFLOAT2 m_hitBox[2] = { XMFLOAT2(0,0) };

	State* m_State = nullptr;
	void ChangeState(State*, ObjectClass*);
	bool FocusOn(POINT);

	// 스프라이트 이미지 정보
	struct Sprite
	{
		ID3D11ShaderResourceView* m_img = nullptr;

		int m_bitmapWidth = 0;
		int m_bitmapHeight = 0;
		float m_fullSizeX = 0;
		float m_fullSizeY = 0;
		int m_animationFrameCount = 0;
		int m_animationRowCount = 0;
		float m_animationFrameTickTime = 0;
		XMFLOAT2 m_anchorPoint = XMFLOAT2(0, 0);

		bool m_isRender = true;
	};
	Sprite* sprite = nullptr;

	// 애니메이션 정보
	bool m_Flip = false;
	bool m_isAnimationEnd = false;
	bool m_isAnimationLoop = true;
	int m_animationX = 1, m_animationY = 1;
	int m_animationFrameCount =1 ;
	float m_frameTime = 0;
	Sprite nowSprite;
	bool m_frameTrigger = false;

	Sprite LoadTexture(ID3D11Device*, LPCWSTR filename, int width, int height, float fullsizeX, float fullsizeY,
		int rowcount, int framecount, float frameticktime, float anchorX = 0.5f, float anchorY = 1.0f);
	bool Render(ID3D11DeviceContext*, float tickTime);
	void Shutdown();
	
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext*, float tickTime);
	void RenderBuffers(ID3D11DeviceContext*);
	void ReleaseTexture();

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
};