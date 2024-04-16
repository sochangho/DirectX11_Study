#include "pch.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(ComPtr<ID3D11Device> device) 
	: _device(device)
{
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Create(const vector<uint32>& indices)
{
	_stride = sizeof(uint32);
	_count = static_cast<uint32>(indices.size());

	D3D11_BUFFER_DESC desc; // 버퍼를 읽고 쓰는 방법을 식별
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = (uint32)(_stride*_count);


	D3D11_SUBRESOURCE_DATA data; // 하위 리소스를 초기화하기 위한 데이터를 지정합니다.
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = indices.data();

	HRESULT hr = _device->CreateBuffer(&desc, &data, _indexBuffer.GetAddressOf());
	CHECK(hr);

}
