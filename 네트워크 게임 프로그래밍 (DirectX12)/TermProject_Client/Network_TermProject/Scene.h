#pragma once
#include "Timer.h"
#include "Shader.h"

class CScene
{
public:
	CScene();
	~CScene();
	//씬에서 마우스와 키보드 메시지를 처리한다. 
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);
	void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList);
	void ReleaseObjects();
	bool ProcessInput(UCHAR *pKeysBuffer);
	void AnimateObjects(float fTimeElapsed, XMFLOAT3& playerPos);
	void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera* pCamera);
	void ReleaseUploadBuffers();
	//그래픽 루트 시그너쳐를 생성한다. 
	ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	ID3D12RootSignature *GetGraphicsRootSignature();
	XMFLOAT4 m_xmf4wallPlanes[4];

	CObjectsShader* getObjectShader() { return m_pObjectShader; }
	CParticleShader* getParticleShader() { return m_pParticleShader; }
	CBulletShader* getBulletShader() { return m_pBulletShader; }
	CEnemyShader* getEnemyShader() { return m_pEnemyShader; }
	CHPBoxShader* getHPBoxShader() { return m_pHPBoxShader; }
	CTimeBarShader* getTimeBarShader() { return m_pTimeBarShader; }
	CPlayerParticleShader* getPlayerParticleShader() { return m_pPlayerParticleShader; }

	void addBullet(XMFLOAT3& playerPos, XMFLOAT3& upVector);

protected:
	//씬은 게임 객체들의 집합이다. 게임 객체는 셰이더를 포함한다. 

	CObjectsShader* m_pObjectShader = nullptr;
	CWallShader* m_pWallShader = nullptr;
	CBulletShader* m_pBulletShader = nullptr;
	CParticleShader* m_pParticleShader = nullptr;
	CEnemyShader* m_pEnemyShader = nullptr;
	CHPBoxShader* m_pHPBoxShader = nullptr;
	CTimeBarShader* m_pTimeBarShader = nullptr;
	CPlayerParticleShader* m_pPlayerParticleShader = nullptr;
	int m_nShaders = 0;
	int m_nwallIndex = 2;
	ID3D12RootSignature *m_pd3dGraphicsRootSignature = NULL;
};

