#include "../../Header/stdafx.h"
#include "../../Graphics/TextureClass.h"
#include "DeathCountUI.h"

DeathCountUIClass::DeathCountUIClass()
{
}

DeathCountUIClass::~DeathCountUIClass()
{
}

bool DeathCountUIClass::Initialize(ID3D11Device* device, LPCWSTR filename, int bitmapWidth, int bitmapHeight, int type)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}

	m_bitmapHeight = bitmapHeight;
	m_bitmapWidth = bitmapWidth;

	m_type = type;
	m_device = device;

	switch (m_type)
	{
	case 0:
		m_Pos.y = 300;
		break;
	case 1:
		m_Pos.x = 27.3f;
		m_Pos.y = 289.7f;
		break;
	}
	return LoadTexture(device, filename);
}


void DeathCountUIClass::Shutdown()
{
	ReleaseTexture();
	ShutdownBuffers();
}


bool DeathCountUIClass::Render(ID3D11DeviceContext* deviceContext, XMFLOAT2 pos)
{
	if (!UpdateBuffers(deviceContext, pos))
	{
		return false;
	}
	RenderBuffers(deviceContext);

	return true;
}
int DeathCountUIClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* DeathCountUIClass::GetTexture()
{
	return m_Texture->GetTexture();
}

bool DeathCountUIClass::InitializeBuffers(ID3D11Device* device)
{
	m_indexCount = 2;
	m_vertexCount = 4;

	VertexType* vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	memset(vertices, 0, (sizeof(VertexType) * m_vertexCount));

	unsigned long* indices = new unsigned long[m_indexCount * 3];
	if (!indices)
	{
		return false;
	}
	// 데이터로 인덱스 배열을 로드합니다.
	//for (int i = 0; i < m_indexCount; i++)
	//{
	//	indices[i] = i;
	//}
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 3; indices[5] = 1;

	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	if (FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer)))
	{
		return false;
	}

	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	if (FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer)))
	{
		return false;
	}

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void DeathCountUIClass::ShutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}

bool DeathCountUIClass::UpdateBuffers(ID3D11DeviceContext* deviceContext, XMFLOAT2 pos)
{
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
	HRESULT result;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	switch (m_type)
	{
	case 0:
		bottomTexture = 0.0f;
		break;
	case 1:
		bottomTexture = 70.0f;
		break;
	}

	float left, right, top, bottom;
	top = m_Pos.y + m_bitmapHeight / 2;
	bottom = m_Pos.y - m_bitmapHeight / 2;
	left = m_Pos.x - m_bitmapWidth / 2;
	right = m_Pos.x + m_bitmapWidth / 2;

	vertices[0].position = XMFLOAT3(left, top, 0);
	vertices[0].texture = XMFLOAT2(0.0f, bottomTexture / 256.0f);

	vertices[1].position = XMFLOAT3(right, bottom, 0);
	vertices[1].texture = XMFLOAT2(m_bitmapWidth / 256.0f, (bottomTexture + m_bitmapHeight) / 256.0f);

	vertices[2].position = XMFLOAT3(left, bottom, 0);
	vertices[2].texture = XMFLOAT2(0.0f, (bottomTexture + m_bitmapHeight) / 256.0f);

	vertices[3].position = XMFLOAT3(right, top, 0);
	vertices[3].texture = XMFLOAT2(m_bitmapWidth / 256.0f, bottomTexture / 256.0f);


	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	verticesPtr = (VertexType*)mappedResource.pData;

	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * m_vertexCount));

	deviceContext->Unmap(m_vertexBuffer, 0);

	delete[] vertices;
	vertices = 0;

	return true;
}

void DeathCountUIClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

bool DeathCountUIClass::LoadTexture(ID3D11Device* device, LPCWSTR filename)
{
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}


	return m_Texture->Initialize(device, filename);
}

void DeathCountUIClass::ReleaseTexture()
{
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
}