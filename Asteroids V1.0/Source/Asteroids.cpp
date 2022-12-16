#include "Asteroids.h"

Asteroids::Asteroids(int size = 1, Vector2 pos = Vector2(0, 0), float angle = rand() % 180) : GameObject()
{
	if (size == 1)
		m_texture = LoadTexture("assets/Asteroid1.png");
	else if (size == 2)
		m_texture = LoadTexture("assets/AsteroidMedium.png");
	else
		m_texture = LoadTexture("assets/AsteroidMini.png");

	m_speed = 3;

	m_size = size;

	SetName("Asteroid");
	SetXPosition(pos.x);
	SetYPosition(pos.y);
	SetAngle(angle);
}

Asteroids::~Asteroids()
{
	Unload();
}

void Asteroids::Update() {
	Move();
}

void Asteroids::Render() {
	DrawTextureEx(m_texture, GetPosition(), GetAngle(), 1, RAYWHITE);
}

void Asteroids::Move() {
	float x_vec = (float)sin(m_angle * 3.14159265358979323846 / -180.0f);
	float y_vec = (float)cos(m_angle * 3.14159265358979323846 / 180.0f);

	float magnitude = (float)sqrt(x_vec * x_vec + y_vec * y_vec);

	SetXPosition(m_pos.x + x_vec / magnitude * m_speed);
	SetYPosition(m_pos.y + y_vec / magnitude * m_speed);
}

float Asteroids::GetRadius() {
	return (float)m_texture.width / 2;
}

int Asteroids::GetSize() {
	return m_size;
}

void Asteroids::Unload() {
	UnloadTexture(m_texture);
}