#include "pch.h"
#include "CameraMove.h"
#include "Game.h"
#include "InputManager.h"
#include "TimeManager.h"

void CameraMove::Update()
{
	if (INPUT->GetButton(KEY_TYPE::W)) {

		Move(Vec3(0.0f, 0.1f, 0.f));
	}
	else if (INPUT->GetButton(KEY_TYPE::A)) {

		Move(Vec3(-0.1f, 0.f, 0.f));
	}
	else if (INPUT->GetButton(KEY_TYPE::S)) {

		Move(Vec3(0.f, -0.1f, 0.f));
	}
	else if (INPUT->GetButton(KEY_TYPE::D)) {

		Move(Vec3(0.1f, 0.f, 0.f));
	}

}


void CameraMove::Move(const Vec3& move)
{
	auto current_pos = GetGameObject()->GetOrAddTransform()->GetPosition();

	current_pos += move * cameraSpeed * TIME->GetDeltaTime();

	GetGameObject()->GetOrAddTransform()->SetPosition(current_pos);
}
