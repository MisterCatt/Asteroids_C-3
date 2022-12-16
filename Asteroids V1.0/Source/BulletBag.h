#pragma once
#include <iostream>
#include <deque>
#include "Bullet.h"

//code taken from https://youtu.be/Mq2zYk5tW_E
class BulletBag
{
public:
	static BulletBag& instance()
	{
		static BulletBag INSTANCE;
		return INSTANCE;
	};
	~BulletBag();

	void Unload();

	Bullet* GetBullet();

	int BulletsInBag();
private:

	std::deque<Bullet*> bullets;
	bool notEnoughBulletsInBag = true;

	
};
