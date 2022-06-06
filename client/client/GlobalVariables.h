#pragma once
inline int WINDOW_WIDTH = 800;
inline int WINDOW_HEIGHT = 600;
inline int MAP_WIDTH = 1000;
inline int MAP_HEIGHT = 1000;
inline int NUM_ASTEROIDS_BIG = 5;
inline int NUM_ASTEROIDS_SMALL = 5;
inline int NUM_AMMO = 3;
inline double ABILITY_PROBABILITY = 0.5;
inline double WINDOW_X = 200;
inline double WINDOW_Y = 200;
inline int PERSONAL_ID = 333;

int NUM_ASTEROIDS() {
	return NUM_ASTEROIDS_BIG + NUM_ASTEROIDS_SMALL;
}