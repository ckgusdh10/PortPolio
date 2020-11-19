#include "stdafx.h"
#include "GameObject.h"
#include "Shader.h"

CGameObject::CGameObject()
{
	XMStoreFloat4x4(&m_xmf4x4World, XMMatrixIdentity());
	
	
}


CGameObject::~CGameObject()
{
	if (m_pMesh)
		m_pMesh->Release();
	if (m_pShader)
	{
		m_pShader->ReleaseShaderVariables();
		m_pShader->Release();
	}
}

void CGameObject::Rotate(float fPitch, float fYaw, float fRoll)
{
	XMMATRIX mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians(fPitch),
		XMConvertToRadians(fYaw), XMConvertToRadians(fRoll));
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

void CGameObject::Rotate(XMFLOAT3 * pxmf3Axis, float fAngle)
{
	XMMATRIX mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(pxmf3Axis),
		XMConvertToRadians(fAngle));
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

void CGameObject::ReleaseUploadBuffers()
{
	if (m_pMesh)
		m_pMesh->ReleaseUploadBuffers();
}

void CGameObject::SetMesh(CMesh * pMesh)
{
	if (m_pMesh)
		m_pMesh->Release();
	m_pMesh = pMesh;
	if (m_pMesh) 
		m_pMesh->AddRef();
}

void CGameObject::SetShader(CShader * pShader)
{
	if (m_pShader) m_pShader->Release();
	m_pShader = pShader;
	if (m_pShader) m_pShader->AddRef();
}

void CGameObject::Animate(float fTimeElapsed)
{

}

void CGameObject::OnPrepareRender()
{
}

void CGameObject::Render(ID3D12GraphicsCommandList * pd3dCommandList,CCamera* pCamera)
{
	OnPrepareRender();

	UpdateShaderVariables(pd3dCommandList);

	if (m_pShader)
	{
		m_pShader->UpdateShaderVariable(pd3dCommandList, &m_xmf4x4World);
		m_pShader->Render(pd3dCommandList, pCamera);
	}
	if (m_pMesh) 
		m_pMesh->Render(pd3dCommandList);
}

void CGameObject::Move(XMFLOAT3* vDirection, float fSpeed)
{
	SetPosition(m_xmf4x4World._41 + vDirection->x * fSpeed,
		m_xmf4x4World._42 + vDirection->y * fSpeed, 
		m_xmf4x4World._43 + vDirection->z * fSpeed);
}

void CGameObject::Move(XMFLOAT3 direction, float fSpeed)
{
	SetPosition(m_xmf4x4World._41 + direction.x * fSpeed,
		m_xmf4x4World._42 + direction.y * fSpeed,
		m_xmf4x4World._43 + direction.z * fSpeed);
}

CEnemyBox ::CEnemyBox()
{
	m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_fRotationSpeed = 90.0f;
	m_fMovingSpeed = 0.0f;
}

CEnemyBox::~CEnemyBox()
{
}

void CEnemyBox::SetPosition(float x, float y, float z)
{
	m_xmf4x4World._41 = x;
	m_xmf4x4World._42 = y;
	m_xmf4x4World._43 = z;
}

void CEnemyBox::Animate(float fTimeElapsed,XMFLOAT3& playerPos)
{
	uniform_real_distribution<> pos(-80.0f, 80.0f);

	default_random_engine dre;

	dre.seed((unsigned int)time(NULL));
	if (!isActive)
	{
		auto now = chrono::system_clock::now();
		auto diff = now - deadTime;
		auto msec = chrono::duration_cast<chrono::milliseconds>(diff);

		if (msec.count() >= 5000)
		{
			isActive = true;
			SetPosition(pos(dre), pos(dre), playerPos.z + (pos(dre) / 2.0f) + 300.0f);
		}
	}
	else
	{
		if (m_fRotationSpeed != 0.0f)
			CGameObject::Rotate(&m_xmf3RotationAxis, m_fRotationSpeed * 0.03f);
		if (m_fMovingSpeed != 0.0f)
		{
			CGameObject::Move(&m_xmf3MovingDirection, m_fMovingSpeed*0.005f);
		}
		if (GetPosition().z < playerPos.z)
		{
			deadTime = chrono::system_clock::now();
			isActive = false;
		}
	}

	m_xmOOBBTransformed.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
	XMStoreFloat4(&m_xmOOBBTransformed.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBBTransformed.Orientation)));
}

void CGameObject::CreateShaderVariables(ID3D12Device * pd3dDevice, ID3D12GraphicsCommandList * pd3dCommandList)
{
}

void CGameObject::UpdateShaderVariables(ID3D12GraphicsCommandList * pd3dCommandList)
{
	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_xmf4x4World)));
	//객체의 월드 변환 행렬을 루트 상수(32-비트 값)를 통하여 셰이더 변수(상수 버퍼)로 복사한다. 
	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);
}

void CGameObject::ReleaseShaderVariables()
{
}

XMFLOAT3 CGameObject::GetPosition()
{
	return XMFLOAT3(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43);
}

XMFLOAT3 CGameObject::GetLook()
{
	return XMFLOAT3(m_xmf4x4World._31, m_xmf4x4World._32, m_xmf4x4World._33);
}

XMFLOAT3 CGameObject::GetUp()
{
	return XMFLOAT3(m_xmf4x4World._21, m_xmf4x4World._22, m_xmf4x4World._23);
}

XMFLOAT3 CGameObject::GetRight()
{
	return XMFLOAT3(m_xmf4x4World._11, m_xmf4x4World._12, m_xmf4x4World._13);
}

void CGameObject::SetPosition(float x, float y, float z)
{
	m_xmf4x4World._41 = x;
	m_xmf4x4World._42 = y;
	m_xmf4x4World._43 = z;
}

void CGameObject::SetPosition(XMFLOAT3 xmf3Position)
{
	SetPosition(xmf3Position.x, xmf3Position.y, xmf3Position.z);
}

void CGameObject::MoveStrafe(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Right = GetRight();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Right, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

void CGameObject::MoveUp(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Up = GetUp();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Up, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

void CGameObject::MoveForward(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Look = GetLook();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Look, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

CWall::CWall()
{

}

CWall::~CWall()
{
}



CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}

void CBullet::Animate(float fTimeElapsed)
{
	if (m_fRotationSpeed != 0.0f)
		CGameObject::Rotate(&m_xmf3RotationAxis, m_fRotationSpeed * 0.03f);
	if (m_fMovingSpeed != 0.0f)
	{
		CGameObject::Move(&m_xmf3MovingDirection, m_fMovingSpeed*0.001f);
	}
	
	m_xmOOBBTransformed.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
	XMStoreFloat4(&m_xmOOBBTransformed.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBBTransformed.Orientation)));
}

CPlane::~CPlane()
{
}

void CParticle::Animate(float fTimeElapsed)
{

	if (m_fRotationSpeed != 0.0f)
		CGameObject::Rotate(&m_xmf3RotationAxis, m_fRotationSpeed * 0.3f);
	if (m_fMovingSpeed != 0.0f)
	{
		CGameObject::Move(&m_xmf3MovingDirection, m_fMovingSpeed*0.5f);
	}
}
