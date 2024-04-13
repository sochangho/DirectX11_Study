#pragma once

struct Vertex {
	Vec3 position;
	//Color color;
	Vec2 uv;
};

//UV


struct TransformData {
	
	Matrix matWorld = Matrix::Identity; // Matrix :: Identity  (항등행렬로 만들어준다.)   
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;

};