#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
{

}


CScene::~CScene()
{

}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return false;
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return false;
}


void CScene::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
	*pd3dCommandList)
{

	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);

	m_xmf4wallPlanes[0] = XMFLOAT4(1.0f, 0.0f, 0.0f, 100.0f);
	m_xmf4wallPlanes[1] = XMFLOAT4(-1.0f, 0.0f, 0.0f, 100.0f);
	m_xmf4wallPlanes[2] = XMFLOAT4(0.0f, 1.0f, 0.0f, 100.0f);
	m_xmf4wallPlanes[3] = XMFLOAT4(0.0f, -1.0f, 0.0f, 100.0f);

	m_pObjectShader = new CObjectsShader();
	m_pWallShader = new CWallShader();
	m_pBulletShader = new CBulletShader();
	m_pParticleShader = new CParticleShader();
	m_pEnemyShader = new CEnemyShader();
	m_pHPBoxShader = new CHPBoxShader();
	m_pTimeBarShader = new CTimeBarShader();
	m_pPlayerParticleShader = new CPlayerParticleShader();

	m_nShaders = 5;
	m_pObjectShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, 0);
	m_pWallShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, 1);
	m_pBulletShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, 0);
	m_pParticleShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, 0);
	m_pEnemyShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, 0);
	m_pHPBoxShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, 0);
	m_pTimeBarShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, 0);
	m_pPlayerParticleShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, 0);


	m_pObjectShader->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pWallShader->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pBulletShader->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pParticleShader->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pEnemyShader->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pHPBoxShader->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pTimeBarShader->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pPlayerParticleShader->BuildObjects(pd3dDevice, pd3dCommandList);
}




void CScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature)
		m_pd3dGraphicsRootSignature->Release();


	m_pObjectShader->ReleaseShaderVariables();
	m_pWallShader->ReleaseShaderVariables();
	m_pBulletShader->ReleaseShaderVariables();
	m_pParticleShader->ReleaseShaderVariables();
	m_pEnemyShader->ReleaseShaderVariables();
	m_pHPBoxShader->ReleaseShaderVariables();
	m_pTimeBarShader->ReleaseShaderVariables();


	m_pObjectShader->ReleaseObjects();
	m_pWallShader->ReleaseObjects();
	m_pBulletShader->ReleaseObjects();
	m_pParticleShader->ReleaseObjects();
	m_pEnemyShader->ReleaseObjects();
	m_pHPBoxShader->ReleaseObjects();
	m_pTimeBarShader->ReleaseObjects();
}

bool CScene::ProcessInput(UCHAR * pKeysBuffer)
{
	return false;
}



void CScene::AnimateObjects(float fTimeElapsed, XMFLOAT3& playerPos)
{
	m_pParticleShader->AnimateObjects(fTimeElapsed);
	m_pPlayerParticleShader->AnimateObjects(fTimeElapsed);
}

void CScene::Render(ID3D12GraphicsCommandList * pd3dCommandList, CCamera* pCamera)
{
	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	pCamera->UpdateShaderVariables(pd3dCommandList);

	//for (int i = 0; i < m_nShaders; i++) 
	//{
	//	m_pShaders[i]->Render(pd3dCommandList, pCamera);
	//}

	m_pObjectShader->Render(pd3dCommandList, pCamera);
	m_pWallShader->Render(pd3dCommandList, pCamera);
	m_pBulletShader->Render(pd3dCommandList, pCamera);
	m_pParticleShader->Render(pd3dCommandList, pCamera);
	m_pEnemyShader->Render(pd3dCommandList, pCamera);
	m_pHPBoxShader->Render(pd3dCommandList, pCamera);
	m_pTimeBarShader->Render(pd3dCommandList, pCamera);
	m_pPlayerParticleShader->Render(pd3dCommandList, pCamera);
}

void CScene::ReleaseUploadBuffers()
{
	//for (int i = 0; i < m_nShaders; i++)
	//	m_pShaders[i]->ReleaseUploadBuffers();
	m_pObjectShader->ReleaseUploadBuffers();
	m_pWallShader->ReleaseUploadBuffers();
	m_pBulletShader->ReleaseUploadBuffers();
	m_pParticleShader->ReleaseUploadBuffers();
}

ID3D12RootSignature * CScene::CreateGraphicsRootSignature(ID3D12Device * pd3dDevice)
{
	ID3D12RootSignature *pd3dGraphicsRootSignature = NULL;
	D3D12_ROOT_PARAMETER pd3dRootParameters[2];
	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[0].Constants.Num32BitValues = 16;
	pd3dRootParameters[0].Constants.ShaderRegister = 0;
	pd3dRootParameters[0].Constants.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[1].Constants.Num32BitValues = 32;
	pd3dRootParameters[1].Constants.ShaderRegister = 1;
	pd3dRootParameters[1].Constants.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = 0;
	d3dRootSignatureDesc.pStaticSamplers = NULL;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;
	ID3DBlob *pd3dSignatureBlob = NULL;
	ID3DBlob *pd3dErrorBlob = NULL;
	::D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1,
		&pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(),
		pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void
			**)&pd3dGraphicsRootSignature);
	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();
	return(pd3dGraphicsRootSignature);
}

ID3D12RootSignature * CScene::GetGraphicsRootSignature()
{
	return(m_pd3dGraphicsRootSignature);
}

void CScene::addBullet(XMFLOAT3& playerPos, XMFLOAT3& upVector)
{
	m_pBulletShader->addBullet(playerPos);
}
