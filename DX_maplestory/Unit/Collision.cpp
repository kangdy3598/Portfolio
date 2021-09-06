#include "../Header/stdafx.h"
#include "Collision.h"

CollisionClass::CollisionClass()
{
}
CollisionClass::~CollisionClass()
{
}


bool CollisionClass::Initialize(ID3D11Device* device)
{
	return InitializeBuffers(device);
}

void CollisionClass::Shutdown()
{
	// 버텍스 및 인덱스 버퍼를 종료합니다.
	ShutdownBuffers();
}

int CollisionClass::GetIndexCount()
{
	return m_indexCount;
}

void CollisionClass::Render(ID3D11DeviceContext* deviceContext, XMFLOAT2 boundingBox[2], XMFLOAT4 Color)
{
	for (int i = 0; i < 2; i++)
	{
		m_renderBoundingBox[i] = boundingBox[i];
	}
	//m_renderBoundingBox = boundingBox;

	m_renderColor = Color;
	UpdateBuffers(deviceContext);
	RenderBuffers(deviceContext);
}

bool CollisionClass::InitializeBuffers(ID3D11Device* device)
{
	m_indexCount = 8;
	m_vertexCount = 4;

	// 정점 배열을 만듭니다.
	VertexCollisionType* vertices = new VertexCollisionType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	memset(vertices, 0, (sizeof(VertexCollisionType) * m_vertexCount));
	// 인덱스 배열을 만듭니다.
	unsigned long* indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	indices[0] = 0; indices[1] = 3;
	indices[2] = 3; indices[3] = 1;
	indices[4] = 1; indices[5] = 2;
	indices[6] = 2; indices[7] = 0;

	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexCollisionType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// subresource 구조에 정점 데이터에 대한 포인터를 제공합니다.
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// 이제 정점 버퍼를 만듭니다.
	if (FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexCollision)))
	{
		return false;
	}

	// 정적 인덱스 버퍼의 구조체를 설정합니다.
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// 인덱스 데이터를 가리키는 보조 리소스 구조체를 작성합니다.
	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// 인덱스 버퍼를 생성합니다.
	if (FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexCollision)))
	{
		return false;
	}

	// 생성되고 값이 할당된 정점 버퍼와 인덱스 버퍼를 해제합니다.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void CollisionClass::ShutdownBuffers()
{
	// 인덱스 버퍼를 해제합니다.
	if (m_indexCollision)
	{
		m_indexCollision->Release();
		m_indexCollision = 0;
	}

	// 정점 버퍼를 해제합니다.
	if (m_vertexCollision)
	{
		m_vertexCollision->Release();
		m_vertexCollision = 0;
	}
}

void CollisionClass::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
	VertexCollisionType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexCollisionType* verticesPtr;
	HRESULT result;

	vertices = new VertexCollisionType[m_vertexCount];
	if (!vertices)
	{
		return;
	}

	// 정점 배열에 데이터를 설정합니다.
	vertices[0].position = XMFLOAT2(m_renderBoundingBox[0].x, m_renderBoundingBox[0].y);
	vertices[1].position = XMFLOAT2(m_renderBoundingBox[1].x, m_renderBoundingBox[1].y);
	vertices[2].position = XMFLOAT2(m_renderBoundingBox[0].x, m_renderBoundingBox[1].y);
	vertices[3].position = XMFLOAT2(m_renderBoundingBox[1].x, m_renderBoundingBox[0].y);

	for (int i = 0; i < 4; i++)
	{
		vertices[i].color = m_renderColor;
	}

	result = deviceContext->Map(m_vertexCollision, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return;
	}

	verticesPtr = (VertexCollisionType*)mappedResource.pData;

	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexCollisionType) * m_vertexCount));

	deviceContext->Unmap(m_vertexCollision, 0);

	delete[] vertices;
	vertices = 0;
}

void CollisionClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	// 정점 버퍼의 단위와 오프셋을 설정합니다.
	unsigned int stride = sizeof(VertexCollisionType);
	unsigned int offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexCollision, &stride, &offset);

	deviceContext->IASetIndexBuffer(m_indexCollision, DXGI_FORMAT_R32_UINT, 0);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
}
