#pragma once

#include "Resource.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"
#include "Animation.h"

class ResourceManager
{
public:

	ResourceManager(ComPtr<ID3D11Device> device);

	void Init();

	template<typename T>
	shared_ptr<T> Load(const wstring& key, const wstring& path);

	template<typename T>
	bool Add(const wstring& key, shared_ptr<T> obj);

	template<typename T>
	shared_ptr<T> Get(const wstring& key);

	template<typename T>
	ResourceType GetResourceType();

private:

	void CreateDefaultTexture();
	void CreateDefaultMesh();
	void CreateDefaultShader();
	void CreateDefaultMaterial();
	void CreateDefaultAnimation();

private:

	ComPtr<ID3D11Device> _device;

	using KeyObjMap = map<wstring, shared_ptr<ResourceBase>>;
	
	array< KeyObjMap, RESOURCE_TYPE_COUNT > _resource;
};





template<typename T>
inline shared_ptr<T> ResourceManager::Load(const wstring& key, const wstring& path)
{
	ResourceType resourceType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resource[static_cast<uint8>(resourceType)];
    
	auto findIt = keyObjMap.find(key);
	
	if (findIt != keyObjMap.end()) {

		return static_pointer_cast<T>();
	}

	shared_ptr<T> object = make_shared<T>();
	object->Load(path);
	keyObjMap[key] = object;

	return object;
}

template<typename T>
inline bool ResourceManager::Add(const wstring& key, shared_ptr<T> obj)
{
	ResourceType resourceType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resource[static_cast<uint8>(resourceType)];
	auto findIt = keyObjMap.find(key);

	if (findIt != keyObjMap.end()) {

		return false;
	}

	keyObjMap[key] = obj;


	return true;
}

template<typename T>
inline shared_ptr<T> ResourceManager::Get(const wstring& key)
{
	ResourceType resourceType = GetResourceType<T>();

	KeyObjMap& keyObjMap = _resource[static_cast<uint8>(resourceType)];


	auto findIt = keyObjMap.find(key);

	if (findIt != keyObjMap.end()) {

		return static_pointer_cast<T>(findIt->second);
	}



	return nullptr;
}

template<typename T>
inline ResourceType ResourceManager::GetResourceType()
{

	if (is_same_v<T,Texture>) {
		return ResourceType::Texture;
	}
	else if (is_same_v<T, Shader>) {
		return ResourceType::Shader;
	}
	else if (is_same_v<T, Mesh>) {
		return ResourceType::Mesh;
	}
	else if (is_same_v<T, Material>) {
		return ResourceType::Merterial;
	}
	else if (is_same_v<T, Animation>) {
		return ResourceType::Animation;
	}

	assert(false);
	return ResourceType::None;
}
