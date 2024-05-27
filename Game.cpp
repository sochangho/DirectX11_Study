#include "pch.h"
#include "Game.h"

//Device : 파이프라인이 사용할 자원들을 생성할 때
//Device Context : 파이프라인 자체를 조작할 때에는 장치 문맥 인터페이스 사용

//SwapChain
//버퍼를 하나만 사용할 경우 그리고 지우는 과장에서 깜빡거리는 현상이 일어날 수 있다.
//해결 방법은 후면버퍼 전면버퍼 2개를 이용해서 
//후면 버퍼는 그려지면 , 전면과 후면과 교체를한다.
//전면은 후면, 후면은 전면이 된다.


Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_width = GWinSizeX;
	_height = GWinSizeY;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewport(); // 화면 옵션설정
	 
	CreateGeometry(); // 기하학 도형 :  정점 버퍼 인데스 버퍼 만든다
	CreateVS();      // 버텍스 쉐이더 생성 
	CreateInputLayout(); // Transform 데이터를 쉐이더로 넘기기 위한 설정
	CreatePS(); // 픽셀쉐이더 생성
	CreateSRV(); // 텍스쳐로드 

	CreateConstantBuffer(); //ConstantBuffer 생성

	CreateRasterizerState(); // Resterizer 옵션 설정 및 생성
	CreateSamplerState(); //Sampler State
    CreateBlendState(); // Blend State
}

void Game::Update()
{
	//_transformData.offset.x += 0.003f;
	//_transformData.offset.y += 0.003f;

	D3D11_MAPPED_SUBRESOURCE subResource;
	ZeroMemory(&subResource, sizeof(subResource));

	_deviceContext->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	::memcpy(subResource.pData, &_transformData, sizeof(_transformData));
	_deviceContext->Unmap(_constantBuffer.Get(), 0);

}

void Game::Render()
{
	RenderBegin();
	
	//TODO : 랜더링 파이프라인
	//IA - VS - RS - PS - OM
	{
		
		uint32 stride = sizeof(Vertex);
		uint32 offset = 0;

		//IA		
		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
		_deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		_deviceContext->IASetInputLayout(_inputLayout.Get());
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//VS
		_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
		_deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());
		
		//RS
		_deviceContext->RSSetState(_rasterizerState.Get());
		
		//PS
		_deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);
		_deviceContext->PSSetShaderResources(0, 1, _shaderResouceView.GetAddressOf());
		_deviceContext->PSSetSamplers(0, 1, _samplerState.GetAddressOf());

		//OM
		_deviceContext->OMSetBlendState(_blendState.Get(), nullptr, 0xFFFFFFFF);

		//_deviceContext->Draw(_vertices.size(), 0);
		_deviceContext->DrawIndexed(_indices.size(), 0,0);

	}
	RenderEnd();
}



void Game::RenderBegin()
{
	_deviceContext->OMSetRenderTargets(1,_renderTargetView.GetAddressOf(), nullptr); // 후면 버퍼에 그려달라고 요청
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(), _clearColor); // 프레임마다 리셋 _clearColor로 
	_deviceContext->RSSetViewports(1, &_viewport);
}




void Game::RenderEnd()
{
	// 후면버퍼에서 -> 전면 버퍼로 복사
	HRESULT hr = _swapChain->Present(1, 0);
	CHECK(hr);
}

void Game::CreateDeviceAndSwapChain()
{

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.BufferDesc.Width = _width;
		desc.BufferDesc.Height = _height;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count = 1; // 계단 현상 완화
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1;
		desc.OutputWindow = _hwnd;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	//_device.Get(); // ID3D11Device*를 가지고 오고 싶을 때
	//_device.GetAddressOf(); // ID3D11Device**를 가지고 오고 싶을 때

	HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		_swapChain.GetAddressOf(),
		_device.GetAddressOf(),
		nullptr,
		_deviceContext.GetAddressOf()
	);

	CHECK(hr);
}

void Game::CreateRenderTargetView()
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());

	CHECK(hr);

	_device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());
	
	CHECK(hr);

}

void Game::SetViewport()
{
	_viewport.TopLeftX = 0.f;
	_viewport.TopLeftY = 0.f;
	_viewport.Width = static_cast<float>(_width);
	_viewport.Height = static_cast<float>(_height);
	_viewport.MinDepth = 0.f;
	_viewport.MaxDepth = 1.f;
}

void Game::CreateGeometry()
{

	//vectexData
	{
		_vertices.resize(4);

		_vertices[0].position = Vec3(-0.5f, -0.5f, 0.f);
		//_vertices[0].color = Color(1.0f, 0.f, 0.f, 1.f);
		_vertices[0].uv = Vec2(0.f, 1.f);

		_vertices[1].position = Vec3(-0.5f, 0.5f, 0.f);
		//_vertices[1].color = Color(0.0f, 1.f, 0.f, 1.f);
		_vertices[1].uv = Vec2(0.f, 0.f);

		_vertices[2].position = Vec3(0.5f, -0.5f, 0.f);
		//_vertices[2].color = Color(0.0f, 0.f, 1.f, 1.f);
		_vertices[2].uv = Vec2(1.f, 1.f);

		_vertices[3].position = Vec3(0.5f, 0.5f, 0.f);
		//_vertices[3].color = Color(1.f, 1.f, 1.f, 1.f);
		_vertices[3].uv = Vec2(1.f, 0.f);
	}


	//vectexBuffer
	{
		D3D11_BUFFER_DESC desc; // 버퍼를 읽고 쓰는 방법을 식별
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = (uint32)(sizeof(Vertex) * _vertices.size());


		D3D11_SUBRESOURCE_DATA data; // 하위 리소스를 초기화하기 위한 데이터를 지정합니다.
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = _vertices.data();

		HRESULT hr = _device->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());
		CHECK(hr);
	}

	//index
	{
		_indices = { 0,1,2, 2,1,3 };
	}

	//IndexBuffer
	{
		D3D11_BUFFER_DESC desc; // 버퍼를 읽고 쓰는 방법을 식별
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = (uint32)(sizeof(uint32) * _indices.size());


		D3D11_SUBRESOURCE_DATA data; // 하위 리소스를 초기화하기 위한 데이터를 지정합니다.
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = _indices.data();

		HRESULT hr =  _device->CreateBuffer(&desc, &data, _indexBuffer.GetAddressOf());
		CHECK(hr);
	}


}

void Game::CreateInputLayout()
{

	//정점 구조체를 정의했다면, 그 구조체의 각 성분이 어떤 용도인지 Direct3D에게 알려줘야 한다.
	//D3D11_INPUT_ELEMENT_DESC 구조체로 이루어진 배열을 통해 구축한다.
	
	//정점의 성분이 2개라면 D3D11_INPUT_ELEMENT_DESC 배열의 원소도 2개여야한다.
    

	D3D11_INPUT_ELEMENT_DESC layout[] = {

		{
			"POSITION",   //SemanticName : 문자열 이름, 정점셰이더에서 쓰이는 유효한 변수이름
 			0,            //SemanticIndex : 인덱스, 텍스쳐 좌표의 인덱스를 구분하는데 쓰인다.
			DXGI_FORMAT_R32G32B32_FLOAT, //정점 성분의 자료 형식을 구분하는데 쓰인다.
			0,            //InputSlot : 이 성분의 자료가 공급될 정점 버퍼 슬롯의 색인이다.
			0,            //AlignedByteOffset : 정점의 위치 offset
			D3D11_INPUT_PER_VERTEX_DATA,//인스턴싱에 쓰이는 부분 
			0  //인스턴싱에 쓰이는 부분
		},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);

	_device->CreateInputLayout(layout,count, _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), _inputLayout.GetAddressOf());

}

void Game::CreateVS()
{

	LoadShaderFromFile(L"Default.hlsl", "VS", "vs_5_0", _vsBlob);

	HRESULT hr =  _device->CreateVertexShader(_vsBlob->GetBufferPointer(),
		_vsBlob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());

	CHECK(hr);
}



void Game::CreatePS()
{
	LoadShaderFromFile(L"Default.hlsl", "PS", "ps_5_0", _psBlob);

	HRESULT hr = _device->CreatePixelShader(_psBlob->GetBufferPointer(),
		_psBlob->GetBufferSize(), nullptr, _pixelShader.GetAddressOf());
	CHECK(hr);
}

void Game::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK; // 뒤에있는 물체는 그리지 않겠다.
	desc.FrontCounterClockwise = false; // 시계방향으로 or 반시계 방향으로

	HRESULT hr = _device->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());
	CHECK(hr);
}

void Game::CreateSamplerState()
{

	// 텍스쳐 좌표가 텍셀에 매칭되지 않을 때, 색상을 어떻게 결정할지 정의합니다.
	//Wrap : 텍스쳐 좌표가 [0,1] 범위를 벗어났을 때, 좌표값을 '감싸서' 반복 적용합니다.
	//Mirror : 좌표가 범위를 벗어날 때 마다 이미지가 거울처럼 반전
	//Clamp : 좌표가 [0,1] 범위를 벗어나면, 가장자리의 색상을 계속 사용합니다.
	//Border : 지정된 색상으로 경계를 채웁니다.

	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.BorderColor[0] = 1;
	desc.BorderColor[1] = 0;
	desc.BorderColor[2] = 0;
	desc.BorderColor[3] = 1;

	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.Filter = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;

	desc.MaxAnisotropy = 16;
	desc.MaxLOD = FLT_MAX;
	desc.MinLOD = FLT_MIN;
	desc.MipLODBias = 0.0f;



	_device->CreateSamplerState(&desc, _samplerState.GetAddressOf());

}

void Game::CreateBlendState()
{
	//BlendState 렌더링 파이프라인에서 픽셀 셰이더를 거쳐 생성된 
	//단편이 렌더 타겟에 어떻게 적용될지 결정하는 상태
	//이미지위에 이미지를 덧그릴 때 결과가 어떻게 나올지를 결정하는 값

	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;

	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT hr = _device->CreateBlendState(&desc, _blendState.GetAddressOf());
	CHECK(hr);

}

void Game::CreateSRV()
{
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;


	HRESULT hr =  ::LoadFromWICFile(L"Skeleton.jpg", WIC_FLAGS_NONE, &md, img);

	CHECK(hr);

	hr = ::CreateShaderResourceView(_device.Get(), img.GetImages(), img.GetImageCount()
		, md, _shaderResouceView.GetAddressOf());
	CHECK(hr);
}

void Game::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DYNAMIC; //CPU_Write + GPU_Read
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(TransformData);
	desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	HRESULT hr = _device->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());

	CHECK(hr);
}



void Game::LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob)
{
	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

	HRESULT hr = ::D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		blob.GetAddressOf()
		,nullptr);

	CHECK(hr);
}
