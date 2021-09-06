#pragma once

class TextureClass;
class DeathCountUIClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

	struct IndexType
	{
		DWORD A, B, C;
	};

public:
	DeathCountUIClass();
	~DeathCountUIClass();

	bool Initialize(ID3D11Device*, LPCWSTR, int, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, XMFLOAT2);
	bool LoadTexture(ID3D11Device*, LPCWSTR);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	static DeathCountUIClass* Instance()
	{
		static DeathCountUIClass instance;
		return &instance;
	}
public:
	ID3D11Device* m_device;

	XMFLOAT2 m_Pos;

	int m_bitmapWidth = 0;
	int m_bitmapHeight = 0;
	int m_deathcount = 5;

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext*, XMFLOAT2);
	void RenderBuffers(ID3D11DeviceContext*);
	void ReleaseTexture();


private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	TextureClass* m_Texture = nullptr;

	int m_vertexCount = 0;
	int m_indexCount = 0;
	int m_type = 0;

	float bottomTexture = 0.0f;
};