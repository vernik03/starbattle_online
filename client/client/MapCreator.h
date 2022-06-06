#pragma once
#include "Background.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Interface.h"

enum Rotation
{
	Top,
	Left,
	Bottom,
	Right
};

static class MapCreator //заведует всеми объектами на карте
{
public:
	MapCreator(){
		background = new Background();

		
		for (int i = 0; i < NUM_ASTEROIDS(); i++)
		{
			if (i < NUM_ASTEROIDS() / 2)
			{
				asteroids.push_back(new BigAsteroid(rand() % MAP_WIDTH, rand() % MAP_HEIGHT, rand() % 10 - 5, rand() % 10 - 5));
			}
			else
			{
				asteroids.push_back(new SmallAsteroid(rand() % MAP_WIDTH, rand() % MAP_HEIGHT, rand() % 10 - 5, rand() % 10 - 5));
			}
		}

		

		main_hero.SetCoords(rand() % MAP_WIDTH, rand() % MAP_HEIGHT);
		

	};
	~MapCreator(){};

	
	void AddShip(int x, int y, Rotation rot) {
		
	}

	void MapResize() {
		
	}
	
	void AddAsteroid(int x, int y, Rotation rot) {
		asteroids.push_back(new BigAsteroid(rand() % MAP_WIDTH, rand() % MAP_HEIGHT, rand() % 10 - 5, rand() % 10 - 5));
	}

	void DrawAll() {
		background->Draw();
		for (auto astroid : asteroids)
		{
			astroid->Draw();
		}
		for (auto ship : ships)
		{
			ship->Draw();
		}
		main_hero.Draw();
		inter.Draw();
	}
	
	//динамически увеличивать карту и добавлять астероиды при присоединении новых игроков
protected:
	std::vector<Asteroid*> asteroids;
	MainHeroShip main_hero;
	std::vector<Ship*> ships;
	Background* background;
	Interface inter;
	
};
