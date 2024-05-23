#pragma once
#include "ResourceBase.h"
class Mesh : public ResourceBase
{
    using Super = ResourceBase;

public:
    Mesh(ComPtr<ID3D11Device> device);
   virtual ~Mesh();

   void CreateDefaultRectangle();

   shared_ptr<VertexBuffer> GetVertexBuffer() { return _vertexBuffer; }
   shared_ptr<IndexBuffer> GetIndexBuffer() { return _indexBuffer; }



private:

    ComPtr<ID3D11Device> _device;


    shared_ptr<Geometry<VertexTextureData>> _geometry; //Geometry
    shared_ptr<VertexBuffer> _vertexBuffer = nullptr;  //Geometry
    shared_ptr<IndexBuffer> _indexBuffer = nullptr;    //Geometry

};

