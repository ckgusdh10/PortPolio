#include "Player.h"

Player::Player()
{
	xmfLook = XMFLOAT3(0.0f, 0.0f, 1.0f);
	xmfRight = XMFLOAT3(1.0f, 0.0f, 0.0f);
	xmfUp = XMFLOAT3(0.0f, 1.0f, 0.0f);

	m_xmf4x4World._11 = xmfRight.x;
	m_xmf4x4World._12 = 0;
	m_xmf4x4World._13 = 0;
	m_xmf4x4World._21 = 0;
	m_xmf4x4World._22 = 1;
	m_xmf4x4World._23 = 0;
	m_xmf4x4World._31 = 0;
	m_xmf4x4World._32 = 0;
	m_xmf4x4World._33 = 1;

	SetOOBB(XMFLOAT3(0, 0, 0), XMFLOAT3(10.0f, 2.0f, 10.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}

void Player::setPosition(XMFLOAT3 pos)
{
	xmfWorld = pos;
	m_xmf4x4World._41 = xmfWorld.x;
	m_xmf4x4World._42 = xmfWorld.y;
	m_xmf4x4World._43 = xmfWorld.z;
	
	m_xmOOBBTransformed.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
	XMStoreFloat4(&m_xmOOBBTransformed.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBBTransformed.Orientation)));
}

void Player::move()
{
	if (dwDirection)
	{
		XMFLOAT3 xmf3Shift = XMFLOAT3(0, 0, 0);
		//ȭ��ǥ Ű ���衯�� ������ ���� z-�� �������� �̵�(����)�Ѵ�. ���顯�� ������ �ݴ� �������� �̵��Ѵ�.
		if (dwDirection & DIR_FORWARD)
			xmf3Shift = Vector3::Add(xmf3Shift, xmfLook, SPEED);
		if (dwDirection & DIR_BACKWARD)
			xmf3Shift = Vector3::Add(xmf3Shift, xmfLook, -SPEED);
		//ȭ��ǥ Ű ���桯�� ������ ���� x-�� �������� �̵��Ѵ�. ���硯�� ������ �ݴ� �������� �̵��Ѵ�. 
		if (dwDirection & DIR_RIGHT)
			xmf3Shift = Vector3::Add(xmf3Shift, xmfRight, SPEED);
		if (dwDirection & DIR_LEFT)
			xmf3Shift = Vector3::Add(xmf3Shift, xmfRight, -SPEED);
		//�÷��̾ ���� ��ġ ���Ϳ��� xmf3Shift ���͸�ŭ �̵��Ѵ�. 

		XMFLOAT3 movedPos = XMFLOAT3(xmfWorld.x + xmf3Shift.x * SPEED,
			xmfWorld.y + xmf3Shift.y * SPEED,
			xmfWorld.z + xmf3Shift.z * SPEED);

		setPosition(movedPos);
		m_xmOOBBTransformed.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
		XMStoreFloat4(&m_xmOOBBTransformed.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBBTransformed.Orientation)));

	}
}

void Player::rotate()
{
	float cxDelta = 0.0f, cyDelta = 0.0f;
	if (dwKey & DIR_RIGHT)
		cxDelta += 5.0f;
	if (dwKey & DIR_LEFT)
		cxDelta -= 5.0f;
	//��Page Up���� ������ ���� y-�� �������� �̵��Ѵ�. ��Page Down���� ������ �ݴ� �������� �̵��Ѵ�.
	if (dwKey & DIR_UP)
		cyDelta -= 5.0f;
	if (dwKey & DIR_DOWN)
		cyDelta += 5.0f;

	rotate(cyDelta, cxDelta, 0.0f);
	/*m_xmOOBBTransformed.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
	XMStoreFloat4(&m_xmOOBBTransformed.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBBTransformed.Orientation)));*/
}

void Player::rotate(float x, float y, float z)
{
	if (x != 0.0f)
	{
		XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&xmfRight),
			XMConvertToRadians(x));
		xmfLook = Vector3::TransformNormal(xmfLook, xmmtxRotate);
		xmfUp = Vector3::TransformNormal(xmfUp, xmmtxRotate);
	}
	if (y != 0.0f)
	{
		XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&xmfUp),
			XMConvertToRadians(y));
		xmfLook = Vector3::TransformNormal(xmfLook, xmmtxRotate);
		xmfRight = Vector3::TransformNormal(xmfRight, xmmtxRotate);
	}
	if (z != 0.0f)
	{
		XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&xmfLook),
			XMConvertToRadians(z));
		xmfUp = Vector3::TransformNormal(xmfUp, xmmtxRotate);
		xmfRight = Vector3::TransformNormal(xmfRight, xmmtxRotate);
	}
	//}
	/*ȸ������ ���� �÷��̾��� ���� x-��, y-��, z-���� ���� �������� ���� �� �����Ƿ� z-��(LookAt ����)�� ������
	�� �Ͽ� ���� �����ϰ� �������Ͱ� �ǵ��� �Ѵ�.*/
	xmfLook = Vector3::Normalize(xmfLook);
	xmfRight = Vector3::CrossProduct(xmfUp, xmfLook, true);
	xmfUp = Vector3::CrossProduct(xmfLook, xmfRight, true);
	makeRotate();
}

void Player::makeRotate()
{
	xmfRotate._11 = xmfLook.x;
	xmfRotate._12 = xmfLook.y;
	xmfRotate._13 = xmfLook.z;

	xmfRotate._21 = xmfUp.x;
	xmfRotate._22 = xmfUp.y;
	xmfRotate._23 = xmfUp.z;

	xmfRotate._31 = xmfRight.x;
	xmfRotate._32 = xmfRight.y;
	xmfRotate._33 = xmfRight.z;

	m_xmf4x4World._11 = xmfRotate._31;
	m_xmf4x4World._12 = xmfRotate._32;
	m_xmf4x4World._13 = xmfRotate._33;
	m_xmf4x4World._21 = xmfRotate._21;
	m_xmf4x4World._22 = xmfRotate._22;
	m_xmf4x4World._23 = xmfRotate._23;
	m_xmf4x4World._31 = xmfRotate._11;
	m_xmf4x4World._32 = xmfRotate._12;
	m_xmf4x4World._33 = xmfRotate._13;

	m_xmOOBBTransformed.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
	XMStoreFloat4(&m_xmOOBBTransformed.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBBTransformed.Orientation)));
}

void Player::setRotate(XMFLOAT3X3 ir)
{
	xmfRotate = ir;
	m_xmf4x4World._11 = xmfRotate._31;
	m_xmf4x4World._12 = xmfRotate._32;
	m_xmf4x4World._13 = xmfRotate._33;
	m_xmf4x4World._21 = xmfRotate._21;
	m_xmf4x4World._22 = xmfRotate._22;
	m_xmf4x4World._23 = xmfRotate._23;
	m_xmf4x4World._31 = xmfRotate._11;
	m_xmf4x4World._32 = xmfRotate._12;
	m_xmf4x4World._33 = xmfRotate._13;
}
