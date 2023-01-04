#pragma once
#include "main_game.h"
#include<windows.h>
#include <iostream>
#include "tank.cpp"
#include "base64.cpp"
#include "bullet.cpp"
#include "wall.cpp"

main_game::main_game() {
        game_mode = 1;
        tank_num = 0;
        winner = NULL;
}

void main_game::init()
{
	obj_pool.push_back(new wall(5, 100, 0));
	obj_pool.push_back(new wall(1195, 100, 0));
	obj_pool.push_back(new wall(5, 300, 0));
	obj_pool.push_back(new wall(1195, 300, 0));
	obj_pool.push_back(new wall(5, 500, 0));
	obj_pool.push_back(new wall(1195, 500, 0));
	obj_pool.push_back(new wall(5, 700, 0));
	obj_pool.push_back(new wall(1195, 700, 0));
	obj_pool.push_back(new wall(100, 5, 3.1415926 / 2));
	obj_pool.push_back(new wall(100, 795, 3.1415926 / 2));
	obj_pool.push_back(new wall(300, 5, 3.1415926 / 2));
	obj_pool.push_back(new wall(300, 795, 3.1415926 / 2));
	obj_pool.push_back(new wall(500, 5, 3.1415926 / 2));
	obj_pool.push_back(new wall(500, 795, 3.1415926 / 2));
	obj_pool.push_back(new wall(700, 5, 3.1415926 / 2));
	obj_pool.push_back(new wall(700, 795, 3.1415926 / 2));
	obj_pool.push_back(new wall(900, 5, 3.1415926 / 2));
	obj_pool.push_back(new wall(900, 795, 3.1415926 / 2));
	obj_pool.push_back(new wall(1100, 5, 3.1415926 / 2));
	obj_pool.push_back(new wall(1100, 795, 3.1415926 / 2));

	gamemap = MapCoder::decode(mapstr);

	for (auto i = gamemap.objs.begin(); i != gamemap.objs.end(); i++)obj_pool.push_back(*i);

	auto i = gamemap.spawns.begin();
	if (gamemap.spawns.size() == 0) {
		obj_pool.push_back(new tank(500, 400, 0, 1, keybinds1[0], keybinds1[1], keybinds1[2], keybinds1[3], keybinds1[4], name1.toStdString()));
		obj_pool.push_back(new tank(700, 400, 0, 2, keybinds2[0], keybinds2[1], keybinds2[2], keybinds2[3], keybinds2[4], name2.toStdString()));
	}
	else if (gamemap.spawns.size() == 1) {
		if (rand() % 2) {
			obj_pool.push_back(new tank((*i).x, (*i).y, (*i).dir, 1, keybinds1[0], keybinds1[1], keybinds1[2], keybinds1[3], keybinds1[4], name1.toStdString()));
			obj_pool.push_back(new tank(700, 400, 0, 2, keybinds2[0], keybinds2[1], keybinds2[2], keybinds2[3], keybinds2[4], name2.toStdString()));
		}
		else {
			obj_pool.push_back(new tank(500, 400, 0, 1, keybinds1[0], keybinds1[1], keybinds1[2], keybinds1[3], keybinds1[4], name1.toStdString()));
			obj_pool.push_back(new tank((*i).x, (*i).y, (*i).dir, 2, keybinds2[0], keybinds2[1], keybinds2[2], keybinds2[3], keybinds2[4], name2.toStdString()));
		}
	}
	else {
		int b = (rand() % (gamemap.spawns.size() - 1)) + 1, a = rand() % b;
		for (int j = 0; j < a; j++)i++;
		obj_pool.push_back(new tank((*i).x, (*i).y, (*i).dir, 1, keybinds1[0], keybinds1[1], keybinds1[2], keybinds1[3], keybinds1[4], name1.toStdString()));
		for (int j = 0; j < b-a; j++)i++;
		obj_pool.push_back(new tank((*i).x, (*i).y, (*i).dir, 2, keybinds2[0], keybinds2[1], keybinds2[2], keybinds2[3], keybinds2[4], name2.toStdString()));
	}

	tank_num = 2;
}

void main_game::load_map(std::string input)
{
	mapstr = Base64::decode(input);
}

void main_game::clear_pool() {
	for (auto i = obj_pool.begin(); i != obj_pool.end();)
	{
		delete* i;
		i = obj_pool.erase(i);
	}
}

main_game::~main_game() {
        std::cout << "GAME OVER";
}


#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 
void main_game::keyboard_detection() {
        for (int i = 1; i < 120; i++)
                        down[i] = KEY_DOWN(i);
}
#undef KEY_DOWN(VK_NONAME)

void main_game::add_object(object * obj) {
        obj_pool.push_back(obj);
}

