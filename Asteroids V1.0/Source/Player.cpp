#pragma once

#pragma once
#include "Player.h"


Player::Player() : GameObject()
{
	m_texture = LoadTexture("assets/Player.png");

	shootSound = LoadSound("assets/shot.ogg");
	tpSound = LoadSound("assets/teleport.ogg");
	thrustSound = LoadSound("assets/thrust.ogg");

	SetXPosition(GetScreenWidth() / 2);
	SetYPosition(GetScreenHeight() / 2);
	SetName("Player");
	SetAngle(0);

	angle = m_angle = 0;

	cooldown = baseCooldownTimer = 20;
	tpCooldown = baseTpCooldownTimer = 60;
	deadTimer = 180;
	respawnTimer = 180;

	hasShot = false;

	dead = false;

	respawned = false;

}

Player::~Player()
{
	Unload();
}

bool Player::IsDead() {
	return dead;
}

void Player::Update() {
	if (active && !dead) {
		if (dead) {
			setActive(false);
			return;
		}

		Input();
		Move();

		if (respawned) {
			respawnTimer--;

			if (respawnTimer <= 0) {
				respawned = false;
				respawnTimer = 180;
			}
		}

		if (cooldown > 0) {
			cooldown--;
		}
		if (tpCooldown > 0) {
			tpCooldown--;
		}
	}
	if (!active && !dead) {
		deadTimer--;

		if (deadTimer <= 0) {
			SetXPosition(GetScreenWidth() / 2);
			SetYPosition(GetScreenHeight() / 2);
			SetAngle(0);

			respawned = true;
			setActive(true);
		}
	}
	

}

void Player::Render() {
	if(active)
	DrawTextureEx(m_texture, GetPosition(), m_angle, 1, RAYWHITE);
}

void Player::Input() {
	if (IsKeyDown(KEY_UP)) {
		angle = m_angle;
		if (m_speed < 5) {
			m_speed += 0.2f;
		}

		//THE SOUND IS BAD! UNCOMMENT AT YOUR OWN RISK
		/*if (!IsSoundPlaying(thrustSound)) {
			PlaySoundMulti(thrustSound);
		}*/
	}

	if (IsKeyDown(KEY_DOWN)) {
		if (m_speed <= 0)
			return;
		m_speed -= 0.2f;
	}
	if (IsKeyDown(KEY_LEFT)) {
		m_angle -= 5;
	}
	if (IsKeyDown(KEY_RIGHT)) {
		m_angle += 5;
	}
	if (IsKeyDown(KEY_SPACE)) {
		if (cooldown == 0) {
			hasShot = true;
			cooldown = baseCooldownTimer;

			PlaySoundMulti(shootSound);
		}
	}
	if (IsKeyPressed(KEY_Q)) {
		if (tpCooldown <= 0) {
			
			SetXPosition((float)(rand() % GetScreenWidth()));
			SetYPosition((float)(rand() % GetScreenHeight()));
			tpCooldown = baseTpCooldownTimer;


			PlaySoundMulti(tpSound);
		}
	}
}

void Player::Move() {
	float x_vec = (float)sin(angle * 3.14159265358979323846 / -180.0f);
	float y_vec = (float)cos(angle * 3.14159265358979323846 / 180.0f);

	float magnitude = (float)sqrt(x_vec * x_vec + y_vec * y_vec);

	SetXPosition(m_pos.x + x_vec / magnitude * m_speed);
	SetYPosition(m_pos.y + y_vec / magnitude * m_speed);

	if (m_speed > 0) {
		m_speed -= 0.1f;
	}
	if (m_speed < 0)
		m_speed = 0;
}

bool Player::HasShot() {
	return hasShot;
}

void Player::ResetShot() {
	hasShot = false;
}

void Player::Unload() {
	UnloadTexture(m_texture);

	StopSoundMulti();

	UnloadSound(shootSound);
	UnloadSound(tpSound);
	UnloadSound(thrustSound);
}