#pragma once
#include "GameObject.h"
#include "Raylib.h"
class UFO : public GameObject
{
public:
	UFO();
	~UFO();

	void Update();
	void Render();
	void Unload();

	float GetAngle() override;

private:
	void Move();

	void NewAngle();

	int ufoAngleTimer, angleTimerBase;

	int deadTimer, baseDeadTimer;
};

