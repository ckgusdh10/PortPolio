#pragma once
#include "stdafx.h"

class Bullet {
public:
	XMFLOAT3 xmfWorld;
	XMFLOAT3 xmfMovingDir;
	XMFLOAT3 xmfFiredPos;
	float Speed = 15.0f;
	int tag;

	BoundingOrientedBox       m_OOBB;
	BoundingOrientedBox      m_xmOOBB;
	BoundingOrientedBox      m_xmOOBBTransformed;
	XMFLOAT4X4             m_xmf4x4World;

	Bullet();
	~Bullet();
	void move();
	float getDistance();
	void SetOOBB(XMFLOAT3& xmCenter, XMFLOAT3& xmExtents, XMFLOAT4& xmOrientation) {
		m_xmOOBBTransformed = m_xmOOBB = BoundingOrientedBox(xmCenter, xmExtents, xmOrientation);
	}
	BoundingOrientedBox* getOOBB() { return &m_xmOOBB; }

	void settag(int t) { tag = t; };
	int gettag() { return tag; }
};