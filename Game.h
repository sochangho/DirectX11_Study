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

private:
	void RenderBegin();
	void RenderEnd();


private :
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

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
	uint32 _width = 0;
	uint32 _height = 0;


private:

	//DX �Լ��� ����������
	//ComPtr : �޸𸮸� new delete ���ص� �ȴ�.
	//����Ʈ�����Ϳ� ����ϴ�
	
	ComPtr<ID3D11Device> _device = nullptr; 
	//�� ����̽��� ����Ŵ�.    
	//**���������ְ�


	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
	// ���ֿ��� ����� ���� ��
	//**������ ������


	ComPtr<IDXGISwapChain> _swapChain = nullptr;
	//õõ�� ��ȭ�ϴ� �κ��� IDXG ���̺귯���� �־����.
	//�����������̶� �����ִ�.
	//**���� ���� : �ĸ���ۿ��ִ� ���� �������� ������� �����Ѵ�.
	//-----------------------------------------------------------

	//RTV
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	//Misc
	D3D11_VIEWPORT _viewport = {0};

	float _clearColor[4] = { 0,0,0,0};
private :
	//Geometry-------------------------------------------------
	//Unity Mesh�� ����
	
	vector<Vertex> _vertices;
	ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;

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

};

