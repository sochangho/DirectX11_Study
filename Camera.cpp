#include "pch.h"
#include "Camera.h"

Matrix Camera::S_MatView = Matrix::Identity;
Matrix Camera::S_MatProjection = Matrix::Identity;


Camera::Camera() : Super(ComponentType::Camera)
{

}

Camera::~Camera()
{
}

void Camera::Update()
{
	UpdateMatrix();

}

void Camera::UpdateMatrix()
{
	Vec3 eyePosition = GetTransform()->GetPosition();
	Vec3 focusPosition = eyePosition + GetTransform()->GetLook();
	Vec3 upDirection = GetTransform()->GetUp();
	
	S_MatView = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection); // 카메라 변환 행렬

	//S_MatView = GetTransform()->GetWordMatrix().Invert(); // 역행렬을 때려서 카메라 기준 좌표로 변환 

	if (_type == ProjectionType::Perspective)
	{
		S_MatProjection = ::XMMatrixPerspectiveFovLH(XM_PI / 4.f, 800.f / 600.f, 1.f, 100.f);
	}
	else 
	{
		S_MatProjection = ::XMMatrixOrthographicLH(800, 600, 0.f, 1.f);
	}
}
