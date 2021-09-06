#include "../Header/stdafx.h"
#include "TextureClass.h"
#include "Background.h"

float BackgroundClass::m_screenLeft, BackgroundClass::m_screenRight;
BackgroundClass::BackgroundClass()
{
}


BackgroundClass::BackgroundClass(const BackgroundClass& other)
{
}


BackgroundClass::~BackgroundClass()
{
}

bool BackgroundClass::Initialize(ID3D11Device* device,  LPCWSTR textureFilename, int bitmapWidth, int bitmapHeight)
{
	m_bitmapWidth = bitmapWidth;
	m_bitmapHeight = bitmapHeight;
	if (!InitializeBuffers(device))
	{
		return false;
	}

	m_device = device;

	return LoadTexture(device, textureFilename);
}


void BackgroundClass::Shutdown()
{
	ReleaseTexture();
	ShutdownBuffers();
}


bool BackgroundClass::Render(ID3D11DeviceContext* deviceContext)
{
	if (!UpdateBuffers(deviceContext))
	{
		return false;
	}

	RenderBuffers(deviceContext);

	return true;
}
int BackgroundClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* BackgroundClass::GetTexture()
{
	return m_Texture->GetTexture();
}

bool BackgroundClass::InitializeBuffers(ID3D11Device* device)
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


void BackgroundClass::ShutdownBuffers()
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


bool BackgroundClass::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
	HRESULT result;

	float left, right, top, bottom;

	m_screenLeft = left = -m_bitmapWidth/2;
	m_screenRight = right =  m_bitmapWidth/2 + 980;

	top = m_bitmapHeight/2 + 80;
	bottom = -m_bitmapHeight/2 - 50;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	vertices[0].position = XMFLOAT2(left, top);
	vertices[0].texture = XMFLOAT2(0.0f, 0.0f);

	vertices[1].position = XMFLOAT2(right, bottom);
	vertices[1].texture = XMFLOAT2(1.0f, 1.0f);

	vertices[2].position = XMFLOAT2(left, bottom);
	vertices[2].texture = XMFLOAT2(0.0f, 1.0f);

	vertices[3].position = XMFLOAT2(right, top);
	vertices[3].texture = XMFLOAT2(1.0f, 0.0f);

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

void BackgroundClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool BackgroundClass::LoadTexture(ID3D11Device* device, LPCWSTR filename)
{
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	return m_Texture->Initialize(device, filename);
}


void BackgroundClass::ReleaseTexture()
{
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
}