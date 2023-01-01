#pragma once
#include "main_game.h"
#include<windows.h>
#include <iostream>
#include "tank.cpp"
#include "bullet.cpp"
#include "wall.cpp"

main_game::main_game() {
        game_mode = 1;
        tank_num = 0;
        bullet_num = 0;
        wall_num = 0;
        winner = NULL;
}

void main_game::init()
{
	statics st;
	st.maingame->obj_pool.push_back(new wall(5, 100, 0));
	st.maingame->obj_pool.push_back(new wall(1195, 100, 0));
	st.maingame->obj_pool.push_back(new wall(5, 300, 0));
	st.maingame->obj_pool.push_back(new wall(1195, 300, 0));
	st.maingame->obj_pool.push_back(new wall(5, 500, 0));
	st.maingame->obj_pool.push_back(new wall(1195, 500, 0));
	st.maingame->obj_pool.push_back(new wall(5, 700, 0));
	st.maingame->obj_pool.push_back(new wall(1195, 700, 0));
	st.maingame->obj_pool.push_back(new wall(100, 5, 3.1415926 / 2));
	st.maingame->obj_pool.push_back(new wall(100, 795, 3.1415926 / 2));
	st.maingame->obj_pool.push_back(new wall(300, 5, 3.1415926 / 2));
	st.maingame->obj_pool.push_back(new wall(300, 795, 3.1415926 / 2));
	st.maingame->obj_pool.push_back(new wall(500, 5, 3.1415926 / 2));
	st.maingame->obj_pool.push_back(new wall(500, 795, 3.1415926 / 2));
	st.maingame->obj_pool.push_back(new wall(700, 5, 3.1415926 / 2));
	st.maingame->obj_pool.push_back(new wall(700, 795, 3.1415926 / 2));
	st.maingame->obj_pool.push_back(new wall(900, 5, 3.1415926 / 2));
	st.maingame->obj_pool.push_back(new wall(900, 795, 3.1415926 / 2));
	st.maingame->obj_pool.push_back(new wall(1100, 5, 3.1415926 / 2));
	st.maingame->obj_pool.push_back(new wall(1100, 795, 3.1415926 / 2));

	st.maingame->obj_pool.push_back(new tank(100, 100, 0, 1, 87, 65, 83, 68, 81, "WASDQ"));
	st.maingame->obj_pool.push_back(new tank(500, 200, 0, 2, 38, 37, 40, 39, 96, "NUMPAD"));
	st.maingame->obj_pool.push_back(new tank(200, 500, 0, 3, 73, 74, 75, 76, 79, "IJKLO"));
	st.maingame->tank_num = 3;
}

void main_game::load_map()
{
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

