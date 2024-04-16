#pragma once


struct VertexTextureData {
	Vec3 position;
	Vec2 uv;

	static vector<D3D11_INPUT_ELEMENT_DESC> desc;

};



struct VertexColorData {
	Vec3 position;
	Color color = { 0,0,0,0 };

	static vector<D3D11_INPUT_ELEMENT_DESC> desc;
};