#pragma once
class Graphics
{

public:
	Graphics(HWND hwnd);
	~Graphics();


	void RenderBegin();
	void RenderEnd();

	ComPtr<ID3D11Device> GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; }

private:

	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

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
	D3D11_VIEWPORT _viewport = { 0 };

	float _clearColor[4] = { 0,0,0,0 };
};

