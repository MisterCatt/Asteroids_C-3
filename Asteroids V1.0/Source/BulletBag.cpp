#include "BulletBag.h"

BulletBag::~BulletBag()
{
	Unload();
}

Bullet* BulletBag::GetBullet() {
	if (bullets.size() > 0) {
		for (int i = 0; i < bullets.size(); i++) {
			if (!bullets[i]->isActive()) {
				std::cout << "Bullet has been aquired" << std::endl;
				return bullets[i];
			}
		}
	}

	if (notEnoughBulletsInBag) {
		Bullet* bul = new Bullet();
		bullets.push_back(bul);
		std::cout << "Bullet has been aquired" << std::endl;
		return bul;
	}

	return nullptr;
}

int BulletBag::BulletsInBag() {
	return bullets.size();
}

void BulletBag::Unload() {
	bullets.clear();
}
