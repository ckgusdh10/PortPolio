#pragma once
#include "stdafx.h"
#define DIR_FORWARD 0x01
#define DIR_BACKWARD 0x02
#define DIR_LEFT 0x04
#define DIR_RIGHT 0x08
#define DIR_UP 0x10
#define DIR_DOWN 0x20

#define SPEED 2.0f


class Player {
public:
	XMFLOAT3 xmfWorld;
	XMFLOAT3 xmfLook;
	XMFLOAT3 xmfRight;
	XMFLOAT3 xmfUp;
	XMFLOAT3X3 xmfRotate;
	XMFLOAT3X3 initRotate;

	BoundingOrientedBox       m_OOBB;
	BoundingOrientedBox      m_xmOOBB;
	BoundingOrientedBox      m_xmOOBBTransformed;
	XMFLOAT4X4             m_xmf4x4World;

	bool shotOnce = false;

	DWORD dwDirection;
	DWORD dwKey;

	Player();

	int hp = 10;
	bool isActive = true;
	void setPosition(XMFLOAT3 pos);

	void SetOOBB(XMFLOAT3& xmCenter, XMFLOAT3& xmExtents, XMFLOAT4& xmOrientation) {
		m_xmOOBBTransformed = m_xmOOBB = BoundingOrientedBox(xmCenter, xmExtents, xmOrientation);
	}
	BoundingOrientedBox* getOOBB() { return &m_xmOOBB; }

	void move();

	void rotate();
	void rotate(float x, float y, float z);
	void makeRotate();
	void setRotate(XMFLOAT3X3 ir);
};