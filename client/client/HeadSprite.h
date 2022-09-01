#pragma once
#include <iostream>
#include <vector>
#include "Framework.h"
#include "GlobalVariables.h"

class HeadSprite {
public:
	HeadSprite() {
		height = 0;
		width = 0;		
	};
	HeadSprite(int sprite_width, int sprite_height) : width(sprite_width), height(sprite_height) {
	};

	virtual ~HeadSprite() {};

	virtual void SetCoords(int new_x, int new_y) {
		global_x = new_x;
		global_y = new_y;
	}

	virtual void SetCoordsByCenter(int new_x, int new_y) {
		global_x = new_x - width / 2;
		global_y = new_y - height / 2;
	}


	std::pair<int, int> GetCenterGlobal() {
		return std::make_pair(global_x + width / 2, global_y + height / 2);
	}

	std::pair<int, int> GetCenter() {
		return std::make_pair(x() + width / 2, y() + height / 2);
	}

	int xGlobal() {
		return global_x;
	}

	int yGlobal() {
		return global_y;
	}

	int x() {
		return global_x - window_x;
	}

	int y() {
		return global_y - window_y;
	}

	virtual std::string GetName() {
		return "HeadSprite";
	}
	
	std::pair<int, int> GetSize() {
		return std::make_pair(width, height);
	}

protected:
	int width;
	int height;
	int global_x;
	int global_y;
};
