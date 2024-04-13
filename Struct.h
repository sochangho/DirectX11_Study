#pragma once

struct Vertex {
	Vec3 position;
	//Color color;
	Vec2 uv;
};

//UV


struct TransformData {
	
	Matrix matWorld = Matrix::Identity; // Matrix :: Identity  (�׵���ķ� ������ش�.)   
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;

};