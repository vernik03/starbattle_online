#pragma once
#include "HeadSprite.h"

class SuperPower : public HeadSprite
{
public:
	SuperPower() {


		
	};
	
	~SuperPower(){};

private:

};

class SuperPowerIcon : public HeadSprite
{
public:
	SuperPowerIcon();
	~SuperPowerIcon();

private:

};


class Shield : public SuperPower
{
public:
	Shield(){
		sprite = createSprite(frames[0]);
		width = 63;
		height = 63;
		shield_duration = 80;
		start_time = getTickCount();
	};
	~Shield(){};

	void FillFramesVector() {
		frames.push_back("data/ships/shield.png");
		frames.push_back("data/ships/shield_02.png");
		frames.push_back("data/ships/shield_03.png");
	}
	

	virtual void Draw() override {
		if (getTickCount() >= start_time + shield_duration)
		{
			delete this;
			return;
		}
		int parts = shield_duration / frames.size();
		int temp = getTickCount() - start_time;
		int i = -1;
		while (temp > 0)
		{
			temp -= parts;
			i++;
		}
		sprite = createSprite(frames[i]);
		
		drawSprite(sprite, x(), y());
		

	}

private:
	unsigned int shield_duration;
	unsigned int start_time;
	std::vector<const char*> frames;
};

class Rocket : public SuperPower
{
public:
	Rocket(){};
	~Rocket(){};

private:

};