#include "../Header/stdafx.h"
#include "cameraclass.h"


CameraClass::CameraClass()
{
	m_viewMatrix = XMMATRIX();
	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
}


CameraClass::CameraClass(const CameraClass& other)
{
	m_viewMatrix = XMMATRIX();
	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	if (PlayerClass::Instance()->m_Pos.x <= BackgroundClass::Instance()->m_screenLeft + 1366 / 2)
	{
		m_position.x = BackgroundClass::Instance()->m_screenLeft + 1366 / 2;
	}
	else if (PlayerClass::Instance()->m_Pos.x >= -BackgroundClass::Instance()->m_screenLeft - 1366 / 2 - 40)
	{
		m_position.x = -BackgroundClass::Instance()->m_screenLeft - 1366 / 2 - 40;
	}
	else
	{
		m_position.x = x;
	}

	m_position.y = y;
	m_position.z = z;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

POINT CameraClass::ScreenToWorldPoint(XMMATRIX ortho, POINT pos)
{
	float pointX = ((2.0f * (float)pos.x) / (float)1366);
	float pointY = ((-2.0f * (float)pos.y) / (float)768);

	XMFLOAT3X3 ortho4;
	XMStoreFloat3x3(&ortho4, ortho);

	// View port에서 투영행렬로 변환하기 위해 X,Y에 영향을 미친 1행 1열과 2행 2열을 나눔
	pointX /= ortho4._11;
	pointY /= ortho4._22;

	XMMATRIX view, inverseView;
	GetViewMatrix(view);
	inverseView = XMMatrixInverse(nullptr, view);
	XMFLOAT3X3 inverseView4;
	XMStoreFloat3x3(&inverseView4, inverseView);

	XMFLOAT3 direction, origin;// , rayOrigin, rayDirection;
	direction.x = (pointX * inverseView4._11) + (pointY * inverseView4._21);// +inverseView4._31;
	direction.y = (pointX * inverseView4._12) + (pointY * inverseView4._22);// +inverseView4._32;
	//direction.z = (pointX * inverseView4._13) + (pointY * inverseView4._23) + inverseView4._33;

	origin = GetPosition();

	POINT WorldPoint;
	WorldPoint.x = direction.x + origin.x; WorldPoint.y = -(direction.y + origin.y);

	return WorldPoint;
}


XMFLOAT3 CameraClass::GetPosition()
{
	return m_position;
}


XMFLOAT3 CameraClass::GetRotation()
{
	return m_rotation;
}


void CameraClass::Render()
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;
	

	// 위쪽을 가리키는 벡터를 설정합니다.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// XMVECTOR 구조체에 로드한다.
	upVector = XMLoadFloat3(&up);

	// 3D월드에서 카메라의 위치를 ​​설정합니다.
	position = m_position;

	// XMVECTOR 구조체에 로드한다.
	positionVector = XMLoadFloat3(&position);

	// 기본적으로 카메라가 찾고있는 위치를 설정합니다.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// XMVECTOR 구조체에 로드한다.
	lookAtVector = XMLoadFloat3(&lookAt);

	// yaw (Y 축), pitch (X 축) 및 roll (Z 축)의 회전값을 라디안 단위로 설정합니다.
	pitch = m_rotation.x * 0.0174532925f;
	yaw = m_rotation.y * 0.0174532925f;
	roll = m_rotation.z * 0.0174532925f;

	//  yaw, pitch, roll 값을 통해 회전 행렬을 만듭니다.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// lookAt 및 up 벡터를 회전 행렬로 변형하여 뷰가 원점에서 올바르게 회전되도록 합니다.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// 회전 된 카메라 위치를 뷰어 위치로 변환합니다.
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	// 마지막으로 세 개의 업데이트 된 벡터에서 뷰 행렬을 만듭니다.
	m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
}


void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}