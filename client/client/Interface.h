#pragma once
#include "HeadSprite.h"
#include "Framework.h"
#include <map>
#include <windows.h>
#include <shellapi.h>

class Interface;
class Reticle;

class Reticle : public HeadSprite
{
public:
	Reticle() {
		sprite_path = "data/reticle2.png";
		sprite = createSprite(sprite_path);		
		width = 126;
		height = 126;
	};
	~Reticle(){};

	void SetCoords(int new_x, int new_y) override {
		global_x = new_x - height / 2 + window_x;
		global_y = new_y - width / 2 + window_y;
	}


	void SetSprite(const char* sprite_path) {
		sprite = createSprite(sprite_path);
	}

	void Draw() {
		drawSprite(sprite, x(), y());
	}

	const char* sprite_path;
	Sprite* sprite;
	
};

class Close : public HeadSprite
{
public:
	Close() {
		sprite_path = "data/interface/close.png";
		sprite = createSprite(sprite_path);
		width = 58;
		height = 58;

		
	};
	~Close() {};


	void Draw() {
		drawSprite(sprite, 1814, 48);
	}

	const char* sprite_path;
	Sprite* sprite;

};



class MainMenu
{
public:
	MainMenu() {
		main_menu_background = createSprite("data/interface/main_menu/background.png");
		play_button = createSprite("data/interface/main_menu/play_button.png");
		about_button = createSprite("data/interface/main_menu/about_button.png");
		exit_button = createSprite("data/interface/game_over/exit_button.png");
		score_button = createSprite("data/interface/main_menu/score_button.png");
	};
	~MainMenu() {};


	void Draw() {
		drawSprite(main_menu_background, 0, 0);
		drawSprite(play_button, 830, 634);
		/*if (is_hover["score_button"])
		{
			drawSprite(score_button, 127, 935);
		}
		else
		{
			drawSprite(score_button, 127, 940);
		}*/
		if (is_hover["exit_button"])
		{
			drawSprite(exit_button, 127, 926);
		}
		else
		{
			drawSprite(exit_button, 127, 931);
		}
		if (is_hover["about_button"])
		{
			drawSprite(about_button, 1595, 926);
		}
		else
		{
			drawSprite(about_button, 1595, 931);
		}
	}

	

public:
	
	const char* play_sprite_path = "data/interface/main_menu/play_button.png";
	Sprite* play_button;
	std::map <std::string, bool> is_hover;

private:

	Sprite* main_menu_background;
	Sprite* about_button;
	Sprite* score_button;
	Sprite* exit_button;
	

};

class GameOver
{
public:
	GameOver() {
		game_over_background = createSprite("data/interface/game_over/background.png");
		play_button = createSprite("data/interface/game_over/play_button.png");
		exit_button = createSprite("data/interface/game_over/exit_button.png");
		about_button = createSprite("data/interface/game_over/about_button.png");
	};
	~GameOver() {};


	void Draw() {
		drawSprite(game_over_background, 0, 0);
		drawSprite(play_button, 830, 634);
		if (is_hover["exit_button"])
		{
			drawSprite(exit_button, 127, 926);
		}
		else
		{
			drawSprite(exit_button, 127, 931);
		}
		if (is_hover["about_button"])
		{
			drawSprite(about_button, 1595, 926);
		}
		else
		{
			drawSprite(about_button, 1595, 931);
		}
	}

public:

	const char* play_sprite_path = "data/interface/game_over/play_button.png";
	Sprite* play_button;
	std::map <std::string, bool> is_hover;

private:

	Sprite* game_over_background;
	Sprite* exit_button;
	Sprite* about_button;

};




class Interface
{
public:
	Interface(){

		load_background = createSprite("data/interface/connecting.png");
		//Sleep(10);
		load_error_background = createSprite("data/interface/connection_error.png");
		//Sleep(10);
		std::cout << "interface" << "\n";
		
	};
	~Interface(){};

	Reticle GetReticle() {
		return reticle;
	}

	void Draw() {
		if (!is_start_game && !is_game_over)
		{
			menu.Draw();
			
		}
		else if (is_game_over) {
			game_over.Draw();
		}
		else if (is_start_game && !is_connected) {
			

			if (reticle.sprite_path != "data/reticle2.png")
			{
				reticle.sprite_path = "data/reticle2.png";
				reticle.SetSprite(reticle.sprite_path);
			}
			if (is_connection_error)
			{
				drawSprite(load_error_background, 0, 0);

			}
			else if (!is_connection_error)
			{
				drawSprite(load_background, 0, 0);
			}
			
			
			if (mouse_x > 127 && mouse_x < 253 && mouse_y > 931 && mouse_y < 985)
			{
				drawSprite(exit_button_connect, 127, 926);
			}
			else
			{
				drawSprite(exit_button_connect, 127, 931);

			}
			
		}
		else
		{
			if (is_connected)
			{
				cross.Draw();
			}
			
			if (reticle.sprite_path != "data/reticle2.png")
			{
				reticle.sprite_path = "data/reticle2.png";
				reticle.SetSprite(reticle.sprite_path);
			}
			
		}
		reticle.SetCoords(mouse_x, mouse_y);
		reticle.Draw();
	}


	void SimpleSetMouseCoords(int x, int y) {
		mouse_x = x;
		mouse_y = y;
	}

	void SetMouseCoords(int x, int y) {
		mouse_x = x;
		mouse_y = y;
		const char* path = "data/reticle2_dark.png";
		const char* button_path = "data/interface/main_menu/play_button_hover.png";
		const char* game_over_button_path = "data/interface/game_over/play_button_hover.png";

		if (x > 830 && x < 1091 && y > 634 && y < 924)
		{
			if (path != reticle.sprite_path)
			{
				reticle.sprite_path = path;
				reticle.SetSprite(reticle.sprite_path);
			}
			if (button_path != menu.play_sprite_path)
			{
				menu.play_sprite_path = button_path;
				menu.play_button = createSprite(menu.play_sprite_path);

			}
			if (game_over_button_path != game_over.play_sprite_path)
			{
				game_over.play_sprite_path = game_over_button_path;
				game_over.play_button = createSprite(game_over.play_sprite_path);

			}
		}
		else
		{
			if (path == reticle.sprite_path)
			{
				reticle.sprite_path = "data/reticle2.png";
				reticle.SetSprite(reticle.sprite_path);
			}
			if (button_path == menu.play_sprite_path)
			{
				menu.play_sprite_path = "data/interface/main_menu/play_button.png";
				menu.play_button = createSprite(menu.play_sprite_path);
			}
			if (game_over_button_path == game_over.play_sprite_path)
			{
				game_over.play_sprite_path = "data/interface/game_over/play_button.png";
				game_over.play_button = createSprite(game_over.play_sprite_path);
			}
		}
		/*if (x > 127 && x < 320 && y > 940 && y < 985)
		{
			menu.is_hover["score_button"] = true;
		}
		else
		{
			menu.is_hover["score_button"] = false;
		}*/
		if (x > 1595 && x < 1793 && y > 931 && y < 985)
		{
			game_over.is_hover["about_button"] = true;
			menu.is_hover["about_button"] = true;
		}
		else
		{
			game_over.is_hover["about_button"] = false;
			menu.is_hover["about_button"] = false;
		}
		if (x > 127 && x < 253 && y > 931 && y < 985)
		{
			game_over.is_hover["exit_button"] = true;
			menu.is_hover["exit_button"] = true;
		}
		else
		{
			game_over.is_hover["exit_button"] = false;
			menu.is_hover["exit_button"] = false;
		}
	}

	bool IsStart(FRMouseButton button, int x, int y) {
		if (button == FRMouseButton::LEFT && x > 830 && x < 1091 && y > 634 && y < 924)
		{
			
			return true;
		}
		return false;
	}

	bool IsExit(FRMouseButton button, int x, int y) {
		if (button == FRMouseButton::LEFT && x > 127 && x < 253 && y > 931 && y < 985)
		{
			return true;
		}
		return false;
	}

	bool IsAbout(FRMouseButton button, int x, int y) {
		if (button == FRMouseButton::LEFT && x > 1595 && x < 1793 && y > 931 && y < 985)
		{
			return true;
		}
		return false;
	}

	bool IsCross(FRMouseButton button) {
		if (button == FRMouseButton::LEFT && mouse_x > 1814 && mouse_x < 1872 && mouse_y > 48 && mouse_y < 106)
		{
			return true;
		}
		return false;
	}


	void ButtonClick(FRMouseButton button) {
		if (is_start_game && !is_connected) {
			if (mouse_x > 127 && mouse_x < 253 && mouse_y > 931 && mouse_y < 985)
			{
				is_connected = 0;
				is_start_game = 0;
				is_game_over = 0;
				exit_game = 0;
				return;
			}
		}
		else
		{
			
			is_start_game = IsStart(button, mouse_x, mouse_y);
			exit_game = IsExit(button, mouse_x, mouse_y);
			if (is_game_over)
			{
				death_ticks = 0;
				is_game_over = !IsStart(button, mouse_x, mouse_y);
			}
			if (IsAbout(button, mouse_x, mouse_y))
			{
				ShellExecute(0, 0, L"https://github.com/STARBATTLE-online", 0, 0, SW_SHOW);
				Sleep(100);
			}
		}
	}

protected:
	Reticle reticle;
	MainMenu menu;
	GameOver game_over;
	Close cross;
	int mouse_x;
	int mouse_y;
	Sprite* exit_button_connect = createSprite("data/interface/game_over/exit_button.png");
	Sprite* load_background = createSprite("data/interface/connecting.png");
	Sprite* load_error_background = createSprite("data/interface/connection_error.png");
};

//D:/Programming/STARBATTLE/client/client/data/interface/main_menu
