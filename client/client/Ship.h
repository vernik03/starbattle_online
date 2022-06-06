#pragma once
#include "HeadSprite.h"
#include "SuperPower.h"

class Ship : public HeadSprite
{
public:
	Ship() {};
	Ship(const char* sprite_path, double sprite_width, double sprite_height, int sprite_mass) {
		sprite = createSprite(sprite_path);
		width = sprite_width;
		height = sprite_height;
	};
	virtual ~Ship() {};

	
	void SetRotation(Rotation rot) {
		rotation = rot;
	}



	void PowersHandler(int x, int y) {
		if (dynamic_cast<Shield*>(power))
		{
			power->SetCoords(x, y);
		}
		else if (dynamic_cast<Rocket*>(power))
		{
			//	
		}
	}

	

	void Draw() override {
		drawSprite(sprite, x(), y());
		if (power)
		{
			power->Draw();
		}
		for (auto bullet : bullets)
		{
			bullet->Draw();
		}
		
	} 


	void Shoot(int x, int y) {
		bullets.push_back(new Bullet(x, y));
	}

protected:
	HeadSprite* power;  //?
	Rotation rotation;	
	std::vector<Bullet*> bullets;
	Sprite* engine;
};

class MainHeroShip : public Ship
{
public:
	MainHeroShip() {
		sprite = createSprite("data/ships/main_hero/spaceship.png");
		engine = createSprite("data/ships/main_hero/engine.png");
		width = 48;
		height = 48;
		rotation = Rotation::Top;
	};
	~MainHeroShip() {};

	void GetRotationByMouse(int x_mouse, int y_mouse) {
		if (x_mouse <= WINDOW_WIDTH / 2) {
			if (abs(x_mouse - WINDOW_WIDTH / 2) > abs(y_mouse - WINDOW_WIDTH / 2))
				SetRotation(Rotation::Left);
			else {
				if (y_mouse <= WINDOW_HEIGHT / 2)
					SetRotation(Rotation::Top);
				else
					SetRotation(Rotation::Bottom);
			}
		}
		else {
			if (abs(x_mouse - WINDOW_WIDTH / 2) > abs(y_mouse - WINDOW_WIDTH / 2))
				SetRotation(Rotation::Right);
			else {
				if (y_mouse <= WINDOW_HEIGHT / 2)
					SetRotation(Rotation::Top);
				else
					SetRotation(Rotation::Bottom);
			}
		}
	}


	void SendMouseMoveEvent(int x, int y) {
		GetRotationByMouse(x, y);
	};

	



private:
	
};

class EnemyShip : public Ship
{
public:
	EnemyShip(int x, int y, Rotation rot) {
		sprite = createSprite("data/ships/enemy/spaceship.png");
		width = 48;
		height = 48;
		SetRotation(rot);
		global_x = x;
		global_y = y;
	};
	~EnemyShip() {};

private:

};


class Bullet : public HeadSprite
{
public:
	Bullet(int x, int y) {
		sprite = createSprite("data/bullet.png");
		width = 13;
		height = 13;
		global_x = x;
		global_y = y;
	};
	~Bullet() {};

};