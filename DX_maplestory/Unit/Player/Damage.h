#pragma once

class TextureClass;
class DamageClass
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
	DamageClass();
	DamageClass(const DamageClass&);
	~DamageClass();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	bool Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	bool LoadTexture(ID3D11Device*, LPCWSTR);

	static DamageClass* Instance()
	{
		static DamageClass instance;
		return &instance;
	}
public:
	ID3D11Device* m_device;

	XMFLOAT2 m_Pos;
private:

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext*);
	void RenderBuffers(ID3D11DeviceContext*);
	void ReleaseTexture();

private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	TextureClass* m_Texture = nullptr;

	int m_vertexCount = 0;
	int m_indexCount = 0;
};