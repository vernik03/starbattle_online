#pragma once
#include "HeadSprite.h"

static class Background : public HeadSprite
{
public:
	Background() {
		sprite = createSprite("data/background_2.png");
		width = 1000;
		height = 1000;
	};
	~Background();

	void Draw() override {
		for (int i = 1; i <= MAP_WIDTH / width + 1; i++)
		{
			for (int i = 1; i <= MAP_HEIGHT / height + 1; i++)
			{
				drawSprite(sprite, (global_x - WINDOW_X) * i, (global_y - WINDOW_Y) * i);
			}
		}		
	}
};