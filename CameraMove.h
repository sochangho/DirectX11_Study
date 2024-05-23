#pragma once
#include "MonoBehavior.h"


class CameraMove : public MonoBehavior
{
public:
	virtual void Update() override;

private :

	void Move(const Vec3& move);


private:

	float cameraSpeed = 10.f;
};