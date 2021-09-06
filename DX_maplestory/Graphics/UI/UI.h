#pragma once

class TextureClass;
class UIClass
{
public:
	UIClass() { };
	~UIClass() { };

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

	XMFLOAT2 m_pivot = XMFLOAT2(0, 0);
	XMFLOAT2 m_Pos = XMFLOAT2(0, 0);

	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	TextureClass* m_Texture = nullptr;

	int m_vertexCount = 0;
	int m_indexCount = 0;

	// 스프라이트 이미지 정보
	struct Sprite
	{
		ID3D11ShaderResourceView* m_img = nullptr;

		int m_startBitmapX = 0;
		int m_startBitmapY = 0;
		int m_bitmapWidth = 0;
		int m_bitmapHeight = 0;
		float m_fullSizeX = 0;
		float m_fullSizeY = 0;

		bool m_isRender = true;
	};
	Sprite* sprite = nullptr;
	Sprite nowSprite;

	Sprite LoadTexture(ID3D11Device*, LPCWSTR filename);
	bool Render(ID3D11DeviceContext*, int type = 0);
	void Shutdown();

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext*, int type = 0);
	void RenderBuffers(ID3D11DeviceContext*);
	void ReleaseTexture();

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
};