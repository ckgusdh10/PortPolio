#pragma once
#include "stdafx.h"

class Box
{
public:
	XMFLOAT3 xmfWorld;
	XMFLOAT3 xmfFirstWorld;
	XMFLOAT3 xmfMovingDir;

	BoundingOrientedBox		 m_OOBB;
	BoundingOrientedBox      m_xmOOBB;
	BoundingOrientedBox      m_xmOOBBTransformed;
	XMFLOAT4X4				 m_xmf4x4World;

	float movingDistance = 0;
	float movedDistance = 0;
	float Speed = 1.0f;
	
	Box();
	~Box();

	bool isActive = true;
	chrono::time_point<chrono::system_clock> deadTime;

	void move();
	float getDistance();
	void setPosition(XMFLOAT3 pos);
	void setMovingDirection(XMFLOAT3 Axis);


	void SetOOBB(XMFLOAT3& xmCenter, XMFLOAT3& xmExtents, XMFLOAT4& xmOrientation) {
		m_xmOOBBTransformed = m_xmOOBB = BoundingOrientedBox(xmCenter, xmExtents, xmOrientation);
	}
	BoundingOrientedBox* getOOBB() { return &m_xmOOBB; }

	void setDeadTime(chrono::time_point<chrono::system_clock> time) { deadTime = time; }
};