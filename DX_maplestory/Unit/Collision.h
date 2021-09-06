#pragma once

//class PlayerClass;
//class EnemyClass;

class CollisionClass : public AlignedAllocationPolicy<16>
{
private:
	struct VertexCollisionType
	{
		XMFLOAT2 position;
		XMFLOAT4 color;
	};

public:
	CollisionClass();
	~CollisionClass();

	bool Initialize(ID3D11Device*);
	
	void Shutdown();
	void Render(ID3D11DeviceContext*, XMFLOAT2 boundingBox[2], XMFLOAT4 Color);
	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();

	void UpdateBuffers(ID3D11DeviceContext*);
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer* m_vertexCollision = nullptr;
	ID3D11Buffer* m_indexCollision = nullptr;

	XMFLOAT2 m_renderBoundingBox[2];
	XMFLOAT4 m_renderColor;

	int m_vertexCount = 0;
	int m_indexCount = 0;
};
