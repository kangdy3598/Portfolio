#include "../../Header/stdafx.h"
#include "../Unit/FSM/State.h"
#include "../../Graphics/TextureClass.h"
#include "Object.h"

void ObjectClass::ChangeState(State* pState, ObjectClass* ob)
{ 
	if (m_State != nullptr) m_State->Exit();
	
	pState->ob = ob;
	m_State = pState;

	m_animationFrameCount = 1;
	m_animationX = m_animationY = 1;
	m_isAnimationEnd = false;

	m_State->Enter();
}

bool ObjectClass::FocusOn(POINT pos)
{
	bool b_Check = true;
	b_Check &= m_hitBox[0].x <= pos.x && m_hitBox[1].x >= pos.x;
	b_Check &= m_hitBox[0].y >= pos.y && m_hitBox[1].y <= pos.y;
	return b_Check;
}

ObjectClass::Sprite ObjectClass::LoadTexture(ID3D11Device* device, LPCWSTR filename,
	int width, int height, float fullsizeX, float fullsizeY,
	int rowcount, int framecount, float frameticktime, float anchorX, float anchorY)
{
	m_Texture = new TextureClass;
	Sprite spr;
	spr.m_img = m_Texture->Init(device, filename);
	spr.m_bitmapWidth = width;
	spr.m_bitmapHeight = height;
	spr.m_fullSizeX = fullsizeX;
	spr.m_fullSizeY = fullsizeY;
	spr.m_animationRowCount = rowcount;
	spr.m_animationFrameCount = framecount;
	spr.m_animationFrameTickTime = frameticktime;
	spr.m_anchorPoint.x = anchorX;
	spr.m_anchorPoint.y = anchorY;

	if (m_Texture)
	{
		delete m_Texture;
		m_Texture = 0;
	}

	return spr;
}

bool ObjectClass::Render(ID3D11DeviceContext* deviceContext, float tickTime)
{
	if (!UpdateBuffers(deviceContext, tickTime))
	{
		return false;
	}
	RenderBuffers(deviceContext);
	return true;
}

bool ObjectClass::InitializeBuffers(ID3D11Device* device)
{
	m_indexCount = 2;
	m_vertexCount = 4;

	VertexType* vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	memset(vertices, 0, (sizeof(VertexType) * m_vertexCount));

	unsigned long* indices = new unsigned long[6];
	if (!indices)
	{
		return false;
	}

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

	//★
	if (FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer)))
	{
		MessageBox(NULL, L"버텍스 버퍼오류", L"오류", MB_OK);
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

	//★
	if (FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer)))
	{
		MessageBox(NULL, L"인덱스 버퍼오류", L"오류", MB_OK);
		return false;
	}

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void ObjectClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

bool ObjectClass::UpdateBuffers(ID3D11DeviceContext* deviceContext, float tickTime)
{
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
	HRESULT result;

	m_frameTime += tickTime;
	if (nowSprite.m_animationFrameTickTime > 0 && m_frameTime >= nowSprite.m_animationFrameTickTime)
	{
		m_frameTime = 0;
		m_frameTrigger = false;
		if (m_animationFrameCount >= nowSprite.m_animationFrameCount)
		{
			if (m_isAnimationLoop)
			{
				m_animationFrameCount = 1;
				m_animationX = m_animationY = 1;
			}
			m_isAnimationEnd = true;
		}
		else
		{
			m_isAnimationEnd = false;
			m_animationX++;
			m_animationFrameCount++;
			if (m_animationX > nowSprite.m_animationRowCount)
			{
				m_animationX = 1; ++m_animationY;
			}
		}
	}

	float left, right, top, bottom;
	left = m_Pos.x + nowSprite.m_bitmapWidth * nowSprite.m_anchorPoint.x * (m_Flip * 2 - 1);
	right = left - nowSprite.m_bitmapWidth * (m_Flip * 2 - 1);

	//★
	top = m_Pos.y + nowSprite.m_bitmapHeight *nowSprite.m_anchorPoint.y;
	bottom = m_Pos.y - nowSprite.m_bitmapHeight *(1 - nowSprite.m_anchorPoint.y);

	vertices = new VertexType[4];
	if (!vertices)
	{
		return false;
	}

	vertices[0].position = XMFLOAT2(left, top);
	vertices[0].texture = XMFLOAT2(nowSprite.m_bitmapWidth *  (m_animationX - 1) / nowSprite.m_fullSizeX,
								   nowSprite.m_bitmapHeight * (m_animationY - 1) / nowSprite.m_fullSizeY);

	vertices[1].position = XMFLOAT2(right, bottom);
	vertices[1].texture = XMFLOAT2(nowSprite.m_bitmapWidth *  m_animationX / nowSprite.m_fullSizeX,
								   nowSprite.m_bitmapHeight * m_animationY / nowSprite.m_fullSizeY);

	vertices[2].position = XMFLOAT2(left, bottom);
	vertices[2].texture = XMFLOAT2(nowSprite.m_bitmapWidth *  (m_animationX - 1) / nowSprite.m_fullSizeX,
		                           nowSprite.m_bitmapHeight * m_animationY       / nowSprite.m_fullSizeY);

	vertices[3].position = XMFLOAT2(right, top);
	vertices[3].texture = XMFLOAT2(nowSprite.m_bitmapWidth *  m_animationX       / nowSprite.m_fullSizeX,
								   nowSprite.m_bitmapHeight * (m_animationY - 1) / nowSprite.m_fullSizeY);

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

int ObjectClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* ObjectClass::GetTexture()
{
	return nowSprite.m_img;
	//return m_Texture->GetTexture();
}

void ObjectClass::Shutdown()
{
	ReleaseTexture();
	ShutdownBuffers();
	
	if (sprite)
	{
		delete[] sprite;
		sprite = 0;
	}
}

void ObjectClass::ShutdownBuffers()
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

void ObjectClass::ReleaseTexture()
{
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
}