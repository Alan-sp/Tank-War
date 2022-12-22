#pragma once
#include <cmath>
#include "tank.cpp"
#include<list>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 

class main_game {
public:
	int game_mode;
	main_game();
	~main_game();
    std::list<object*> obj_pool;
	int tank_num;
	int bullet_num;
	int wall_num;
    int down[181];

	int keyboard_detection();
	int flushed(main_game* game);
	int crash(main_game* game);
};



