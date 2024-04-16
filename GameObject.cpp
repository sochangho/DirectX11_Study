#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	:_device(device)
{

	_geometry = make_shared<Geometry<VertexTextureData>>();	
	GeometryHelper::CreateRectangle(_geometry);

	_vertexBuffer = make_shared<VertexBuffer>(device);
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>(device);
	_indexBuffer->Create(_geometry->GetIndices());

	_vertexShader = make_shared<VertexShader>(device);
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");


	_inputLayout = make_shared<InputLayout>(device);
	_inputLayout->Create(VertexTextureData::desc, _vertexShader->GetBlob());


	_pixelShader = make_shared<PixelShader>(device);
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");


	_rasterizerState = make_shared<RasterizerState>(device);
	_rasterizerState->Create();


	_blendState = make_shared<BlendState>(device);
	_blendState->Create();

	_constantBuffer = make_shared<ConstantBuffer<TransformData>>(device, deviceContext);
	_constantBuffer->Create();

	_texture1 = make_shared<Texture>(device);
	_texture1->Create(L"Skeleton.jpg");

	_samplerState = make_shared<SamplerState>(device);
	_samplerState->Create();

}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	//_transformData.offset.x += 0.003f;
	//_transformData.offset.y += 0.003f;

	
	Matrix matScale =  Matrix::CreateScale(_localScale/4);
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPostion);

	Matrix matWorld = matScale * matRotation * matTranslation;
	_transformData.matWorld = matWorld;
	
	_constantBuffer->CopyData(_transformData);
}

void GameObject::Render(shared_ptr<Pipeline> pipeline)
{
	PipelineInfo info;
	info.inputLayout = _inputLayout;
	info.vertexShader = _vertexShader;
	info.pixelShader = _pixelShader;
	info.rasterizerState = _rasterizerState;
	info.blendState = _blendState;

	pipeline->UpdatePipeline(info);

	auto _deviceContext = deviceContext;

	pipeline->SetVertexBuffer(_vertexBuffer);
	pipeline->SetIndexBuffer(_indexBuffer);
	pipeline->SetConstantBuffer(0, SS_VertexShader, _constantBuffer);
	pipeline->SetTexture(0, SS_PixelShader, _texture1);
	pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);
	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);


}
