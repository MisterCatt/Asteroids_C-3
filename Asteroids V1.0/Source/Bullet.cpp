#include "Bullet.h"

Bullet::Bullet() : GameObject()
{
	m_texture = LoadTexture("assets/bullet.png");

	m_speed = 5;

	bulletTimer = 120;

	SetName("Bullet");

	SetXPosition(0);
	SetYPosition(0);
	SetAngle(0);
	setActive(false);
}

Bullet::~Bullet()
{
	Unload();
}

void Bullet::Update() {

	if (active) {
		Move();

		if (bulletTimer >= 0)
			bulletTimer--;

		if (bulletTimer <= 0) {
			Destroy();
		}
	}
}

void Bullet::Render() {
	if(active)
	DrawTextureEx(m_texture, GetPosition(), GetAngle(), 1, RAYWHITE);
}

void Bullet::Move() {
	float x_vec = (float)sin(m_angle * 3.14159265358979323846 / -180.0f);
	float y_vec = (float)cos(m_angle * 3.14159265358979323846 / 180.0f);

	float magnitude = (float)sqrt(x_vec * x_vec + y_vec * y_vec);

	SetXPosition(m_pos.x + x_vec / magnitude * m_speed);
	SetYPosition(m_pos.y + y_vec / magnitude * m_speed);
}

void Bullet::Destroy() {
	setActive(false);
}

void Bullet::Unload() {
	UnloadTexture(m_texture);
}

void Bullet::RestartTimer() {
	bulletTimer = 120;
}