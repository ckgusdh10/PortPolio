#include "Bullet.h"

Bullet::Bullet()
{
	m_xmf4x4World._41 = xmfWorld.x;
	m_xmf4x4World._42 = xmfWorld.y;
	m_xmf4x4World._43 = xmfWorld.z;

	m_xmf4x4World._11 = 1;
	m_xmf4x4World._12 = 0;
	m_xmf4x4World._13 = 0;
	m_xmf4x4World._21 = 0;
	m_xmf4x4World._22 = 1;
	m_xmf4x4World._23 = 0;
	m_xmf4x4World._31 = 0;
	m_xmf4x4World._32 = 0;
	m_xmf4x4World._33 = 1;

}

Bullet::~Bullet()
{
}

void Bullet::move()
{
	XMFLOAT3 movedPos = XMFLOAT3(xmfWorld.x + xmfMovingDir.x * Speed,
		xmfWorld.y + xmfMovingDir.y * Speed,
		xmfWorld.z + xmfMovingDir.z * Speed);

	xmfWorld = movedPos;

	m_xmf4x4World._41 = xmfWorld.x;
	m_xmf4x4World._42 = xmfWorld.y;
	m_xmf4x4World._43 = xmfWorld.z;

	m_xmOOBBTransformed.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
	XMStoreFloat4(&m_xmOOBBTransformed.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBBTransformed.Orientation)));
}

float Bullet::getDistance()
{
	return sqrt((xmfWorld.x - xmfFiredPos.x)* (xmfWorld.x - xmfFiredPos.x) +
		(xmfWorld.y - xmfFiredPos.y)* (xmfWorld.y - xmfFiredPos.y) +
		(xmfWorld.z - xmfFiredPos.z)* (xmfWorld.z - xmfFiredPos.z));
}