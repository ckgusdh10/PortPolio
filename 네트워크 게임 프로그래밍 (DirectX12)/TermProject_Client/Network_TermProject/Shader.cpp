#include "stdafx.h"
#include "Shader.h"


CShader::CShader()
{

}


CShader::~CShader()
{
	if (m_ppd3dPipelineStates)
	{
		for (int i = 0; i < m_nPipelineStates; i++) if (m_ppd3dPipelineStates[i])
			m_ppd3dPipelineStates[i]->Release();
		delete[] m_ppd3dPipelineStates;
	}
}

D3D12_INPUT_LAYOUT_DESC CShader::CreateInputLayout()
{
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = NULL;
	d3dInputLayoutDesc.NumElements = 0;
	return(d3dInputLayoutDesc);
}

D3D12_RASTERIZER_DESC CShader::CreateRasterizerState_CullBack()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	d3dRasterizerDesc.FrontCounterClockwise = FALSE;
	d3dRasterizerDesc.DepthBias = 0;
	d3dRasterizerDesc.DepthBiasClamp = 0.0f;
	d3dRasterizerDesc.SlopeScaledDepthBias = 0.0f;
	d3dRasterizerDesc.DepthClipEnable = TRUE;
	d3dRasterizerDesc.MultisampleEnable = FALSE;
	d3dRasterizerDesc.AntialiasedLineEnable = FALSE;
	d3dRasterizerDesc.ForcedSampleCount = 0;
	d3dRasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	return(d3dRasterizerDesc);
}

D3D12_RASTERIZER_DESC CShader::CreateRasterizerState_CullFront()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_FRONT;
	d3dRasterizerDesc.FrontCounterClockwise = FALSE;
	d3dRasterizerDesc.DepthBias = 0;
	d3dRasterizerDesc.DepthBiasClamp = 0.0f;
	d3dRasterizerDesc.SlopeScaledDepthBias = 0.0f;
	d3dRasterizerDesc.DepthClipEnable = TRUE;
	d3dRasterizerDesc.MultisampleEnable = FALSE;
	d3dRasterizerDesc.AntialiasedLineEnable = FALSE;
	d3dRasterizerDesc.ForcedSampleCount = 0;
	d3dRasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	return(d3dRasterizerDesc);
}

D3D12_BLEND_DESC CShader::CreateBlendState()
{
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	return(d3dBlendDesc);
}

D3D12_DEPTH_STENCIL_DESC CShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	d3dDepthStencilDesc.DepthEnable = TRUE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0x00;
	d3dDepthStencilDesc.StencilWriteMask = 0x00;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	return(d3dDepthStencilDesc);
}

D3D12_SHADER_BYTECODE CShader::CreateVertexShader(ID3DBlob ** ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;
	return(d3dShaderByteCode);
}

D3D12_SHADER_BYTECODE CShader::CreatePixelShader(ID3DBlob ** ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;
	return(d3dShaderByteCode);
}

D3D12_SHADER_BYTECODE CShader::CompileShaderFromFile(WCHAR * pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderProfile, ID3DBlob ** ppd3dShaderBlob)
{
	UINT nCompileFlags = 0;
#if defined(_DEBUG)
	nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	::D3DCompileFromFile(pszFileName, NULL, NULL, pszShaderName, pszShaderProfile,
		nCompileFlags, 0, ppd3dShaderBlob, NULL);
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
	d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();
	return(d3dShaderByteCode);
}

void CShader::CreateShader(ID3D12Device * pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature, int cullState)
{
	ID3DBlob *pd3dVertexShaderBlob = NULL, *pd3dPixelShaderBlob = NULL;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS = CreateVertexShader(&pd3dVertexShaderBlob);
	d3dPipelineStateDesc.PS = CreatePixelShader(&pd3dPixelShaderBlob);
	if (cullState == 0)
		d3dPipelineStateDesc.RasterizerState = CreateRasterizerState_CullBack();
	else
		d3dPipelineStateDesc.RasterizerState = CreateRasterizerState_CullFront();
	d3dPipelineStateDesc.BlendState = CreateBlendState();
	d3dPipelineStateDesc.DepthStencilState = CreateDepthStencilState();
	d3dPipelineStateDesc.InputLayout = CreateInputLayout();
	d3dPipelineStateDesc.SampleMask = UINT_MAX;
	d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	d3dPipelineStateDesc.NumRenderTargets = 1;
	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc,
		__uuidof(ID3D12PipelineState), (void **)&m_ppd3dPipelineStates[0]);
	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();
	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[]
		d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}

void CShader::CreateShaderVariables(ID3D12Device * pd3dDevice, ID3D12GraphicsCommandList * pd3dCommandList)
{
}

void CShader::UpdateShaderVariables(ID3D12GraphicsCommandList * pd3dCommandList)
{

}

void CShader::ReleaseShaderVariables()
{
}

void CShader::UpdateShaderVariable(ID3D12GraphicsCommandList * pd3dCommandList, XMFLOAT4X4 * pxmf4x4World)
{
}


void CShader::OnPrepareRender(ID3D12GraphicsCommandList * pd3dCommandList)
{
	pd3dCommandList->SetPipelineState(m_ppd3dPipelineStates[0]);
}

void CShader::Render(ID3D12GraphicsCommandList * pd3dCommandList, CCamera * pCamera)
{
	OnPrepareRender(pd3dCommandList);
}

CPlayerShader::CPlayerShader()
{
}

CPlayerShader::~CPlayerShader()
{
}

D3D12_INPUT_LAYOUT_DESC CPlayerShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CPlayerShader::CreateVertexShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CPlayerShader::CreatePixelShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CPlayerShader::CreateShader(ID3D12Device * pd3dDevice, ID3D12RootSignature * pd3dGraphicsRootSignature, int cullState)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature, 0);
}

CObjectsShader::CObjectsShader()
{
}

CObjectsShader::~CObjectsShader()
{
}

void CObjectsShader::BuildObjects(ID3D12Device * pd3dDevice, ID3D12GraphicsCommandList * pd3dCommandList)
{

	CCubeMeshDiffused *pEnemyMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		12.0f, 12.0f, 12.0f);
	CEnemyBox *pEnemy = nullptr;

	m_nObjects = 10;

	dre.seed((unsigned int)time(NULL));

	m_ppObjects = new CEnemyBox*[m_nObjects];


	//나중에 프레임 안나오면 한번 다시 보자 (깊이 우선)
	//따라하기 11
	for (int i = 0;i < 10;++i)
	{
		pEnemy = new CEnemyBox;
		pEnemy->SetMesh(pEnemyMesh);
		//각 정육면체 객체의 위치를 설정한다.
		//pEnemy->SetPosition(i, i, i);
		m_ppObjects[i] = pEnemy;

		//delete pEnemy;
	}

	CreateShaderVariables(pd3dDevice, pd3dCommandList);

}

void CObjectsShader::AnimateObjects(float fTimeElapsed, XMFLOAT3& playerPos)
{

	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed, playerPos);

	}
}

void CObjectsShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++)
		{
			if (m_ppObjects[j]) delete m_ppObjects[j];
		}
		delete[] m_ppObjects;
	}
}

D3D12_INPUT_LAYOUT_DESC CObjectsShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CObjectsShader::CreateVertexShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CObjectsShader::CreatePixelShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CObjectsShader::CreateShader(ID3D12Device * pd3dDevice, ID3D12RootSignature * pd3dGraphicsRootSignature, int cullState)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature, cullState);
}

void CObjectsShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++)
			m_ppObjects[j]->ReleaseUploadBuffers();
	}
}

void CObjectsShader::Render(ID3D12GraphicsCommandList * pd3dCommandList, CCamera * pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);

	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j]->getActive())
		{

			m_ppObjects[j]->Render(pd3dCommandList, pCamera);
		}
	}
}

CWallShader::CWallShader()
{
}

CWallShader::~CWallShader()
{
}

void CWallShader::BuildObjects(ID3D12Device * pd3dDevice, ID3D12GraphicsCommandList * pd3dCommandList)
{

	CWallMeshDiffused* pWallMeshDif = new CWallMeshDiffused(pd3dDevice, pd3dCommandList, 4000.0f, 4000.0f, 4000.0f);

	CWall* pWall = nullptr;

	m_ppWalls = new CWall*[1];
	m_nWallNum = 1;



	pWall = new CWall();
	pWall->SetMesh(pWallMeshDif);
	//각 정육면체 객체의 위치를 설정한다. 
	pWall->SetPosition(0.0f, 0.0f, 0.0f);
	//pEnemy->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//pEnemy->SetRotationSpeed(10.0f*(i % 10) + 3.0f);
	//pWall->SetOOBB(pWall->GetPosition(), XMFLOAT3(100.0f, 100.0f, 200.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_ppWalls[0] = pWall;


}

void CWallShader::AnimateObjects(float fTimeElapsed)
{
}

void CWallShader::ReleaseObjects()
{
	if (m_ppWalls)
	{
		for (int j = 0; j < m_nWallNum; j++)
		{
			if (m_ppWalls[j]) delete m_ppWalls[j];
		}
		delete[] m_ppWalls;
	}
}

D3D12_INPUT_LAYOUT_DESC CWallShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CWallShader::CreateVertexShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CWallShader::CreatePixelShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CWallShader::CreateShader(ID3D12Device * pd3dDevice, ID3D12RootSignature * pd3dGraphicsRootSignature, int cullState)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature, cullState);
}

void CWallShader::ReleaseUploadBuffers()
{
	if (m_ppWalls)
	{
		for (int j = 0; j < m_nWallNum; j++)
			m_ppWalls[j]->ReleaseUploadBuffers();
	}
}

void CWallShader::Render(ID3D12GraphicsCommandList * pd3dCommandList, CCamera * pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);

	for (int j = 0; j < m_nWallNum; j++)
	{
		if (m_ppWalls[j])
		{
			m_ppWalls[j]->Render(pd3dCommandList, pCamera);
		}
	}
}

int CWallShader::moveWall(float playerZ, int wallIndex)
{

	if (playerZ >= m_ppWalls[(wallIndex + 1) % 5]->GetPosition().z)
	{
		if (wallIndex <= 1)
			m_ppWalls[wallIndex + 3]->Move(XMFLOAT3(0.0, 0.0, 1.0), 2000);
		else if (wallIndex > 1)
			m_ppWalls[wallIndex - 2]->Move(XMFLOAT3(0.0, 0.0, 1.0), 2000);

		wallIndex++;
		if (wallIndex == 5)
			wallIndex = 0;
	}
	return wallIndex;
}

void CBulletShader::AnimateObjects(float f)
{
	for (auto p = bulletList.begin(); p != bulletList.end();p++)
	{
		(*p)->Animate(f);
		if ((*p)->getDistance() > 300.0f)
		{
			p = bulletList.erase(p);
		}
	}

}

void CBulletShader::addBullet(XMFLOAT3& playerPos)
{
	bulletList.insert(bulletList.end(), new CBullet());

	list<CBullet*>::iterator end = bulletList.end().operator--();

	(*end)->SetMesh(bulletMesh);
	//(*end)->setFiredPosition(playerPos);
	(*end)->SetPosition(playerPos);
	//
	//(*end)->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//(*end)->SetRotationAxis(XMFLOAT3(1.0f, 0.0f, 1.0f));
	////
	//(*end)->SetRotationSpeed(100.0f);
	//(*end)->SetMovingSpeed(200.0f);

	numOfBullet++;
}

D3D12_INPUT_LAYOUT_DESC CBulletShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CBulletShader::CreateVertexShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CBulletShader::CreatePixelShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CBulletShader::CreateShader(ID3D12Device * pd3dDevice, ID3D12RootSignature * pd3dGraphicsRootSignature, int cullState)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature, cullState);
}

void CBulletShader::Render(ID3D12GraphicsCommandList * pd3dCommandList, CCamera * pCamera)
{
	for (CBullet* b : bulletList)
		b->Render(pd3dCommandList, pCamera);
}

void CParticleShader::AnimateObjects(float f)
{
	for (auto p = particleList.begin();p != particleList.end();)
	{
		for (int i = 0;i < m_nParticles;++i)
		{
			(*p)[i].Animate(f);
		}
		if ((*p)[0].getDistance() > 80.0f)
		{
			p = particleList.erase(p);
		}
		else
			p++;
	}
}



void CParticleShader::addParticles(XMFLOAT3 & boxPos)
{
	particleList.insert(particleList.end(), new CParticle[64]);

	uniform_real_distribution<> random(-1.0f, 1.0f);

	uniform_real_distribution<> rotateSpeed(10.0f, 30.0f);
	auto end = --particleList.end();

	dre.seed((unsigned int)time(NULL));
	for (int i = 0;i < m_nParticles;i++)
	{
		(*end)[i].setBoomPosition(boxPos);
		(*end)[i].SetPosition(boxPos);
		(*end)[i].SetMesh(particleMesh);
		(*end)[i].SetRotationAxis(XMFLOAT3(random(dre), random(dre), random(dre)));
		(*end)[i].SetRotationSpeed(rotateSpeed(dre));
		(*end)[i].SetMovingDirection(XMFLOAT3(random(dre), random(dre), random(dre)));
		(*end)[i].SetMovingSpeed(20.0f);
	}
}

D3D12_INPUT_LAYOUT_DESC CParticleShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CParticleShader::CreateVertexShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CParticleShader::CreatePixelShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CParticleShader::CreateShader(ID3D12Device * pd3dDevice, ID3D12RootSignature * pd3dGraphicsRootSignature, int cullState)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature, cullState);
}

void CParticleShader::Render(ID3D12GraphicsCommandList * pd3dCommandList, CCamera * pCamera)
{
	for (CParticle* p : particleList)
	{
		for (int i = 0;i < m_nParticles;++i)
		{
			p[i].Render(pd3dCommandList, pCamera);
		}
	}
}

void CEnemyShader::AnimateObjects(float)
{
}

void CEnemyShader::addEnem(XMFLOAT3& pos, XMFLOAT3X3& rot, int hp)
{
	enemlist.insert(enemlist.end(), new CEnemy());

	list<CEnemy*>::iterator end = enemlist.end().operator--();

	(*end)->SetMesh(enemMesh);
	//(*end)->setFiredPosition(playerPos);
	(*end)->SetPosition(pos);
	//(*end)->setRotate(rot);
	//(*end)->Rotate(&((*end)->GetRight()), 45.0f);
	(*end)->setRotate(rot);
	(*end)->onPrepareRender();
	(*end)->hp = hp;
	//(*end)->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//(*end)->SetRotationAxis(XMFLOAT3(1.0f, 0.0f, 1.0f));
	////
	//(*end)->SetRotationSpeed(100.0f);
	//(*end)->SetMovingSpeed(200.0f);

}

D3D12_INPUT_LAYOUT_DESC CEnemyShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CEnemyShader::CreateVertexShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CEnemyShader::CreatePixelShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CEnemyShader::CreateShader(ID3D12Device * pd3dDevice, ID3D12RootSignature * pd3dGraphicsRootSignature, int cullState)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature, cullState);
}

void CEnemyShader::Render(ID3D12GraphicsCommandList * pd3dCommandList, CCamera * pCamera)
{
	for (auto e = enemlist.begin(); e != enemlist.end(); e++)
	{

		(*e)->Render(pd3dCommandList, pCamera);
	}
}

void CHPBoxShader::addHPBox()
{
	CHPBox* box = new CHPBox();

	box->SetPosition(0.0, 0.0, 0.0);
	box->setActive(true);
	box->SetMesh(hpBoxMesh);

	HPBoxes.push_back(box);
}

D3D12_INPUT_LAYOUT_DESC CHPBoxShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CHPBoxShader::CreateVertexShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CHPBoxShader::CreatePixelShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CHPBoxShader::CreateShader(ID3D12Device * pd3dDevice, ID3D12RootSignature * pd3dGraphicsRootSignature, int cullState)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature, cullState);
}

void CHPBoxShader::Render(ID3D12GraphicsCommandList * pd3dCommandList, CCamera * pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);

	for (int j = 0; j < 30; j++)
	{
		if (HPBoxes[j]->getActive())
		{
			HPBoxes[j]->Render(pd3dCommandList, pCamera);
		}
	}
}

void CTimeBarShader::addTimeBar()
{
	CTimeBar* tbar = new CTimeBar();

	tbar->SetPosition(0.0, 0.0, 0.0);
	tbar->setActive(true);
	tbar->SetMesh(TimeBarMesh);

	TimeBars.push_back(tbar);
}

D3D12_INPUT_LAYOUT_DESC CTimeBarShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CTimeBarShader::CreateVertexShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CTimeBarShader::CreatePixelShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CTimeBarShader::CreateShader(ID3D12Device * pd3dDevice, ID3D12RootSignature * pd3dGraphicsRootSignature, int cullState)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature, cullState);
}

void CTimeBarShader::Render(ID3D12GraphicsCommandList * pd3dCommandList, CCamera * pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);

	for (int j = 0; j < 60; j++)
	{
		if (TimeBars[j]->getActive())
		{
			TimeBars[j]->Render(pd3dCommandList, pCamera);
		}
	}
}

void CPlayerParticleShader::AnimateObjects(float f)
{
	for (auto p = particleList.begin();p != particleList.end();)
	{
		for (int i = 0;i < m_nParticles;++i)
		{
			(*p)[i].Animate(f);
		}
		if ((*p)[0].getDistance() > 80.0f)
		{
			p = particleList.erase(p);
		}
		else
			p++;
	}
}

void CPlayerParticleShader::addParticles(XMFLOAT3 & boxPos)
{
	particleList.insert(particleList.end(), new CParticle[32]);

	uniform_real_distribution<> random(-1.0f, 1.0f);

	uniform_real_distribution<> rotateSpeed(10.0f, 30.0f);
	auto end = --particleList.end();

	dre.seed((unsigned int)time(NULL));
	for (int i = 0;i < m_nParticles;i++)
	{
		(*end)[i].setBoomPosition(boxPos);
		(*end)[i].SetPosition(boxPos);
		(*end)[i].SetMesh(PlayerParticleMesh);
		(*end)[i].SetRotationAxis(XMFLOAT3(random(dre), random(dre), random(dre)));
		(*end)[i].SetRotationSpeed(rotateSpeed(dre));
		(*end)[i].SetMovingDirection(XMFLOAT3(random(dre), random(dre), random(dre)));
		(*end)[i].SetMovingSpeed(10.0f);
	}
}

void CPlayerParticleShader::addDeathParticles(XMFLOAT3 & boxPos)
{
	particleList.insert(particleList.end(), new CParticle[32]);

	uniform_real_distribution<> random(-1.0f, 1.0f);

	uniform_real_distribution<> rotateSpeed(10.0f, 30.0f);
	auto end = --particleList.end();

	dre.seed((unsigned int)time(NULL));
	for (int i = 0;i < m_nParticles;i++)
	{
		(*end)[i].setBoomPosition(boxPos);
		(*end)[i].SetPosition(boxPos);
		(*end)[i].SetMesh(PlayerDeathMesh);
		(*end)[i].SetRotationAxis(XMFLOAT3(random(dre), random(dre), random(dre)));
		(*end)[i].SetRotationSpeed(rotateSpeed(dre));
		(*end)[i].SetMovingDirection(XMFLOAT3(random(dre), random(dre), random(dre)));
		(*end)[i].SetMovingSpeed(3.0f);
	}
}

D3D12_INPUT_LAYOUT_DESC CPlayerParticleShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CPlayerParticleShader::CreateVertexShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CPlayerParticleShader::CreatePixelShader(ID3DBlob ** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CPlayerParticleShader::CreateShader(ID3D12Device * pd3dDevice, ID3D12RootSignature * pd3dGraphicsRootSignature, int cullState)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature, cullState);
}

void CPlayerParticleShader::Render(ID3D12GraphicsCommandList * pd3dCommandList, CCamera * pCamera)
{
	for (CParticle* p : particleList)
	{
		for (int i = 0;i < m_nParticles;++i)
		{
			p[i].Render(pd3dCommandList, pCamera);
		}
	}
}
