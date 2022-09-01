#pragma once
#pragma once
#include "HeadSprite.h"

enum class AsteroidTypes {
	Big,
	Small
};

class Asteroid : public HeadSprite
{
public:
	Asteroid() {};
	Asteroid(int x, int y, AsteroidTypes type){
		if (type == AsteroidTypes::Big)
		{
			width = 100;
			height = 88;
		}
		else if (true)
		{
			width = 60;
			height = 49;
		}		
		SetCoordsByCenter(x, y);

		name = type;
	};

	virtual ~Asteroid() = default;


	AsteroidTypes name;
};


