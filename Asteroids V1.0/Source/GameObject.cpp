#include "GameObject.h"

GameObject::GameObject() {
	m_angle = m_angle = 0.0f;
	m_speed = 0;
	setActive(true);
}

GameObject::~GameObject() {

}

Vector2 GameObject::GetPosition() {
	return m_pos;
}

void GameObject::SetXPosition(float x) {
	m_pos.x = x;
}

void GameObject::SetYPosition(float y) {
	m_pos.y = y;
}

std::string GameObject::GetName() {
	return m_name;
}

void GameObject::SetName(std::string name) {
	m_name = name;
}

void GameObject::SetAngle(float angle) {
	m_angle = angle;
}

float GameObject::GetAngle() {
	return m_angle;
}

void GameObject::setActive(bool activeStatus) {
	active = activeStatus;
}

bool GameObject::isActive() {
	return active;
}

float GameObject::GetRadius() {
	return (float)m_texture.width;
}