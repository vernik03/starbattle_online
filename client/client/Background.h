#pragma once
#include "HeadSprite.h"

class Background : public HeadSprite
{
public:
	Background() {
		//sprite = createSprite("data/background_very_big.png");
		backgrounds[0] = createSprite("data/background_very_big.png");
		backgrounds[1] = createSprite("data/background_very_big_fast_horisontal_0.png");
		backgrounds[2] = createSprite("data/background_very_big_fast_horisontal_1.png");
		backgrounds[3] = createSprite("data/background_very_big_fast_vertical_0.png");
		backgrounds[4] = createSprite("data/background_very_big_fast_vertical_1.png");
		width = 4000;
		height = 4000;
	};
	~Background() {};

	void Draw(double x_speed, double y_speed) {
		for (int i = 0; i < map_width / width; i++)
		{
			for (int j = 0; j < map_height / height; j++)
			{
				for (int k = -1; k <= 1; k++)
				{
					for (int t = -1; t <= 1; t++)
					{
						int x = -1 * window_x/4 + i * width + map_width * k;
						int y = -1 * window_y/4 + j * height + map_width * t ;

						if (abs(x_speed) > 30)
						{
							drawSprite(backgrounds[1], x, y);
						}
						else if (abs(x_speed) > 20)
						{
							drawSprite(backgrounds[2], x, y);
						}
						else if (abs(y_speed) > 30)
						{
							drawSprite(backgrounds[3], x, y);
						}
						else if (abs(y_speed) > 20)
						{
							drawSprite(backgrounds[4], x, y);
						}
						else
						{
							drawSprite(backgrounds[0], x, y);
						}
					}
				}
			}
		}
	}

	//Sprite* sprite;
};