#pragma once
#include "GameObject.h"
#include "raylib.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Update();
	void Render();
	void Unload();
	bool HasShot();
	void ResetShot();

	bool IsDead();

private:
	void Input();

	void Move();

	bool hasShot, dead, respawned;
	int cooldown, tpCooldown, baseCooldownTimer, baseTpCooldownTimer, deadTimer, respawnTimer;

	Sound shootSound, tpSound, thrustSound;

	float angle;

};