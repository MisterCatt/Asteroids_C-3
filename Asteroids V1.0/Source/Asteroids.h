#pragma once
#include "GameObject.h"
#include "Raylib.h"
class Asteroids : public GameObject
{
public:
	Asteroids(int size, Vector2 pos, float angle);
	~Asteroids();

	void Update();
	void Render();
	void Unload();

	float GetRadius() override;

	int GetSize();

private:

	void Move();

	int m_size;

};