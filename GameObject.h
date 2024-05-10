#pragma once
class GameObject
{

public:
	GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	~GameObject();

	void Update();
	void Render(shared_ptr<Pipeline> pipeline);

private:

	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> deviceContext;

	shared_ptr<Geometry<VertexTextureData>> _geometry; //Geometry
	shared_ptr<VertexBuffer> _vertexBuffer = nullptr;  //Geometry
	shared_ptr<IndexBuffer> _indexBuffer = nullptr;    //Geometry
	shared_ptr<InputLayout> _inputLayout = nullptr;	   //Geometry

	shared_ptr<VertexShader> _vertexShader = nullptr;  //VS
	shared_ptr<PixelShader> _pixelShader = nullptr;    //PS

	shared_ptr<Texture> _texture1 = nullptr;           //resorceView


	shared_ptr<RasterizerState> _rasterizerState = nullptr;
	shared_ptr<SamplerState> _samplerState = nullptr;
	shared_ptr<BlendState> _blendState = nullptr;


private:


	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _constantBuffer = nullptr;

	shared_ptr<Transform> _transform = make_shared<Transform>();

	shared_ptr<Transform> _parent = make_shared<Transform>();
};

