#pragma once


class MonoBehavior;

class GameObject : public enable_shared_from_this<GameObject>
{

public:
	GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	~GameObject();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();

	shared_ptr<Component> GetFixedComponent(ComponentType type);
	shared_ptr<Transform> GetTransform();

	shared_ptr<Transform> GetOrAddTransform();

	void AddComponent(shared_ptr<Component> component);

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


protected:

	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
	vector<shared_ptr<MonoBehavior>> _scripts;

};

