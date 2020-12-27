#pragma once
#pragma comment (lib,"ws2_32")

#define SERVERIP "127.0.0.1"
#define SERVERPORT	9000
#define BUFSIZE 512
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>

#include "Timer.h"
#include "Scene.h"
#include "Camera.h"
#include "Player.h"

class CGameFramework
{
	//
	bool shotOnce = false;

	float xrot = 0.0f;
	float yrot = 0.0f;
	
	CGameTimer m_GameTimer;
	_TCHAR m_pszFrameRate[50];

	HINSTANCE m_hInstance;
	HWND m_hWnd;

	int m_nWndClientWidth;
	int m_nWndClientHeight;
	
	IDXGIFactory4* m_pdxgiFactory;
	IDXGISwapChain3* m_pdxgiSwapChain;
	ID3D12Device* m_pd3dDevice;

	bool m_bMsaa4xEnable = false;
	UINT m_nMsaa4xQualityLevels = 0;

	static const UINT m_nSwapChainBuffers = 2;

	UINT m_nSwapChainBufferIndex;

	ID3D12Resource* m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;
	UINT m_nRtvDescriptorIncrementSize;

	ID3D12Resource* m_pd3dDepthStencilBuffer;
	ID3D12DescriptorHeap* m_pd3dDsvDescriptorHeap;
	UINT m_nDsvDescriptorIncrementSize;

	ID3D12CommandQueue*	m_pd3dCommandQueue;
	ID3D12CommandAllocator* m_pd3dCommandAllocator;
	ID3D12GraphicsCommandList* m_pd3dCommandList;
	ID3D12PipelineState* m_pd3dPipelineState;

	ID3D12Fence* m_pd3dFence;
	UINT64 m_nFenceValues[m_nSwapChainBuffers];
	HANDLE m_hFenceEvent;

	CScene* m_pScene;

	SOCKET sock;
	int retval;
	WSADATA wsa;
	char buf[BUFSIZE];

	CBulletShader* bs = nullptr;
	CObjectsShader* os = nullptr;
	CEnemyShader* es = nullptr;
	CHPBoxShader* hs = nullptr;
	CParticleShader* ps = nullptr;
	CTimeBarShader* ts = nullptr;
	CPlayerParticleShader* pps = nullptr;


#if defined(_DEBUG)
	ID3D12Debug* m_pd3dDebugController;
#endif

public:
	//CPlayer* m_pPlayer = nullptr;
	CPlayer* m_pPlayer;

	
	POINT m_ptOldCursorPos;
	CCamera* m_pCamera = nullptr;
	CGameObject* m_pWalls;

	CParticle* playerParticle;

	int Time;

	CGameFramework();
	~CGameFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	void CreateSwapChain();
	void CreateDirect3DDevice();
	void CreateRtvAndDsvDescriptorHeaps();
	void CreateCommandQueueAndList();

	void CreateRenderTargetView();
	void CreateDepthStencilView();

	void BuildObjects();

	void ConnectSocket();

	void ReleaseObjects();


	void ProcessInput();
	void AnimateObjects();
	void FrameAdvance();

	void WaitForGpuComplete();

	
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);

	void Update();

	void OnResizeBackBuffers();
	void MoveToNextFrame();

};

