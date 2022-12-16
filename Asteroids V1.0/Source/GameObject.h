#pragma once
#include "raylib.h"
#include <iostream>

class GameObject {
public:

	GameObject();
	~GameObject();

	virtual Vector2 GetPosition();
	virtual void SetXPosition(float x);
	virtual void SetYPosition(float y);
	virtual void SetAngle(float angle);
	virtual float GetAngle();

	virtual float GetRadius();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Unload() = 0;

	virtual void setActive(bool activeStatus);
	virtual bool isActive();

	virtual std::string GetName();
	virtual void SetName(std::string name);

protected:

	Vector2 m_pos;

	std::string m_name;

	Texture2D m_texture;
	Sound shootSound, tpSound, thrustSound;

	float m_speed, m_angle;
	

	bool active;
};