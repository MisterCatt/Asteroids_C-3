//Daniel Mardunovich Dama7895
#include "Game.h"

Game::Game()
{
	m_player = new Player();
	ufo = new UFO();

	bulletBag = new BulletBag();

	asteroidsArray.push_back(new Asteroids(1, Vector2((float)(rand() % GetScreenWidth()), (float)(rand() % GetScreenHeight())), (float)(rand() % 180)));
	asteroidsArray.push_back(new Asteroids(1, Vector2((float)(rand() % GetScreenWidth()), (float)(rand() % GetScreenHeight())), (float)(rand() % 180)));
	asteroidsArray.push_back(new Asteroids(1, Vector2((float)(rand() % GetScreenWidth()), (float)(rand() % GetScreenHeight())), (float)(rand() % 180)));

	playerLifeTexture = LoadTexture("assets/Player.png");

	lives = 3;
	deadTimer = 160;

	score = 0;

	bigAsteroidScore = 20;
	mediumAsteroidScore = 70;
	smallAsteroidScore = 140;
	UFOScore = 300;

	UFOBulletTimer = 120;

	deleted = false;
}

Game::~Game()
{
	DeleteAll();
}

void Game::run()
{
	Update();
	Render();
}

void Game::Update()
{
	if (lives > 0) {
		PlayerUpdate();

		BulletUpdate();

		AsteroidUpdate();

		UFOUpdate();
	}
	else {
		if (!deleted)
			DeleteAll();
	}

	
}

void Game::Render()
{
	if (lives > 0) {
			m_player->Render();

		for (int i = 0; i < renderBullets.size(); i++) {
			if (renderBullets[i]->isActive())
				renderBullets[i]->Render();
			else {
				renderBullets.erase(renderBullets.begin() + i);
			}
		}

		for (int i = 0; i < asteroidsArray.size(); i++) {
			if (asteroidsArray[i]->isActive())
				asteroidsArray[i]->Render();
		}

		ufo->Render();
	}

		UIRender();
	
}

//Code that helps with worldwrapping for every GameObject
void Game::WorldWrap(GameObject& obj) {
	if (obj.GetPosition().x > GetScreenWidth()) {
		obj.SetXPosition(0);
	}
	if (obj.GetPosition().y > GetScreenHeight()) {
		obj.SetYPosition(0);
	}
	if (obj.GetPosition().x < 0) {
		obj.SetXPosition((float)GetScreenWidth());
	}
	if (obj.GetPosition().y < 0) {
		obj.SetYPosition((float)GetScreenHeight());
	}


}

//help from https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
void Game::OnCollision(GameObject& obj1, GameObject& obj2) {
	if (!obj1.isActive() || !obj2.isActive())
		return;

	float o1x = ((obj1.GetPosition().x + obj1.GetRadius() / 2) + obj1.GetRadius()) - ((obj2.GetPosition().x + obj2.GetRadius()/2) + obj2.GetRadius());
	float o2y = ((obj1.GetPosition().y - obj1.GetRadius()/2) + obj1.GetRadius()) - ((obj2.GetPosition().y - obj2.GetRadius()/2) + obj2.GetRadius());
	float distance = std::sqrt(o1x * o1x + o2y * o2y);

	//Show hitboxes
	/*DrawCircle((obj1.GetPosition().x) + obj1.GetRadius(), (obj1.GetPosition().y) + obj1.GetRadius(), obj1.GetRadius(), RED);
	DrawCircle((obj2.GetPosition().x) + obj2.GetRadius(), (obj2.GetPosition().y) + obj2.GetRadius(), obj2.GetRadius(), RED);*/

	if (distance < obj1.GetRadius() + obj2.GetRadius()) {

		if (obj1.GetName() == "PLAYERBULLET" || obj2.GetName() == "PLAYERBULLET") {
			if (obj1.GetName() == "UFO" || obj2.GetName() == "UFO" || obj1.GetName() == "Asteroid" || obj2.GetName() == "Asteroid") {
				//PlaySoundMulti(boom);

				obj1.setActive(false);
				obj2.setActive(false);

				if(obj1.GetName() == "UFO" || obj2.GetName() == "UFO")
				score += UFOScore;
			}
		}
		if (obj1.GetName() == "UFOBULLET" || obj2.GetName() == "UFOBULLET") {
			if (obj1.GetName() == "Player" || obj2.GetName() == "Player" ) {
					//PlaySoundMulti(boom);
				obj1.setActive(false);
				obj2.setActive(false);
					
					lives--;
			}
		}
		if (obj1.GetName() == "Asteroid" || obj2.GetName() == "Asteroid") {
			if (obj1.GetName() == "Player" || obj2.GetName() == "Player" ) {
				//PlaySoundMulti(boom);
				obj1.setActive(false);
				obj2.setActive(false);

				lives--;

			}
		}
	}
}

void Game::PlayerUpdate()
{
	m_player->Update();

	if (m_player->HasShot()) {
		Bullet* bul = bulletBag->instance().GetBullet();
		bul->SetName("PLAYERBULLET");
		bul->SetAngle(m_player->GetAngle());
		bul->SetXPosition(m_player->GetPosition().x);
		bul->SetYPosition(m_player->GetPosition().y);
		bul->RestartTimer();

		bul->setActive(true);

		renderBullets.push_back(bul);
	}
	m_player->ResetShot();
	WorldWrap(*m_player);
}

void Game::AsteroidUpdate() {
	for (Asteroids* a : asteroidsArray) {
		a->Update();
		WorldWrap(*a);
		OnCollision(*a, *m_player);
	}

	for (int i = 0; i < asteroidsArray.size(); i++) {
		if (!asteroidsArray.at(i)->isActive()) {
			if (asteroidsArray.at(i)->GetSize() == 1) {
				score += bigAsteroidScore;
				asteroidsArray.push_back(new Asteroids(2, asteroidsArray.at(i)->GetPosition(), asteroidsArray.at(i)->GetAngle() + 40));
				asteroidsArray.push_back(new Asteroids(2, asteroidsArray.at(i)->GetPosition(), asteroidsArray.at(i)->GetAngle() - 40));
			}
			else if (asteroidsArray.at(i)->GetSize() == 2) {
				score += mediumAsteroidScore;
				asteroidsArray.push_back(new Asteroids(3, asteroidsArray.at(i)->GetPosition(), asteroidsArray.at(i)->GetAngle() + 40));
				asteroidsArray.push_back(new Asteroids(3, asteroidsArray.at(i)->GetPosition(), asteroidsArray.at(i)->GetAngle() - 40));
				asteroidsArray.push_back(new Asteroids(3, asteroidsArray.at(i)->GetPosition(), asteroidsArray.at(i)->GetAngle() + 20));
				asteroidsArray.push_back(new Asteroids(3, asteroidsArray.at(i)->GetPosition(), asteroidsArray.at(i)->GetAngle() - 20));
			}
			else {
				score += smallAsteroidScore;
			}
			asteroidsArray.erase(asteroidsArray.begin() + i);
		}
	}

	if (asteroidsArray.size() == 0) {
		asteroidsArray.push_back(new Asteroids(1, Vector2((float)(rand() % GetScreenWidth()), (float)(rand() % GetScreenHeight())), (float)(rand() % 180)));
		asteroidsArray.push_back(new Asteroids(1, Vector2((float)(rand() % GetScreenWidth()), (float)(rand() % GetScreenHeight())), (float)(rand() % 180)));
		asteroidsArray.push_back(new Asteroids(1, Vector2((float)(rand() % GetScreenWidth()), (float)(rand() % GetScreenHeight())), (float)(rand() % 180)));
	}
}

void Game::UFOUpdate()
{
	ufo->Update();
	WorldWrap(*ufo);

	OnCollision(*ufo, *m_player);

	if (UFOBulletTimer == 0) {
		Bullet* bul = bulletBag->instance().GetBullet();
		bul->SetName("UFOBULLET");
		bul->SetAngle((float)(rand() % 180));
		bul->SetXPosition(ufo->GetPosition().x);
		bul->SetYPosition(ufo->GetPosition().y);
		bul->RestartTimer();

		bul->setActive(true);

		renderBullets.push_back(bul);

		UFOBulletTimer = 120;
	}
	UFOBulletTimer--;
}


void Game::DeleteAll()
{
	asteroidsArray.clear();
	renderBullets.clear();

	UnloadTexture(playerLifeTexture);

	delete bulletBag;
	bulletBag = nullptr;

	delete m_player;
	m_player = nullptr;

	delete ufo;
	ufo = nullptr;

	deleted = true;
}

void Game::BulletUpdate() {
	for (Bullet* b : renderBullets) {
		if (b->isActive()) {
			b->Update();
			WorldWrap(*b);

			OnCollision(*b, *m_player);
			OnCollision(*b, *ufo);

			for(int i = 0; i < asteroidsArray.size(); i++)
			OnCollision(*b, *asteroidsArray[i]);
		}
	}

	for (int i = 0; i < renderBullets.size(); i++) {
		if (!renderBullets[i]->isActive())
			renderBullets.erase(renderBullets.begin() + i);
	}
}

void Game::UIRender() {
	if (lives > 0) {
		int spacing = 15;
		for (int i = 0; i < lives; i++) {
			DrawTextureEx(playerLifeTexture, Vector2{ (float)GetScreenWidth() / 6 + 100 + spacing, (float)GetScreenHeight() / 6 }, 0, 0.5, RAYWHITE);
			spacing += 15;
		}
		DrawText(TextFormat("Lives: "), GetScreenWidth() / 6, GetScreenHeight() / 6, 12, WHITE);
		DrawText(TextFormat("score: %d", score), GetScreenWidth() / 6, GetScreenHeight() / 8, 12, WHITE);
	}
	else {
		DrawText(TextFormat("You are dead!"), GetScreenWidth() / 6, GetScreenHeight() / 8, 12, WHITE);
		DrawText( TextFormat("Final score: %d", score), GetScreenWidth() / 2 - 100, (int)(GetScreenHeight() / 2), 24, WHITE);

	}
}
