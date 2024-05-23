#include "pch.h"
#include "MeshRenderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "Game.h"
#include "Pipeline.h"
#include "ResourceManager.h"


MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext) :
	_device(device), _deviceContext(deviceContext),
Super(ComponentType::MeshRenderer)
{

}

MeshRenderer::~MeshRenderer()
{


}




