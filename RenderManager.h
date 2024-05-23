#pragma once
#include"RenderHelper.h"

class RenderManager
{
public:
	RenderManager(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	


	void Init();
	void Update(shared_ptr<Graphics> graphics);
private :
	void PushCameraData();
	void PushTransformData();
	void PushAnimationData();

	void GatherRenderableObjects();
	void RenderObjects();


private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;

	shared_ptr<Pipeline> _pipeline;

private:

	CameraData _cameraData;
	shared_ptr<ConstantBuffer<CameraData>> _cameraBuffer = nullptr;

	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _transformBuffer = nullptr;

	//Animation
	AnimationData _animationData;
	shared_ptr<ConstantBuffer<AnimationData>> _animationBuffer;

private:

	shared_ptr<RasterizerState> _rasterizerState = nullptr;
	shared_ptr<SamplerState> _samplerState = nullptr;
	shared_ptr<BlendState> _blendState = nullptr;


	vector<shared_ptr<GameObject>> _renderObjects;
};

