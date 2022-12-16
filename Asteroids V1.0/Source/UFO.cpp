#include "UFO.h"
UFO::UFO() : GameObject()
{
	m_texture = LoadTexture("assets/UFO.png");

	SetAngle((float)(rand() % 180));
	SetName("UFO");

	m_speed = 3;

	ufoAngleTimer = angleTimerBase = 240;
	deadTimer = baseDeadTimer = 520;

	active = true;
}

UFO::~UFO()
{
	Unload();
}

void UFO::Move() {
	float x_vec = (float)sin(m_angle * 3.14159265358979323846 / -180.0f);
	float y_vec = (float)cos(m_angle * 3.14159265358979323846 / 180.0f);

	float magnitude = (float)sqrt(x_vec * x_vec + y_vec * y_vec);

	SetXPosition(m_pos.x + x_vec / magnitude * m_speed);
	SetYPosition(m_pos.y + y_vec / magnitude * m_speed);
}

void UFO::Update() {
	if (isActive()) {

		if (ufoAngleTimer == 0) {
			NewAngle();
			ufoAngleTimer = angleTimerBase;
		}

		Move();

		ufoAngleTimer--;
	}
	else {
		SetXPosition((float)(GetScreenWidth() * 6));
		SetYPosition((float)(GetScreenHeight() * 6));

		deadTimer--;
		if (deadTimer <= 0) {
			SetXPosition((float)(rand() % GetScreenWidth()));
			SetYPosition((float)(rand() % GetScreenHeight()));

			SetAngle((float)(rand() % 180));

			deadTimer = baseDeadTimer;

			setActive(true);
		}
	}
}

void UFO::Render() {
	if (isActive())
		DrawTextureEx(m_texture, GetPosition(), 0, 1, RAYWHITE);
}

void UFO::NewAngle() {
	m_angle = (float)(rand() % 180);
}

float UFO::GetAngle() {
	return m_angle;
}

void UFO::Unload() {
	UnloadTexture(m_texture);
}
