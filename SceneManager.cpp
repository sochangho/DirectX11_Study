#include "pch.h"
#include "SceneManager.h"
#include "Scene.h";
#include "GameObject.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "ResourceManager.h"

#include "Game.h"

#include "Animation.h"
#include "Animator.h"

#include "CameraMove.h"

SceneManager::SceneManager(shared_ptr<Graphics> graphics) : _graphics(graphics)
{
	

}

void SceneManager::Init()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Awake();
	_activeScene->Start();
}

void SceneManager::Update()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Update();
	_activeScene->LateUpdate();

	_activeScene->FixedUpdate();

}

void SceneManager::LoadScene(wstring sceneName)
{
	_activeScene = LoadTestScene();
	
}

void SceneManager::Render()
{

}

shared_ptr<Scene> SceneManager::LoadTestScene()
{
	shared_ptr<Scene> scene = make_shared<Scene>();

	{
		shared_ptr<GameObject> _monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		{
			_monster->GetOrAddTransform();

			auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());

			_monster->AddComponent(meshRenderer);

			auto mesh = RESOURCE->Get<Mesh>(L"Rectangle");
			auto mat = RESOURCE->Get<Material>(L"Default");

			_monster->GetMeshRenderer()->SetMesh(mesh);
			_monster->GetMeshRenderer()->SetMeterial(mat);
		}

		auto animator = make_shared<Animator>();
		_monster->AddComponent(animator);
		auto anim = RESOURCE->Get<Animation>(L"SnakeAnim");
		animator->SetAnimation(anim);

		scene->AddGameObject(_monster);

	}


	{
		shared_ptr<GameObject> _monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());		
		{
			_monster->GetOrAddTransform()->SetPosition(Vec3(1.f,1.f,0.f));

			auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());

			_monster->AddComponent(meshRenderer);

			auto mesh = RESOURCE->Get<Mesh>(L"Rectangle");
			auto mat = RESOURCE->Get<Material>(L"Default");

			_monster->GetMeshRenderer()->SetMesh(mesh);
			_monster->GetMeshRenderer()->SetMeterial(mat);
		}

		auto animator = make_shared<Animator>();
		_monster->AddComponent(animator);
		auto anim = RESOURCE->Get<Animation>(L"SnakeAnim");
		animator->SetAnimation(anim);

		scene->AddGameObject(_monster);

	}



	{
		shared_ptr<GameObject> _camera = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		{
			_camera->GetOrAddTransform();
			_camera->AddComponent(make_shared<Camera>());
			_camera->AddComponent(make_shared<CameraMove>());

		}
		scene->AddGameObject(_camera);
	}
		
	return scene;
}
