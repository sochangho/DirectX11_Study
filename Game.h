#pragma once
class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();


private :
	void CreateGeometry();
	void CreateInputLayout();
	
	void CreateVS();
	void CreatePS();

	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateSRV();

	void CreateConstantBuffer();

	void LoadShaderFromFile(const wstring& path,
		const string& name, const string& version,
		ComPtr<ID3DBlob>& blob
	);

private:
	HWND _hwnd;
	
	
	shared_ptr<Graphics> _graphics = nullptr;

	

private :
	//Geometry-------------------------------------------------
	//Unity Mesh¿« ∞≥≥‰
	
	vector<Vertex> _vertices;
	//ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;

	shared_ptr<VertexBuffer> _vertexBuffer = nullptr;


	vector<uint32> _indices;
	ComPtr<ID3D11Buffer> _indexBuffer = nullptr;

	ComPtr<ID3D11InputLayout> _inputLayout = nullptr;
	
	//------------------------------------------------------------




	//VS---------------------------------------------------------
	ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
	ComPtr<ID3DBlob> _vsBlob = nullptr;
	//------------------------------------------------------------
	
	//PS---------------------------------------------------------
	ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
	ComPtr<ID3DBlob> _psBlob = nullptr;
	//-----------------------------------------------------------
	
	//RAS
	ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;
	ComPtr<ID3D11SamplerState> _samplerState = nullptr;
	ComPtr<ID3D11BlendState> _blendState = nullptr;

	//SRV
	ComPtr<ID3D11ShaderResourceView> _shaderResouceView = nullptr;

	//[cpu<->ram] [GPU <-> vram]

private :


	TransformData _transformData;
	ComPtr<ID3D11Buffer> _constantBuffer;

	Vec3 _localPostion = { 0.f,0.f,0.f };
	Vec3 _localRotation = { 0.f,0.f,0.f };
	Vec3 _localScale = { 1.f,1.f,1.f };

};

