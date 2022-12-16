#pragma once
#include "Player.h"
#include <deque>
#include<cmath>
#include <iostream>
#include "Raylib.h"
#include <string>
#include "Bullet.h"
#include "BulletBag.h"
#include "Asteroids.h"
#include "UFO.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void Update();
	void Render();

	void UIRender();

	void WorldWrap(GameObject& obj);

	void OnCollision(GameObject& obj1, GameObject& obj2);

	void PlayerUpdate();
	void BulletUpdate();
	void AsteroidUpdate();
	void UFOUpdate();

	void DeleteAll();

	Player* m_player;

	std::deque<Asteroids*> asteroidsArray;

	BulletBag* bulletBag;

	std::deque<Bullet*> renderBullets;
	UFO* ufo;

	Texture2D playerLifeTexture;

	bool deleted;

	int bigAsteroidScore, mediumAsteroidScore, smallAsteroidScore, 
		UFOScore, score, lives, deadTimer, UFOBulletTimer;
};