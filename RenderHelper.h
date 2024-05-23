#pragma once

struct CameraData {

	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;

};


struct TransformData {

	Matrix matWorld = Matrix::Identity; // Matrix :: Identity  (�׵���ķ� ������ش�.)   

};

struct AnimationData
{
	Vec2 spriteOffset;
	Vec2 spriteSize;
	Vec2 textureSize;

	float useAniamtion;
	float padding;
};