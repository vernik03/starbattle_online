#pragma once
#include <mutex>

#include "Background.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Interface.h"
#include "InfoToSend.h"
#include "InfoFromServer.h"


enum class ExplosionTypes {
	Big,
	Small,
	Huge
};

class Bullet : public HeadSprite
{
public:
	Bullet(int x, int y) {
		width = 20;
		height = 20;
		SetCoordsByCenter(x, y);
	};
	~Bullet() override {};
};

class Explosion : public HeadSprite
{
public:
	Explosion(int x, int y, int start, ExplosionTypes type) {
		if (type == ExplosionTypes::Big)
		{
			width = 384;
			height = 384;
		}
		else if (type == ExplosionTypes::Huge)
		{
			width = 1660;
			height = 1660;
		}
		else
		{
			width = 200;
			height = 200;
		}
		SetCoordsByCenter(x, y);
		start_tick = start;
		name = type;
	};
	~Explosion() override {};
	int start_tick;
	ExplosionTypes name;
};

class Power : public HeadSprite
{
public:
	Power(int x, int y, PowerTypes type) {
		if (type == PowerTypes::Shield)
		{
			width = 126;
			height = 126;
			SetCoordsByCenter(x, y);
		}
		else if (type == PowerTypes::Barrage)
		{
			width = 126;
			height = 126;
			SetCoordsByCenter(x, y);
		}
		else if (type == PowerTypes::Heal)
		{
			width = 126;
			height = 126;
			SetCoordsByCenter(x, y);
		}
		name = type;
	};
	~Power() override {};
	PowerTypes name;
};

class Base : public HeadSprite
{
public:
	Base() {
		width = 876;
		height = 876;
	};
	~Base() override {};

	void Draw(int x, int y) {
		if (hp > 0)
		{
			//std::cout << global_x << " " << global_y << "\n";
			drawSprite(base_sprites[0], x,y);	

			//std::cout << start_animation_time[0] << " " << tick_number << "\n";


			if (start_animation_time[0] != 0)
			{
				BlueLight(x, y, start_animation_time[0]);
			}

			if (start_animation_time[1] != 0)
			{
				RedLight(x, y, start_animation_time[1]);

			}

			if (start_animation_time[2] != 0)
			{
				BlueFace(x, y, start_animation_time[2]);
			}
			
			if (start_animation_time[3] != 0)
			{
				RedFace(x, y, start_animation_time[3]);
			}

			if (start_animation_time[4] != 0)
			{
				RedRoundLights(x, y, start_animation_time[3]);
			}
			
		}
	}

	void BlueLight(int x, int y, int& start_time) {
		if ((tick_number - start_time)%40 < 20)
		{

			drawSprite(base_sprites[2], x, y);
		}
		else
		{
			
			drawSprite(base_sprites[1], x, y);
		}		
	}

	void RedLight(int x, int y, int& start_time) {
		if ((tick_number - start_time) % 40 < 20)
		{

			drawSprite(base_sprites[4], x, y);
		}
		else
		{

			drawSprite(base_sprites[3], x, y);
		}
	}

	void BlueFace(int x, int y, int& start_time) {
		if ((tick_number - start_time) % 100 < 30)
		{

			drawSprite(base_sprites[5], x, y);
		}
		else
		{

			drawSprite(base_sprites[6], x, y);
		}
	}

	void RedFace(int x, int y, int& start_time) {
		if ((tick_number - start_time) % 100 < 30)
		{

			drawSprite(base_sprites[7], x, y);
		}
		else
		{

			drawSprite(base_sprites[8], x, y);
		}
	}

	void RedRoundLights(int x, int y, int& start_time) {
		drawSprite(base_sprites[9], x, y);
	}

	void SetHP(int hp_new) {
		hp = hp_new;
	}

	void SetStatus(int status_new) {
		if (status_new != status)
		{
			status = status_new;
				//std::cout << status << "\n";
			for (auto& time : start_animation_time)
			{
				time = 0;
			}


			if (status == 1)
			{
				start_animation_time[0] = tick_number;
				start_animation_time[2] = tick_number;
			}
			else if (status == 2)
			{
				start_animation_time[1] = tick_number;
				start_animation_time[3] = tick_number;
				start_animation_time[4] = tick_number;
			}
			
		}
	}
	

	int status = 0;
	int hp;

	std::vector<int> start_animation_time = { 0, 0, 0, 0, 0 };
	
};


class MapCreator 
{
public:
	MapCreator() {
		
		background = new Background();
		keep_info = new InfoToSend();
		UpdateRequest();

		for (int i = 1; i <= 7; i++)
		{
			big_explosion_sprites[i] = createSprite(("data/ships/explosions/big/" + std::to_string(i) + ".png").c_str());
		}

		for (int i = 1; i <= 50; i++)
		{
			huge_explosion_sprites[i] = createSprite(("data/ships/explosions/huge/" + std::to_string(i) + ".png").c_str());
		}

		AddBase();
		
		no_hp_sprite = createSprite("data/ships/hp/no_hp.png");
		hp_sprite = createSprite("data/ships/hp/hp.png");

		shield_sprites[1] = createSprite("data/ships/shields/1.png");
		shield_sprites[2] = createSprite("data/ships/shields/2.png");
		shield_sprites[3] = createSprite("data/ships/shields/3.png");

		for (int i = 1; i <= 7; i++)
		{
			ship_sprites[{i, Rotation::Left}] = createSprite(("data/ships/sprites/" + std::to_string(i) + "/spaceship_l.png").c_str());
			ship_sprites[{i, Rotation::Right}] = createSprite(("data/ships/sprites/" + std::to_string(i) + "/spaceship_r.png").c_str());
			ship_sprites[{i, Rotation::Top}] = createSprite(("data/ships/sprites/" + std::to_string(i) + "/spaceship.png").c_str());
			ship_sprites[{i, Rotation::Bottom}] = createSprite(("data/ships/sprites/" + std::to_string(i) + "/spaceship_b.png").c_str());

			engine_sprites[{i, Rotation::Left}] = createSprite(("data/ships/engines/" + std::to_string(i) + "/spaceship_power_l.png").c_str());
			engine_sprites[{i, Rotation::Right}] = createSprite(("data/ships/engines/" + std::to_string(i) + "/spaceship_power_r.png").c_str());
			engine_sprites[{i, Rotation::Top}] = createSprite(("data/ships/engines/" + std::to_string(i) + "/spaceship_power.png").c_str());
			engine_sprites[{i, Rotation::Bottom}] = createSprite(("data/ships/engines/" + std::to_string(i) + "/spaceship_power_b.png").c_str());
		}
		
		for (int i = 1; i <= 10; i++)
		{
			hp_sprites[i] = createSprite(("data/ships/hp/" + std::to_string(i) + ".png").c_str());
		}

		for (int i = 0; i <= 10; i++)
		{
			self_hp_sprites[i] = createSprite(("data/interface/self_hp/" + std::to_string(i) + ".png").c_str());
		}
		
	};
	~MapCreator() {};
	MapCreator(const MapCreator& other){
		asteroids = other.asteroids;
		ships = other.ships;
		explosions = other.explosions;
		powers = other.powers;
		bullets = other.bullets;
		main_hero = other.main_hero;
	};
	

	void AddMainHero(int x, int y, int sprite_id) {
		//se.playSoundEffect(5);
		const char* path = "data/ships/sprites/1/spaceship.png";
		main_hero.SetCoordsByCenter(x, y);
		main_hero.SetRotation(Rotation::Top);
		main_hero.sprite_id = sprite_id;

		window_x = main_hero.GetCenterGlobal().first - window_width / 2;
		window_y = main_hero.GetCenterGlobal().second - window_height / 2;
	}

	void AddBase() {
		base_sprites[0] = createSprite("data/base/base.png");

		base_sprites[1] = createSprite("data/base/blue/bottom_light.png");
		base_sprites[2] = createSprite("data/base/blue/top_light.png");
		
		base_sprites[3] = createSprite("data/base/red/bottom_light.png");
		base_sprites[4] = createSprite("data/base/red/top_light.png");

		base_sprites[5] = createSprite("data/base/blue/face_1.png");
		base_sprites[6] = createSprite("data/base/blue/face_2.png");
		
		base_sprites[7] = createSprite("data/base/red/face_1.png");
		base_sprites[8] = createSprite("data/base/red/face_2.png");
		
		base_sprites[9] = createSprite("data/base/red/lights.png");

	}

	void OldVersion() {
		std::cout << "Please update the game" << "\n";
	}


	void DrawAll() {
		
		background->Draw(main_hero.x_speed, main_hero.y_speed);

		for (auto& power : powers)
		{
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int x = power.xGlobal() + map_width * i - window_x;
					int y = power.yGlobal() + map_width * j - window_y;

					if (x > -BUFFER && x < window_width + BUFFER && y > -BUFFER && y < window_height + BUFFER)
					{
						if (power.name == PowerTypes::Shield)
						{
							drawSprite(small_shield_sprite, x, y);
						}
						else if (power.name == PowerTypes::Barrage)
						{
							drawSprite(small_barrage_sprite, x, y);
						}
						else if (power.name == PowerTypes::Heal)
						{
							drawSprite(small_heal_sprite, x, y);
						}
					}
				}
			}
		}
		for (auto& asteroid : asteroids)
		{
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int x = asteroid.xGlobal() + map_width * i - window_x;
					int y = asteroid.yGlobal() + map_width *j - window_y;
			
					if (x > -BUFFER && x < window_width + BUFFER && y > -BUFFER && y < window_height + BUFFER)
					{
						if (asteroid.name == AsteroidTypes::Big)
						{
							drawSprite(big_asteroid_sprite, x, y);
						}
						else if (asteroid.name == AsteroidTypes::Small)
						{
							drawSprite(small_asteroid_sprite, x, y);
						}
					}		
				}
			}
		}


		for (auto& bullet : bullets)
		{

			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int x = bullet.xGlobal() + map_width * i - window_x;
					int y = bullet.yGlobal() + map_width * j - window_y;

					if (x > -BUFFER && x < window_width + BUFFER && y > -BUFFER && y < window_height + BUFFER)
					{
						drawSprite(bullet_sprite, x, y);
					}
				}
			}
		}
		for (auto& ship : ships)
		{
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int x = ship.xGlobal() + map_width * i - window_x;
					int y = ship.yGlobal() + map_width * j - window_y;

					if (x > -BUFFER && x < window_width + BUFFER && y > -BUFFER && y < window_height + BUFFER)
					{						
						ship.DrawXY(x, y);
					}
				}
			}
			
		}
		if (death_ticks == 0)
		{
			main_hero.Draw();
		}
		
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				int x = base.xGlobal() + map_width * i - window_x;
				int y = base.yGlobal() + map_width * j - window_y;

				
					base.Draw(x, y);
				
			}
		}

		

		for (auto& explosion : explosions)
		{
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int x = explosion.xGlobal() + map_width * i - window_x;
					int y = explosion.yGlobal() + map_width * j - window_y;
			
					if (x > -BUFFER && x < window_width + BUFFER && y > -BUFFER && y < window_height + BUFFER)
					{
						int temp = tick_number - explosion.start_tick;
						if (explosion.name == ExplosionTypes::Huge)
						{
							//std::cout << tick_number << "\n";
							if (temp <= 6) {
								drawSprite(huge_explosion_sprites[1], x, y);
							}
							else if (temp >= 6 && temp <= 300)
							{
								drawSprite(huge_explosion_sprites[temp / 6], x, y);
							}
							if (temp == 6 || temp == 7)
							{

								se.playSoundEffect(6);
							}
							else if (temp == 100 || temp == 101)
							{

								se.playSoundEffect(6);
							}
						}
						else if (temp >= 4 && temp <= 28)
						{
							if (explosion.name == ExplosionTypes::Big)
							{
								drawSprite(big_explosion_sprites[temp/4], x, y);
							}
							else if (explosion.name == ExplosionTypes::Small)
							{
								drawSprite(small_explosion_sprites[temp / 4], x, y);
							}
							if (temp == 4 || temp == 5)
							{
								se.playSoundEffect(6);
							}
							
						}
					}		
				}
			}
		}
		

		if (death_ticks == 0)
		{
			if (main_hero.GetHP() > 0 && main_hero.GetHP() <= 10)
			{
				drawSprite(self_hp_sprites[main_hero.GetHP()], 600, 1000);
			}
		}
		else
		{
			drawSprite(self_hp_sprites[0], 600, 1000);
		}
	}


	void SetRot(int x, int y) {
		mouse_x = x;
		mouse_y = y;
		if (main_hero.GetRotationByMouse(mouse_x, mouse_y))
		{
			keep_info->SetCoords(mouse_x, mouse_y, main_hero.GetRotation());
		}
	}

	void SetKeyToRequest(FRKey k) {
		keep_info->SetKey(k);
	}

	void SetClickToRequest(FRMouseButton button, bool isReleased) {		
		keep_info->SetCoords(mouse_x, mouse_y, main_hero.GetRotation());
		keep_info->SetClick(button, isReleased);

		if (is_connected)
		{
			if (button == FRMouseButton::LEFT)
			{
				se.playSoundEffect(4);
			}
		}

	}

	void SetClosed() {
		keep_info->SetClose();
	}

	void UpdateRequest() {
	}

	void Shoot(int x, int y) {
		bullets.push_back(Bullet(x, y));
	}
	
protected:
	Background* background;
	Interface inter;

	int mouse_x = 1;
	int mouse_y = 1;

	InfoToSend* keep_info;
	
public:
	std::mutex mt;
	std::vector<Asteroid> asteroids;
	std::vector<Ship> ships;
	std::vector<Explosion> explosions;
	std::vector<Power> powers;
	std::vector<Bullet> bullets;
	MainHeroShip main_hero;
	Base base;
	Sprite* big_asteroid_sprite = createSprite("data/big_asteroid.png");
	Sprite* small_asteroid_sprite = createSprite("data/small_asteroid.png");
	Sprite* bullet_sprite = createSprite("data/bullet.png");
	Sprite* small_shield_sprite = createSprite("data/ships/shield_icon_small.png");
	Sprite* small_barrage_sprite = createSprite("data/ships/barrage_icon_small.png");
	Sprite* small_heal_sprite = createSprite("data/ships/heal_icon_small.png");
	
	const int BUFFER = 1000;
};
