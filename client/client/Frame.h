#pragma once
#include <string>
#include <algorithm>
#include <map>

#include "Framework.h"

enum class Elements
{
	top_left,
	top,
	top_right,
	right,
	bottom_right,
	bottom,
	bottom_left,
	left,
	center
};

struct Elem {
	Sprite* symbol;
	int height;
	int width;
};

class Frame
{
public:
	Frame(){
		frame_elements[Elements::center].symbol = createSprite("data/frame/center.png");
		frame_elements[Elements::center].height = 199;
		frame_elements[Elements::center].width = 199;

		frame_elements[Elements::bottom_left].symbol = createSprite("data/frame/corner_bottom_left.png");
		frame_elements[Elements::bottom_left].height = 820;
		frame_elements[Elements::bottom_left].width = 820;

		frame_elements[Elements::bottom_right].symbol = createSprite("data/frame/corner_bottom_right.png");
		frame_elements[Elements::bottom_right].height = 820;
		frame_elements[Elements::bottom_right].width = 820;

		frame_elements[Elements::top_left].symbol = createSprite("data/frame/corner_top_left.png");
		frame_elements[Elements::top_left].height = 820;
		frame_elements[Elements::top_left].width = 820;

		frame_elements[Elements::top_right].symbol = createSprite("data/frame/corner_top_right.png");
		frame_elements[Elements::top_right].height = 820;
		frame_elements[Elements::top_right].width = 820;

		frame_elements[Elements::bottom].symbol = createSprite("data/frame/side_bottom.png");
		frame_elements[Elements::bottom].height = 820;
		frame_elements[Elements::bottom].width = 199;

		frame_elements[Elements::top].symbol = createSprite("data/frame/side_top.png");
		frame_elements[Elements::top].height = 820;
		frame_elements[Elements::top].width = 199;

		frame_elements[Elements::left].symbol = createSprite("data/frame/side_left.png");
		frame_elements[Elements::left].height = 199;
		frame_elements[Elements::left].width = 820;

		frame_elements[Elements::right].symbol = createSprite("data/frame/side_right.png");
		frame_elements[Elements::right].height = 199;
		frame_elements[Elements::right].width = 820;
	};
	~Frame(){};

	void print_frame(int x, int y,
		int width_counter = 0,
		int height_counter = 0) {

		//by center
		x -= ((820 - 562) + (width_counter * frame_elements[Elements::top].width)/2);
		y -= ((820 - 562) + (height_counter * frame_elements[Elements::left].height)/2);
		//

		x -= 562;
		y -= 562;

		drawSprite(frame_elements[Elements::top_left].symbol, x, y);
		int x_temp = x + frame_elements[Elements::top_left].width;
		int y_temp = y + frame_elements[Elements::top_left].height;
		if (width_counter > 0)
		{	
			for (int i = 0; i < width_counter; i++)
			{	
				drawSprite(frame_elements[Elements::top].symbol, x_temp, y);
				x_temp += frame_elements[Elements::top].width;
			}
			
		}
		

		if (height_counter > 0)
		{
			for (int i = 0; i < height_counter; i++)
			{
				drawSprite(frame_elements[Elements::left].symbol, x, y_temp);
				y_temp += frame_elements[Elements::left].height;
			}

		}

		drawSprite(frame_elements[Elements::top_right].symbol, x_temp, y);
		drawSprite(frame_elements[Elements::bottom_left].symbol, x, y_temp);

		int x_temp_for_height = x_temp;
		int y_temp_for_width = y_temp;
		x_temp = x + frame_elements[Elements::top_left].width;
		y_temp = y + frame_elements[Elements::top_left].height;

		if (width_counter > 0)
		{
			for (int i = 0; i < width_counter; i++)
			{
				drawSprite(frame_elements[Elements::bottom].symbol, x_temp, y_temp_for_width);
				x_temp += frame_elements[Elements::bottom].width;
			}

		}
		if (height_counter > 0)
		{
			for (int i = 0; i < height_counter; i++)
			{
				drawSprite(frame_elements[Elements::right].symbol, x_temp_for_height, y_temp);
				y_temp += frame_elements[Elements::right].height;
			}

		}

		drawSprite(frame_elements[Elements::bottom_right].symbol, x_temp, y_temp);
		
		if (height_counter > 0 && width_counter > 0)
		{
			x_temp = x + frame_elements[Elements::top_left].width;
			y_temp = y + frame_elements[Elements::top_left].height;
			for (int i = 0; i < height_counter; i++)
			{
				for (int j = 0; j < width_counter; j++)
				{
					drawSprite(frame_elements[Elements::center].symbol, x_temp, y_temp);
					x_temp += frame_elements[Elements::center].width;
				}
				x_temp = x + frame_elements[Elements::left].width;
				y_temp += frame_elements[Elements::center].height;
			}
			
		}

	}

private:

	std::map<Elements, Elem> frame_elements;

};