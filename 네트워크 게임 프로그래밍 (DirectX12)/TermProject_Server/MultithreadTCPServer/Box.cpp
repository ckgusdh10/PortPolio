#include "Box.h"



Box::Box()
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


Box::~Box()
{
}

void Box::move()
{
	uniform_real_distribution<> pos(-100.0f, 100.0f);

	default_random_engine dre;

	if (!isActive)
	{
		auto now = chrono::system_clock::now();
		auto diff = now - deadTime;
		auto msec = chrono::duration_cast<chrono::milliseconds>(diff);

		if (msec.count() >= 5000)
		{
			m_xmf4x4World._41 = pos(dre);
			m_xmf4x4World._42 = pos(dre);
			m_xmf4x4World._43 = pos(dre);
			isActive = true;
		}
	}
	else
	{
		XMFLOAT3 moved = XMFLOAT3(xmfWorld.x + xmfMovingDir.x* Speed* 0.2f,
			xmfWorld.y + xmfMovingDir.y* Speed* 0.2f,
			xmfWorld.z + xmfMovingDir.z* Speed* 0.2f);

		xmfWorld = moved;
		m_xmf4x4World._41 = xmfWorld.x;
		m_xmf4x4World._42 = xmfWorld.y;
		m_xmf4x4World._43 = xmfWorld.z;

		movedDistance += Speed *0.2f;

		m_xmOOBBTransformed.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
		XMStoreFloat4(&m_xmOOBBTransformed.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBBTransformed.Orientation)));

		if (movedDistance > movingDistance)
		{
			movedDistance = 0.0f;
			setMovingDirection(XMFLOAT3(-xmfMovingDir.x, -xmfMovingDir.y, -xmfMovingDir.z));
		}
	}
}

float Box::getDistance()
{
	return sqrt((xmfWorld.x - xmfFirstWorld.x)* (xmfWorld.x - xmfFirstWorld.x) +
		(xmfWorld.y - xmfFirstWorld.y)* (xmfWorld.y - xmfFirstWorld.y) +
		(xmfWorld.z - xmfFirstWorld.z)* (xmfWorld.z - xmfFirstWorld.z));

}

void Box::setPosition(XMFLOAT3 pos)
{
	xmfWorld = pos;
	m_xmf4x4World._41 = xmfWorld.x;
	m_xmf4x4World._42 = xmfWorld.y;
	m_xmf4x4World._43 = xmfWorld.z;
}

void Box::setMovingDirection(XMFLOAT3 Axis)
{
	xmfMovingDir = Vector3::Normalize(Axis);

}