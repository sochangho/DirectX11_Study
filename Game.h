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

	//DX 함수가 개많음ㅎㅎ
	//ComPtr : 메모리를 new delete 안해도 된다.
	//스마트포인터와 비슷하다
	
	ComPtr<ID3D11Device> _device = nullptr; 
	//이 디바이스로 만들거다.    
	//**생성시켜주고


	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
	// 유닛에게 명령을 내릴 때
	//**오더를 내리고


	ComPtr<IDXGISwapChain> _swapChain = nullptr;
	//천천히 변화하는 부분을 IDXG 라이브러리에 넣어놨다.
	//최종랜더링이랑 관련있다.
	//**더블 버퍼 : 후면버퍼에있는 것을 전면으로 고속으로 복사한다.
	//-----------------------------------------------------------

	//RTV
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	//Misc
	D3D11_VIEWPORT _viewport = {0};

	float _clearColor[4] = { 0,0,0,0};
private :
	//Geometry-------------------------------------------------
	//Unity Mesh의 개념
	
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

