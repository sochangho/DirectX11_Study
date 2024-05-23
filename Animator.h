#pragma once

#include "Component.h"
#include "Animation.h"


class Animator : public Component
{
	using Super = Component;
public:
	Animator();
	~Animator();

	void Init();

	virtual void Awake() override;
	virtual void Start() override;

	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FixedUpdate() override;


	shared_ptr<Animation> GetCurrentAnimation();
	const Keyframe& GetCurrentKeyfram();

	void SetAnimation(shared_ptr<Animation> animation) { _currentAnimation = animation; }

private:
	float _sumTime = 0.f;

	int32 _currentKeyframeIndex = 0;
	shared_ptr<Animation> _currentAnimation;

};

