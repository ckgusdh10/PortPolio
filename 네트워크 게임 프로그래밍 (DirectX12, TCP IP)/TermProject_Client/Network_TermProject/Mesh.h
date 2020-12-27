#pragma once
#include "DiffusedVertex.h"
class CMesh
{
	int m_nReferences = 0;
protected:
	ID3D12Resource *m_pd3dVertexBuffer = NULL;
	ID3D12Resource *m_pd3dVertexUploadBuffer = NULL;
	D3D12_VERTEX_BUFFER_VIEW m_d3dVertexBufferView;
	D3D12_PRIMITIVE_TOPOLOGY m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	UINT m_nSlot = 0;
	UINT m_nVertices = 0;
	UINT m_nStride = 0;
	UINT m_nOffset = 0;
	ID3D12Resource *m_pd3dIndexBuffer = NULL;
	ID3D12Resource *m_pd3dIndexUploadBuffer = NULL;
	/*인덱스 버퍼(인덱스의 배열)와 인덱스 버퍼를 위한 업로드 버퍼에 대한 인터페이스 포인터이다. 인덱스 버퍼는 정점
	버퍼(배열)에 대한 인덱스를 가진다.*/
	D3D12_INDEX_BUFFER_VIEW m_d3dIndexBufferView;
	UINT m_nIndices = 0;
	//인덱스 버퍼에 포함되는 인덱스의 개수이다. 
	UINT m_nStartIndex = 0;
	//인덱스 버퍼에서 메쉬를 그리기 위해 사용되는 시작 인덱스이다.
	int m_nBaseVertex = 0;
	//인덱스 버퍼의 인덱스에 더해질 인덱스이다. 
public:
	CMesh() {}
	CMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual ~CMesh();

	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }
	void ReleaseUploadBuffers();


	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList);
};

class CTriangleMesh : public CMesh
{
public:
	CTriangleMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual ~CTriangleMesh() { }
};

class CCubeMeshDiffused : public CMesh
{
public:
	CCubeMeshDiffused(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList, float fWidth = 2.0f, float fHeight = 2.0f, float fDepth = 2.0f);
	virtual ~CCubeMeshDiffused();
};

class CBulletMesh : public CMesh
{
public:
	CBulletMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList, float fWidth = 2.0f, float fHeight = 2.0f, float fDepth = 2.0f);
	virtual ~CBulletMesh();
};

class CAirplaneMeshDiffused : public CMesh
{
public:
	CAirplaneMeshDiffused(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList, float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 4.0f,
		XMFLOAT4 xmf4Color = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.0f));
	virtual ~CAirplaneMeshDiffused();
};

class CWallMeshDiffused : public CMesh
{
public:
	CWallMeshDiffused(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList, float fWidth = 400.0f, float fHeight = 400.0f, float fDepth = 800.0f);
	virtual ~CWallMeshDiffused();
};
class CParticleMesh : public CMesh
{
public:
	CParticleMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList, float fWidth = 400.0f, float fHeight = 400.0f, float fDepth = 800.0f);
	virtual ~CParticleMesh();
};

class CHPBoxMesh : public CMesh
{
public:
	CHPBoxMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList, float fWidth = 400.0f, float fHeight = 400.0f, float fDepth = 800.0f);
	virtual ~CHPBoxMesh();
};


class CTimeBarMesh : public CMesh
{
public:
	CTimeBarMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList, float fWidth = 400.0f, float fHeight = 400.0f, float fDepth = 800.0f);
	virtual ~CTimeBarMesh();
};


class CPlayerParticleMesh : public CMesh
{
public:
	CPlayerParticleMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList, float fWidth = 400.0f, float fHeight = 400.0f, float fDepth = 800.0f);
	virtual ~CPlayerParticleMesh();
};