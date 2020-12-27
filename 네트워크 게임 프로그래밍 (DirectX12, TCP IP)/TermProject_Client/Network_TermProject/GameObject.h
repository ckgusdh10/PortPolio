#pragma once
#include "Mesh.h"
#include "Camera.h"
class CShader;

class CGameObject
{

	int m_nReferences = 0;
protected:
	XMFLOAT4X4 m_xmf4x4World;
	CMesh *m_pMesh = NULL;
	CShader *m_pShader = NULL;
	BoundingOrientedBox      m_xmOOBB;
	BoundingOrientedBox      m_xmOOBBTransformed;

	XMFLOAT3 m_xmf3RotationAxis;
	float m_fRotationSpeed;
	bool isActive = true;
	float m_fMovingSpeed;
public:
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList);

	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();
	
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 xmf3Position);

	void setRotate(XMFLOAT3X3& rot) {
		m_xmf4x4World._31 = rot._11;
		m_xmf4x4World._32 = rot._12;
		m_xmf4x4World._33 = rot._13;

		m_xmf4x4World._21 = rot._21;
		m_xmf4x4World._22 = rot._22;
		m_xmf4x4World._23 = rot._23;

		m_xmf4x4World._11 = rot._31;
		m_xmf4x4World._12 = rot._32;
		m_xmf4x4World._13 = rot._33;
	};

	XMFLOAT3X3& getRotate()
	{
		XMFLOAT3X3 rot;

		rot._11 = m_xmf4x4World._11;
		rot._12 = m_xmf4x4World._12;
		rot._13 = m_xmf4x4World._13;

		rot._21 = m_xmf4x4World._21;
		rot._22 = m_xmf4x4World._22;
		rot._23 = m_xmf4x4World._23;

		rot._31 = m_xmf4x4World._31;
		rot._32 = m_xmf4x4World._32;
		rot._33 = m_xmf4x4World._33;

		return rot;
	};
	void onPrepareRender() {
		XMMATRIX mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
		m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
	};
	void MoveStrafe(float fDistance = 1.0f);
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);

	void SetOOBB(XMFLOAT3& xmCenter, XMFLOAT3& xmExtents, XMFLOAT4& xmOrientation) {
		m_xmOOBBTransformed = m_xmOOBB = BoundingOrientedBox(xmCenter, xmExtents, xmOrientation);
	}

	CGameObject();
	virtual ~CGameObject();

	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);
	void Rotate(XMFLOAT3* pxmf3Axis, float fAngle);
	void Move(XMFLOAT3* vDirection, float fSpeed);
	void Move(XMFLOAT3 direction, float fSpeed);

	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

	void ReleaseUploadBuffers();
	void SetMesh(CMesh *pMesh);
	virtual void SetShader(CShader *pShader);
	virtual void Animate(float fTimeElapsed);
	virtual void OnPrepareRender();
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList
		, CCamera* pCamera);
	BoundingOrientedBox* getOOBB() { return &m_xmOOBB; }

	XMFLOAT3 m_xmf3MovingDirection;
	XMFLOAT3* getMovingDirection() { return &m_xmf3MovingDirection; }

	void SetMovingDirection(XMFLOAT3& xmf3MovingDirection) { m_xmf3MovingDirection = Vector3::Normalize(xmf3MovingDirection); }
	void SetMovingSpeed(float fSpeed) { m_fMovingSpeed = fSpeed; }

	void SetRotationSpeed(float fRotationSpeed) { m_fRotationSpeed = fRotationSpeed; }
	void SetRotationAxis(XMFLOAT3 xmf3RotationAxis) {
		m_xmf3RotationAxis =
			xmf3RotationAxis;
	}
	bool getActive() { return isActive; }
	void setActive(bool a) { isActive = a; }
};


class CEnemyBox : public CGameObject
{
	BoundingOrientedBox      m_xmOOBB;
	BoundingOrientedBox      m_xmOOBBTransformed;
	chrono::time_point<chrono::system_clock> deadTime;
public:
	CEnemyBox();
	virtual ~CEnemyBox();
	bool isDead = false;

	void SetOOBB(XMFLOAT3& xmCenter, XMFLOAT3& xmExtents, XMFLOAT4& xmOrientation) {
		m_xmOOBBTransformed = m_xmOOBB = BoundingOrientedBox(xmCenter, xmExtents, xmOrientation);
	}
	BoundingOrientedBox* getOOBB() { return &m_xmOOBB; }
	//void SetMovingRange(float fRange) { m_fMovingRange = fRange; }
	void SetPosition(float x, float y, float z);
	virtual void Animate(float fTimeElapsed, XMFLOAT3& playerPos);
	void setDeadTime(chrono::time_point<chrono::system_clock> time) { deadTime = time; }
};

class CWall : public CGameObject
{
public:
	CWall();
	~CWall();
};

class CPlane
{
	XMFLOAT4 wallVector;
public:
	CPlane() {};
	CPlane(XMFLOAT4 v) { wallVector = v; };
	~CPlane();
	XMFLOAT4& getWall() { return wallVector; }

};

class CBullet : public CGameObject
{
	XMFLOAT3 firedPosition;
	BoundingOrientedBox m_OOBB;
public:
	CBullet();
	~CBullet();

	void SetOOBB(XMFLOAT3& xmCenter, XMFLOAT3& xmExtents, XMFLOAT4& xmOrientation) {
		m_xmOOBBTransformed = m_xmOOBB = BoundingOrientedBox(xmCenter, xmExtents, xmOrientation);
	}
	void setFiredPosition(XMFLOAT3 v) { firedPosition = v; }
	float getDistance() {
		XMFLOAT3 pos(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43);
		return sqrt((pos.x - firedPosition.x)* (pos.x - firedPosition.x) +
			(pos.y - firedPosition.y)* (pos.y - firedPosition.y) +
			(pos.z - firedPosition.z)* (pos.z - firedPosition.z));
	}
	virtual void Animate(float fTimeElapsed);
};

class CParticle : public CGameObject
{
	XMFLOAT3 boomPosition;
public:
	void setBoomPosition(XMFLOAT3 v) { boomPosition = v; }
	float getDistance() {
		XMFLOAT3 pos(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43);
		return sqrt((pos.x - boomPosition.x)* (pos.x - boomPosition.x) +
			(pos.y - boomPosition.y)* (pos.y - boomPosition.y) +
			(pos.z - boomPosition.z)* (pos.z - boomPosition.z));
	}
	virtual void Animate(float fTimeElapsed);
};
class CEnemy : public CGameObject
{
	//XMFLOAT3 boomPosition;
public:
	int hp = 10;
	/*void setBoomPosition(XMFLOAT3 v) { boomPosition = v; }
	float getDistance() {
	XMFLOAT3 pos(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43);
	return sqrt((pos.x - boomPosition.x)* (pos.x - boomPosition.x) +
	(pos.y - boomPosition.y)* (pos.y - boomPosition.y) +
	(pos.z - boomPosition.z)* (pos.z - boomPosition.z));
	}
	virtual void Animate(float fTimeElapsed);*/
};

class CHPBox : public CGameObject
{
	XMFLOAT3 position;
	//CGameObject::GetPosition();
	
};

class CTimeBar : public CGameObject
{
	XMFLOAT3 position;
	//CGameObject::GetPosition();
};