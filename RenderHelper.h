#pragma once

struct CameraData {

	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;

};


struct TransformData {

	Matrix matWorld = Matrix::Identity; // Matrix :: Identity  (항등행렬로 만들어준다.)   

};

struct AnimationData
{
	Vec2 spriteOffset;
	Vec2 spriteSize;
	Vec2 textureSize;

	float useAniamtion;
	float padding;
};