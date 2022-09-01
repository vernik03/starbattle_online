#pragma once
#include <iostream>
#include <memory>
#include "MapCreator.h"

// Request format:

// MAP_WIDTH, MAP_HEIGHT
// asteroid_count, ship_count
// for each asteroid:
//  ASTEROID_TYPE
//  serialize(asteroid)
// for each ship:
//  SHIP
//  serialize(ship)
//  

// Singleton
class InfoFromServer {
    static std::shared_ptr<MapCreator> m_map_creator;
    static std::shared_ptr<MapCreator> m_swap_map_creator;
public:
    InfoFromServer() {};
    ~InfoFromServer() {};
    static void SetMapCreator(std::shared_ptr<MapCreator> map_creator);
    static std::string ProcessRequest(const std::string& request);
    static void InitRequest(std::stringstream& ss);
    static void TickRequest(std::stringstream& ss);
};

std::shared_ptr<MapCreator> InfoFromServer::m_map_creator;
std::shared_ptr<MapCreator> InfoFromServer::m_swap_map_creator;

void InfoFromServer::SetMapCreator(std::shared_ptr<MapCreator> map_creator) {
    InfoFromServer::m_map_creator = map_creator;
    InfoFromServer::m_swap_map_creator = std::make_shared<MapCreator>(*map_creator);
}

std::string InfoFromServer::ProcessRequest(const std::string& request) {
    //Sleep(0);//?
    std::stringstream ss(request);
    std::string output, commandType;

    //////std::cout << request << std::endl;

    while (ss >> commandType) {
        if (commandType == "INIT") {

            std::lock_guard<std::mutex> lock(InfoFromServer::m_map_creator->mt);
            //////std::cout << "INIT" << std::endl;
            InitRequest(ss);
        }
        else if (commandType == "TICK") {

            //////std::cout << "TICK" << std::endl;
            TickRequest(ss);
        }
    }

    return output;
}

void InfoFromServer::InitRequest(std::stringstream& ss) {
    int x, y;
    uint64_t sprite_id;
    std::string init_version;
    ss >> init_version >> personal_id_public >> personal_id_private >> x >> y >> sprite_id >> map_width >> map_height;

    if (init_version == VERSION)
    {
        InfoFromServer::m_map_creator->AddMainHero(x, y, sprite_id);

        request = "TICK";
        request += " ";
        request += std::to_string(personal_id_public);
		
        is_connected = 1;
    }
    else
    {
        InfoFromServer::m_map_creator->OldVersion();
    }
    
}

void InfoFromServer::TickRequest(std::stringstream& ss) {

    ss >> tick_number;
    bool i_am_here = false;
    std::string commandType;
    InfoFromServer::m_swap_map_creator->asteroids.clear();
    InfoFromServer::m_swap_map_creator->asteroids.reserve(50);
    InfoFromServer::m_swap_map_creator->ships.clear();
    InfoFromServer::m_swap_map_creator->ships.reserve(50);
    InfoFromServer::m_swap_map_creator->bullets.clear();
    InfoFromServer::m_swap_map_creator->bullets.reserve(50);
	InfoFromServer::m_swap_map_creator->explosions.clear();
	InfoFromServer::m_swap_map_creator->explosions.reserve(50);
    InfoFromServer::m_swap_map_creator->powers.clear();
    InfoFromServer::m_swap_map_creator->powers.reserve(50);
    InfoFromServer::m_swap_map_creator->base.SetHP(0);
	Ship* ship;
    while (ss >> commandType)
    {
        if (commandType == "BigAsteroid")
        {
            int x, y;
			ss >> x >> y ;
            InfoFromServer::m_swap_map_creator->asteroids.emplace_back(Asteroid(x, y, AsteroidTypes::Big));
		}
		else if (commandType == "SmallAsteroid")
		{
            int x, y;
            ss >> x >> y;
            InfoFromServer::m_swap_map_creator->asteroids.emplace_back(Asteroid(x, y, AsteroidTypes::Small));

		}
		else if (commandType == "Ship")
		{
			int x, y, score, hp, shield;
            bool is_hp;
			uint64_t sprite_id, public_id;
            char rotation;
            bool is_engine;
            double x_speed, y_speed;
            Rotation rot = Rotation::Top;

            ss >> is_hp >> x >> y >> rotation >> x_speed >> y_speed >> sprite_id >> shield >> hp >> is_engine >> public_id >> score;
			
            switch (rotation) {
            case 'T':
                rot = Rotation::Top;
                break;
            case 'L':
                rot = Rotation::Left;
                break;
            case 'B':
                rot = Rotation::Bottom;
                break;
            case 'R':
                rot = Rotation::Right;
                break;
            default:
                break;
            }

            if (personal_id_public == public_id)
            {
                InfoFromServer::m_swap_map_creator->main_hero.SetCoordsByCenter(x, y);
                InfoFromServer::m_swap_map_creator->main_hero.SetEngine(is_engine);
                InfoFromServer::m_swap_map_creator->main_hero.SetShield(shield);
                InfoFromServer::m_swap_map_creator->main_hero.SetHP(hp);
                InfoFromServer::m_swap_map_creator->main_hero.SetSpeed(x_speed, y_speed);
                ship = &(InfoFromServer::m_swap_map_creator->main_hero);
                window_x = InfoFromServer::m_swap_map_creator->main_hero.GetCenterGlobal().first - window_width / 2;
                window_y = InfoFromServer::m_swap_map_creator->main_hero.GetCenterGlobal().second - window_height / 2;
                my_score = score;
                i_am_here = true;
                death_ticks = 0;
                //std::cout << score << "\n";
            }
            else
            {
                InfoFromServer::m_swap_map_creator->ships.push_back(EnemyShip(x, y, rot, sprite_id));
                InfoFromServer::m_swap_map_creator->ships.back().SetRotation(rot);
                InfoFromServer::m_swap_map_creator->ships.back().SetEngine(is_engine);
                InfoFromServer::m_swap_map_creator->ships.back().SetShield(shield);
                InfoFromServer::m_swap_map_creator->ships.back().SetHP(hp, is_hp);
                ship = &InfoFromServer::m_swap_map_creator->ships.back();
            }
		}
        else if (commandType == "Bullet")
        {
            int x, y;
            int x_speed, y_speed;
			ss >> x >> y >> x_speed >> y_speed;
            InfoFromServer::m_swap_map_creator->Shoot(x, y);
			
        }
        else if (commandType == "BigExplosion")
        {
            int x, y, start_tick;
            ss >> x >> y >> start_tick;
            InfoFromServer::m_swap_map_creator->explosions.emplace_back(Explosion(x, y, start_tick, ExplosionTypes::Big));
           //how many explosions?
            //se.playSoundEffect(2);			
        }
        else if (commandType == "SmallExplosion")
        {
            int x, y, start_tick;
            ss >> x >> y >> start_tick;
            InfoFromServer::m_swap_map_creator->explosions.emplace_back(Explosion(x, y, start_tick, ExplosionTypes::Small));

        }
        else if (commandType == "HugeExplosion")
        {
            int x, y, start_tick;
            ss >> x >> y >> start_tick;
            InfoFromServer::m_swap_map_creator->explosions.emplace_back(Explosion(x, y, start_tick, ExplosionTypes::Huge));
            //std::cout << "BOOM" << "\n";

        }
        else if (commandType == "Shield")
        {
            int x, y;
            ss >> x >> y;
            InfoFromServer::m_swap_map_creator->powers.emplace_back(Power(x, y, PowerTypes::Shield));

        }
        else if (commandType == "Barrage")
        {
            int x, y;
            ss >> x >> y;
            InfoFromServer::m_swap_map_creator->powers.emplace_back(Power(x, y, PowerTypes::Barrage));

			
        }
        else if (commandType == "Heal")
        {
            int x, y;
            ss >> x >> y;
            InfoFromServer::m_swap_map_creator->powers.emplace_back(Power(x, y, PowerTypes::Heal));
        }
        else if (commandType == "EnemySpawner")
        {
            int x, y, hp, status;
            bool is_hp;
            ss >> is_hp >> x >> y >> hp >> status;
            InfoFromServer::m_swap_map_creator->base.SetCoordsByCenter(x, y);
            InfoFromServer::m_swap_map_creator->base.SetStatus(status);
            InfoFromServer::m_swap_map_creator->base.SetHP(hp);
            //std::cout << x << y << hp << status << "\n";
        }
        
    }
    if (!i_am_here)
    {
       
        death_ticks++;
        if (death_ticks > 70)
        {
             is_start_game = 0;
             is_game_over = 1;
             is_connected = 0;
             death_ticks = 0;

             se.playMusicEffect(0);
        }
        //is_start_game = 0;
        //is_game_over = 1;
        //is_connected = 0;
    }
    //////std::cout << InfoFromServer::m_map_creator->asteroids.size() << " " << InfoFromServer::m_map_creator->ships.size() << " " << InfoFromServer::m_map_creator->bullets.size() << "\n";
   
    //InfoFromServer::m_map_creator = std::make_shared<MapCreator>(*m_swap_map_creator);
    //std::swap(InfoFromServer::m_map_creator, InfoFromServer::m_swap_map_creator);
    InfoFromServer::m_map_creator->asteroids = InfoFromServer::m_swap_map_creator->asteroids;
	InfoFromServer::m_map_creator->ships = InfoFromServer::m_swap_map_creator->ships;
	InfoFromServer::m_map_creator->bullets = InfoFromServer::m_swap_map_creator->bullets;
	InfoFromServer::m_map_creator->powers = InfoFromServer::m_swap_map_creator->powers;
	InfoFromServer::m_map_creator->explosions = InfoFromServer::m_swap_map_creator->explosions;
    InfoFromServer::m_swap_map_creator->main_hero.SetRotation(InfoFromServer::m_map_creator->main_hero.GetRotation());
    InfoFromServer::m_swap_map_creator->main_hero.sprite_id = InfoFromServer::m_map_creator->main_hero.sprite_id;
    InfoFromServer::m_map_creator->main_hero = InfoFromServer::m_swap_map_creator->main_hero;
	InfoFromServer::m_map_creator->base = InfoFromServer::m_swap_map_creator->base;
	
}