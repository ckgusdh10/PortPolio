#pragma once
#include "GameObject.h"
#include "Camera.h"



struct CB_GAMEOBJECT_INFO
{
	XMFLOAT4X4 m_xmf4x4World;
};

class CShader
{
public:
	CShader();
	virtual ~CShader();
private:
	int m_nReferences = 0;
public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }


	virtual  void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList) = 0;
	virtual void ReleaseObjects() =0;
	virtual void AnimateObjects(float) {};
	virtual void ReleaseUploadBuffers() = 0;

	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	virtual D3D12_RASTERIZER_DESC CreateRasterizerState_CullBack();
	virtual D3D12_RASTERIZER_DESC CreateRasterizerState_CullFront();
	virtual D3D12_BLEND_DESC CreateBlendState();
	virtual D3D12_DEPTH_STENCIL_DESC CreateDepthStencilState();
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
	D3D12_SHADER_BYTECODE CompileShaderFromFile(WCHAR *pszFileName, LPCSTR pszShaderName,
		LPCSTR pszShaderProfile, ID3DBlob **ppd3dShaderBlob);
	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
		*pd3dGraphicsRootSignature,int cullState);
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();
	virtual void UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList,
		XMFLOAT4X4 *pxmf4x4World);
	virtual void OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);

protected:
	ID3D12PipelineState **m_ppd3dPipelineStates = NULL;
	int m_nPipelineStates = 0;
	default_random_engine dre;
};

class CPlayerShader : public CShader
{
public:
	CPlayerShader();
	virtual ~CPlayerShader();
	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
		*pd3dGraphicsRootSignature,int cullState);

	virtual  void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList) {};
	virtual void ReleaseObjects() {};
	virtual void AnimateObjects(float) {};
	virtual void ReleaseUploadBuffers() {};
	virtual CGameObject** getObjP() { return nullptr; };
	virtual int getNum() { return 1; };
};

class CObjectsShader : public CShader
{
public:
	CObjectsShader();
	virtual ~CObjectsShader();


	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList);
	virtual void AnimateObjects(float fTimeElapsed, XMFLOAT3& playerPos);
	virtual void ReleaseObjects();
	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
		*pd3dGraphicsRootSignature,int cullState);
	virtual void ReleaseUploadBuffers();
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);
	virtual int getNum() { return m_nObjects; }
	CEnemyBox** getObjP() { return m_ppObjects; }
protected:
	CEnemyBox** m_ppObjects = NULL;

	int m_nObjects = 0;
};

class CWallShader : public CShader
{
public:
	CWallShader();
	virtual ~CWallShader();
	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void ReleaseObjects();
	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
		*pd3dGraphicsRootSignature, int cullState);
	virtual void ReleaseUploadBuffers();
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);

	virtual int getNum() { return m_nWallNum; }
	CWall** getObjP() { return m_ppWalls; }

	int moveWall(float playerZ,int wallIndex);
protected:
	CWall** m_ppWalls = nullptr;
	
	int m_nObjects = 0;
	int m_nWallNum = 5;
};

class CBulletShader : public CShader
{

	list<CBullet*> bulletList;
	CMesh* bulletMesh;
	int numOfBullet = 0;
public:
	virtual  void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList) {
		bulletMesh = new CBulletMesh(pd3dDevice, pd3dCommandList, 4.0f, 4.0f, 4.0f);
	};
	virtual void ReleaseObjects() {};
	virtual void AnimateObjects(float) ;
	virtual void ReleaseUploadBuffers() {};

	virtual CGameObject** getObjP() { return nullptr; };
	list<CBullet*>* getList() { return &bulletList; }
	virtual int getNum() {return numOfBullet;};
	void addBullet(XMFLOAT3& playerPos);

	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
		*pd3dGraphicsRootSignature, int cullState);

	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);
};

class CParticleShader : public CShader
{
	list<CParticle*> particleList;
	CMesh* particleMesh;
	int m_nParticles = 64;
public :
	list<CParticle*>* getList() { return &particleList; }

	virtual  void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList) {
		particleMesh = new CParticleMesh(pd3dDevice, pd3dCommandList, 2.0f, 2.0f, 2.0f);
	};
	virtual void ReleaseObjects() {};
	virtual void AnimateObjects(float);
	virtual void ReleaseUploadBuffers() {};
	virtual CGameObject** getObjP() { return nullptr; };
	void addParticles(XMFLOAT3& boxPos);

	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
		*pd3dGraphicsRootSignature, int cullState);

	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);
};
class CPlayerParticleShader : public CShader
{
	list<CParticle*> particleList;
	CMesh* PlayerParticleMesh;
	CMesh* PlayerDeathMesh;

	int m_nParticles = 32;
public:
	list<CParticle*>* getList() { return &particleList; }

	virtual  void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList) {
		PlayerParticleMesh = new CPlayerParticleMesh(pd3dDevice, pd3dCommandList, 1.0f, 1.0f, 1.0f);
		PlayerDeathMesh = new CPlayerParticleMesh(pd3dDevice, pd3dCommandList, 3.0f, 3.0f, 3.0f);
	};
	virtual void ReleaseObjects() {};
	virtual void AnimateObjects(float);
	virtual void ReleaseUploadBuffers() {};
	virtual CGameObject** getObjP() { return nullptr; };
	void addParticles(XMFLOAT3& boxPos);
	void addDeathParticles(XMFLOAT3& boxPos);

	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
		*pd3dGraphicsRootSignature, int cullState);

	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);
};
class CEnemyShader : public CShader
{
	list<CEnemy*> enemlist;
	CMesh* enemMesh;
	//int m_nParticles = 64;
public:
	list<CEnemy*>* getList() { return &enemlist; }

	virtual  void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList) {
		enemMesh = new CAirplaneMeshDiffused(pd3dDevice, pd3dCommandList, 20.0f,
			20.0f, 4.0f, XMFLOAT4(0.0f, 0.5f, 0.0f, 0.0f));
	};
	virtual void ReleaseObjects() {};
	virtual void AnimateObjects(float);
	virtual void ReleaseUploadBuffers() {};
	virtual CGameObject** getObjP() { return nullptr; };
	//void addParticles(XMFLOAT3& boxPos);
	void addEnem(XMFLOAT3& pos,XMFLOAT3X3& rot,int hp);
	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
		*pd3dGraphicsRootSignature, int cullState);

	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);
};	

class CHPBoxShader : public CShader
{
	vector<CHPBox*> HPBoxes;
	CMesh* hpBoxMesh;

public:
	vector<CHPBox*>& getHPBoxes() { return HPBoxes; }

	virtual  void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList) {
		hpBoxMesh = new CHPBoxMesh(pd3dDevice, pd3dCommandList, 1.0f, 1.0f, 1.0f);
		for (int i = 0; i < 30;i++)
			addHPBox();
	};
	

	virtual void ReleaseObjects() {};
	virtual void AnimateObjects(float) {};
	virtual void ReleaseUploadBuffers() {};
	virtual CGameObject** getObjP() { return nullptr; };
	
	void addHPBox();
	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
		*pd3dGraphicsRootSignature, int cullState);

	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);
};

class CTimeBarShader : public CShader
{
	vector<CTimeBar*> TimeBars;
	CMesh* TimeBarMesh;

public:
	vector<CTimeBar*>& getTimeBar() { return TimeBars; }

	virtual  void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList) {
		TimeBarMesh = new CTimeBarMesh(pd3dDevice, pd3dCommandList, 0.25f, 1.0f, 1.0f);

		for (int i = 0; i < 60;i++)
			addTimeBar();
	};


	virtual void ReleaseObjects() {};
	virtual void AnimateObjects(float) {};
	virtual void ReleaseUploadBuffers() {};
	virtual CGameObject** getObjP() { return nullptr; };

	void addTimeBar();
	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
		*pd3dGraphicsRootSignature, int cullState);

	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);
};