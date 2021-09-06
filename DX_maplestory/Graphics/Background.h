#pragma once

class TextureClass;
class BackgroundClass
{
private:
	struct VertexType
	{
		XMFLOAT2 position;
		XMFLOAT2 texture;
	};

	struct IndexType
	{
		DWORD A, B, C;
	};
public:
	BackgroundClass();
	BackgroundClass(const BackgroundClass&);
	~BackgroundClass();

	bool Initialize(ID3D11Device*, LPCWSTR, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
	static BackgroundClass* Instance()
	{
		static BackgroundClass instance;
		return &instance;
	}
public:
	ID3D11Device* m_device = nullptr;
	static float m_screenLeft, m_screenRight;

private:

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext*);
	void RenderBuffers(ID3D11DeviceContext*);
	bool LoadTexture(ID3D11Device*, LPCWSTR);
	void ReleaseTexture();

private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	TextureClass* m_Texture = nullptr;

	int m_vertexCount = 0;
	int m_indexCount = 0;

	int m_bitmapWidth = 0;
	int m_bitmapHeight = 0;
};